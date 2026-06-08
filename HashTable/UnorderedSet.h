#pragma once
#include "HashTable.h"

namespace helta
{
    template<class K, class HashFunc = DefaultHashFunc<K>>
    class UnorderedSet
    {
        struct SetKeyOfT
        {
            const K& operator() (const K& key) const
            {
                return key;
            }
        };

    public:
        typedef typename hash_bucket::HashTable<K, K, SetKeyOfT, HashFunc>::const_iterator iterator;
        typedef typename hash_bucket::HashTable<K, K, SetKeyOfT, HashFunc>::const_iterator const_iterator;

        iterator begin() const
        {
            return ht_.begin();
        }

        iterator end() const
        {
            return ht_.end();
        }

        pair<iterator, bool> Insert(const K& data)
        {
            return ht_.Insert(data);
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
        hash_bucket::HashTable<K, K, SetKeyOfT, HashFunc> ht_;
    };
}
