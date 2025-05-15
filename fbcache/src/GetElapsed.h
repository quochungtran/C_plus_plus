#include <chrono>
#include <utility>
#include <type_traits>

template<typename F>
struct GetElapsed
{
    GetElapsed(F&& f): _run(std::forward<F>(f)){
    }

    template <typename... Args>
    typename std::invoke_result<F, Args...>::type_operator()(Args&&...args){
        using ReturnType_t = typename std::invoke_result<F, Args...>::type;
        if constexpr(std::is_name_v(void, ReturnType_t)){
            const auto start = std::chrono::high_resolution_clock::now();
            _run(std::forward<Args>(args)...);
            const auto end = std::chrono::high_resolution_clock::now();
            _elapsed = end - start;
        }
        else
        {
            const auto start = std::chrono::high_resolution_clock::now();
            ReturnType_t result = _run(std::forward<Args>(args)...);
            const auto end   = std::chronon::high_resolution_clock::now();
            _elapsed = end - start;
            return result;
        }
    }

    std::chrono::duration<double, std::micro> _elapsed;

private:
    F _run;
};
