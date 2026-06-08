#pragma once
#include "HashTable.h"

namespace helta
{
    template<class K, class V, class HashFunc = DefaultHashFunc<K>>
    class UnorderedMap
    {
        struct MapKeyOfT
        {
            const K& operator() (const pair<const K, V>& kv) const
            {
                return kv.first;
            }
        };

    public:
        typedef typename hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, HashFunc>::iterator iterator;
        typedef typename hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, HashFunc>::const_iterator const_iterator;

        iterator begin()
        {
            return ht_.begin();
        }

        iterator end()
        {
            return ht_.end();
        }

        const_iterator begin() const
        {
            return ht_.begin();
        }

        const_iterator end() const
        {
            return ht_.end();
        }

        pair<iterator, bool> Insert(const pair<K, V>& kv)
        {
            return ht_.Insert(kv);
        }

        V& operator[] (const K& key)
        {
            pair<iterator, bool> ret = ht_.Insert(make_pair(key, V()));
            return ret.first->second;
        }

        iterator Find(const K& key)
        {
            return ht_.Find(key);
        }

        bool Erase(const K& key)
        {
            return ht_.Erase(key);
        }

    private:
        hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, HashFunc> ht_;
    };
}
