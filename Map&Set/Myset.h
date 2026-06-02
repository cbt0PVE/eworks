#pragma once
#include "RBTree.h"

namespace helta
{
    template<class T>
    class Set
    {
        struct KeyOfT
        {
            const T& operator()(const T& key)
            {
                return key;
            }
        };
        public:
        // Set iterators should be const even if they are not const_iterators
        typedef typename RBTree<T,T,KeyOfT>::const_iterator iterator;
        typedef typename RBTree<T,T,KeyOfT>::const_iterator const_iterator;

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
        pair<iterator,bool> Insert(const T& key)
        {
            auto ret = t_.Insert(key);
            return pair<iterator,bool>(ret.first,ret.second);
        }
        private:
        RBTree<T,T,KeyOfT> t_;
    };
}