#pragma once
#include "RBTree.h"

namespace helta
{
    template<class K,class V>
    class map
    {
        struct MapKeyOfT
        {
            const K& operator()(const pair<const K,V>& kv)
            {
                return kv.first;
            }
        };
        public:
        typedef typename RBTree<K,pair<const K,V>,MapKeyOfT>::iterator iterator;
        typedef typename RBTree<K,pair<const K,V>,MapKeyOfT>::const_iterator const_iterator;
        
        iterator begin()
        {
            return t_.begin();
        }

        iterator end()
        {
            return t_.end();
        }


        const_iterator begin() const
        {
            return t_.begin();
        }

        const_iterator end() const
        {
            return t_.end();
        }
        V& operator[](const K& key)
        {
            pair<iterator,bool> ret = t_.Insert(make_pair(key,V()));
            return ret.first->second;
        }
        pair<iterator,bool> Insert(const pair<const K,V>& kv)
        {
            return t_.Insert(kv);
        }
        private:
        RBTree<K,pair<const K,V>,MapKeyOfT> t_;
    };
}