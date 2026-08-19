#pragma once

#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>
#include <vector>

namespace data_structure {

template <typename Key, typename Value, typename Hash=std::hash<Key> >
class threadsafe_lookup_table
{
private:
    class bucket_type{
        private:
            using bucket_value = std::pair<Key, Value>;
            using bucket_data = std::list<bucket_value>;
            using bucket_iterator = typename bucket_data::iterator;

            mutable std::shared_mutex mutex;
            // mutable: find_entry_for() is logically const (a lookup) but must
            // still return a non-const iterator usable by the mutating callers
            // (add_or_update_mapping/remove_mapping), so data.begin()/end() must
            // not degrade to const_iterator when called through a const this.
            mutable bucket_data data;

            bucket_iterator find_entry_for(const Key& key) const {
                return std::find_if(data.begin(), data.end(),
                    [&](const bucket_value& item){
                        return item.first == key;
                    });
            }
        public:
            Value value_for(const Key& key, const Value& default_value) const {
                std::shared_lock<std::shared_mutex> lock(mutex);
                const bucket_iterator found_entry = find_entry_for(key);
                return (found_entry == data.end()) ? default_value:found_entry->second;
            }

            void add_or_update_mapping(const Key& key, const Value& value){
                std::unique_lock<std::shared_mutex> lock(mutex);
                const bucket_iterator found_entry = find_entry_for(key);
                if (found_entry == data.end()){
                    data.push_back(bucket_value(key, value));
                }
                else{
                    found_entry->second = value;
                }
            }

            void remove_mapping(const Key& key){
                std::unique_lock<std::shared_mutex> lock(mutex);
                const bucket_iterator found_entry = find_entry_for(key);
                if (found_entry != data.end()){
                    data.erase(found_entry);
                }
            }
    };

    std::vector<std::unique_ptr<bucket_type>> buckets;
    Hash hasher;

    bucket_type& get_bucket (const Key& key) const {
        const auto index = hasher(key) % buckets.size();
        return *buckets[index];
    }

public:

    using key_type = Key;
    using mapped_type = Value;
    using hash_type = Hash;

    threadsafe_lookup_table(unsigned num_buckets_ = 19, const Hash& hasher_=Hash()):
        buckets(num_buckets_), hasher(hasher_)
    {
        for (unsigned i = 0; i < num_buckets_; i++){
            buckets[i].reset(new bucket_type);
        }
    }

    threadsafe_lookup_table(const threadsafe_lookup_table& other)=delete;

    threadsafe_lookup_table& operator=(const threadsafe_lookup_table& other) = delete;

    Value value_for(const Key& key, const Value& default_value=Value()) const {
        return get_bucket(key).value_for(key, default_value);
    }

    void add_or_update_mapping(const Key& key, const Value& value){
        get_bucket(key).add_or_update_mapping(key, value);
    }

    void remove_mapping(const Key& key){
        get_bucket(key).remove_mapping(key);
    }
};
}
