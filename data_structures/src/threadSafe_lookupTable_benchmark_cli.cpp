// Standalone CLI benchmark for threadsafe_lookup_table.
// Times an iterative (no-thread) read baseline against value_for split across
// a sweep of reader-thread counts. Build in Release — this target has no
// compiler-level speedup in Debug builds.
//
// Usage: threadSafe_lookupTable_benchmark_cli [total_ops] [num_buckets] [thread_counts...]
//   total_ops     total keys read per session (default 20000)
//   num_buckets   bucket count for the table (default: total_ops/4, floor 19 —
//                 keeps average bucket occupancy low so find_entry_for's linear
//                 scan doesn't dominate; pass explicitly to stress contention)
//   thread_counts space-separated thread counts to sweep (default: 1 2 4 8 12 16 20)

#include "threadSafe_lookupTable.hpp"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <thread>
#include <vector>

using data_structure::threadsafe_lookup_table;
using Clock = std::chrono::steady_clock;

namespace {

// Stopwatch: get() reports elapsed time as of the call, not deferred to
// destruction — start/stop by scope alone (no explicit .stop()), but the
// caller must query get() before the object goes out of scope.
class ElapsedTimer
{
public:
    ElapsedTimer() : start_(Clock::now()) {}

    double get() const {
        return std::chrono::duration<double>(Clock::now() - start_).count();
    }

private:
    Clock::time_point start_;
};

// Pre-populates the table, then reads every key back sequentially — isolates
// value_for's cost from add_or_update_mapping's.
double sequential_read_seconds(long total_ops, unsigned num_buckets) {
    threadsafe_lookup_table<long, long> table(num_buckets);
    for (long key = 0; key < total_ops; ++key) table.add_or_update_mapping(key, key);

    ElapsedTimer clock;
    for (long key = 0; key < total_ops; ++key) {
        volatile long value = table.value_for(key, -1);
        (void)value;
    }
    return clock.get();
}

// Same pre-population, then `threads` readers each read a disjoint key slice
// concurrently. value_for takes a std::shared_lock, so readers on different
// buckets — and even the same bucket — don't block each other.
double concurrent_read_seconds(int threads, long total_ops, unsigned num_buckets) {
    threadsafe_lookup_table<long, long> table(num_buckets);
    for (long key = 0; key < total_ops; ++key) table.add_or_update_mapping(key, key);

    std::vector<std::thread> readers;
    readers.reserve(threads);
    // Each thread writes only its own index — no synchronization needed, and
    // nothing here runs until after join(), so it can't skew the timed region.
    std::vector<long> reads_per_thread(threads, 0);

    ElapsedTimer clock;
    for (int t = 0; t < threads; ++t)
        readers.emplace_back([&table, &reads_per_thread, t, threads, total_ops] {
            long count = 0;
            for (long key = t; key < total_ops; key += threads) {
                volatile long value = table.value_for(key, -1);
                (void)value;
                ++count;
            }
            reads_per_thread[t] = count;
        });
    for (auto& r : readers) r.join();
    const double elapsed = clock.get();

    long total_reads = 0;
    for (long count : reads_per_thread) total_reads += count;
    if (total_reads != total_ops) {
        std::fprintf(stderr,
                      "WARNING: %d threads read %ld elements, expected %ld (strided partition is broken)\n",
                      threads, total_reads, total_ops);
    }

    return elapsed;
}

// Prints the iterative baseline then the concurrent sweep for one workload.
// Elapsed times print in microseconds — these sessions are typically well
// under a second, where a %.4f-second column reads as mostly zeroes.
void report_sweep(const char* label, long total_ops, const std::vector<int>& thread_counts,
                   double sequential_seconds, const std::function<double(int)>& concurrent_seconds) {
    std::printf("\n-- %s --\n", label);
    std::printf("%-28s %12.1f us  %14.0f ops/sec\n",
                "iterative (no threads)", sequential_seconds * 1e6, total_ops / sequential_seconds);
    for (int threads : thread_counts) {
        const double elapsed = concurrent_seconds(threads);
        std::printf("concurrent, %2d thread(s)     %12.1f us  %14.0f ops/sec\n",
                    threads, elapsed * 1e6, total_ops / elapsed);
    }
}

}  // namespace

int main(int argc, char** argv) {
    const long total_ops = argc > 1 ? std::atol(argv[1]) : 20000L;
    const unsigned num_buckets = argc > 2
        ? static_cast<unsigned>(std::atoi(argv[2]))
        : static_cast<unsigned>(std::max(19L, total_ops / 4));

    std::vector<int> thread_counts;
    if (argc > 3) {
        for (int i = 3; i < argc; ++i) thread_counts.push_back(std::atoi(argv[i]));
    } else {
        thread_counts = {1, 2, 4, 8, 12, 16, 20};
    }

    std::printf("total_ops=%ld num_buckets=%u\n", total_ops, num_buckets);

    // value_for takes a std::shared_lock, so this is where multiple threads
    // should scale rather than serialize.
    report_sweep("reads (value_for, std::shared_lock)", total_ops, thread_counts,
                 sequential_read_seconds(total_ops, num_buckets),
                 [&](int threads) { return concurrent_read_seconds(threads, total_ops, num_buckets); });

    return 0;
}
