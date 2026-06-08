#pragma once 
#include <vector>
#include <iostream>
#include <string>

using namespace std;

template <class K>
struct DefaultHashFunc
{
    size_t operator()(const K& key) const
    {
        return (size_t)key;
    }
};

template<>
struct DefaultHashFunc<string>
{
    size_t operator() (const string& str) const
    {
        size_t hash = 0;
        for(auto ch : str)
        {
            hash *= 131;
            hash += ch;
        }
        return hash;
    }
};

namespace open_address
{
    enum STATE
    {
        EMPTY,
        EXIST,
        DELETE
    };

    template<class K, class V>
    struct HashData
    {
        pair<K, V> kv_;
        STATE state_ = EMPTY;
    };

    template<class K, class V, class HashFunc = DefaultHashFunc<K>>
    class HashTable
    {
    public:
        HashTable()
        {
            ht_.resize(10);
        }

        bool Insert(const pair<K, V>& kv)
        {
            if (Find(kv.first))
            {
                return false;
            }

            if (n_ * 10 / ht_.size() >= 7)
            {
                size_t newSize = ht_.size() * 2;
                HashTable<K, V, HashFunc> newTable;
                newTable.ht_.resize(newSize);

                for (size_t i = 0; i < ht_.size(); i++)
                {
                    if (ht_[i].state_ == EXIST)
                    {
                        newTable.Insert(ht_[i].kv_);
                    }
                }
                ht_.swap(newTable.ht_);
            }

            HashFunc hf;
            size_t hashi = hf(kv.first) % ht_.size();
            while (ht_[hashi].state_ == EXIST)
            {
                ++hashi;
                hashi %= ht_.size();
            }

            ht_[hashi].kv_ = kv;
            ht_[hashi].state_ = EXIST;
            n_++;
            return true;
        }

        HashData<K, V>* Find(const K& key)
        {
            HashFunc hf;
            size_t hashi = hf(key) % ht_.size();
            while (ht_[hashi].state_ != EMPTY)
            {
                if (ht_[hashi].state_ == EXIST && ht_[hashi].kv_.first == key)
                {
                    return &ht_[hashi];
                }
                ++hashi;
                hashi %= ht_.size();
            }
            return nullptr;
        }

        bool Erase(const K& key)
        {
            HashData<K, V>* data = Find(key);
            if (data)
            {
                data->state_ = DELETE;
                n_--;
                return true;
            }
            return false;
        }

    private:
        vector<HashData<K, V>> ht_;
        size_t n_ = 0;
    };
}

namespace hash_bucket
{
    template<class T>
    struct HashNode
    {
        T data_;
        HashNode<T>* next_;

        HashNode(const T& data)
            : data_(data)
            , next_(nullptr)
        {}
    };

    template<class K, class T, class KeyOfT, class HashFunc>
    class HashTable;

    template<class K, class T, class Ptr, class Ref, class KeyOfT, class HashFunc>
    struct HashTableIterator
    {
        typedef HashNode<T> Node;
        typedef HashTableIterator<K, T, Ptr, Ref, KeyOfT, HashFunc> Self;

        Node* node_;
        const HashTable<K, T, KeyOfT, HashFunc>* pht_;

        HashTableIterator(Node* node, const HashTable<K, T, KeyOfT, HashFunc>* pht)
            : node_(node)
            , pht_(pht)
        {}

        HashTableIterator(const HashTableIterator<K, T, T*, T&, KeyOfT, HashFunc>& it)
            : node_(it.node_)
            , pht_(it.pht_)
        {}

        Ref operator*()
        {
            return node_->data_;
        }

        Ptr operator->()
        {
            return &(node_->data_);
        }

        Self& operator++()
        {
            if (node_->next_)
            {
                node_ = node_->next_;
            }
            else
            {
                KeyOfT kot;
                HashFunc hf;
                size_t hashi = hf(kot(node_->data_)) % pht_->ht_.size();
                ++hashi;
                while (hashi < pht_->ht_.size())
                {
                    if (pht_->ht_[hashi])
                    {
                        node_ = pht_->ht_[hashi];
                        return *this;
                    }
                    else
                    {
                        hashi++;
                    }
                }
                node_ = nullptr;
            }
            return *this;
        }

        bool operator!=(const Self& it) const
        {
            return node_ != it.node_;
        }

        bool operator==(const Self& it) const
        {
            return node_ == it.node_;
        }
    };

    template<class K, class T, class KeyOfT, class HashFunc = DefaultHashFunc<K>>
    class HashTable
    {
        typedef HashNode<T> Node;
        template<class K1, class T1, class Ptr, class Ref, class KeyOfT1, class HashFunc1>
        friend struct HashTableIterator;

    public:
        typedef HashTableIterator<K, T, T*, T&, KeyOfT, HashFunc> iterator;
        typedef HashTableIterator<K, T, const T*, const T&, KeyOfT, HashFunc> const_iterator;

        iterator begin()
        {
            for (size_t i = 0; i < ht_.size(); i++)
            {
                Node* cur = ht_[i];
                if (cur)
                {
                    return iterator(cur, this);
                }
            }
            return iterator(nullptr, this);
        }

        iterator end()
        {
            return iterator(nullptr, this);
        }

        const_iterator begin() const
        {
            for (size_t i = 0; i < ht_.size(); i++)
            {
                Node* cur = ht_[i];
                if (cur)
                {
                    return const_iterator(cur, this);
                }
            }
            return const_iterator(nullptr, this);
        }

        const_iterator end() const
        {
            return const_iterator(nullptr, this);
        }

        size_t GetNextPrime(size_t prime)
        {
            static const int __stl_num_primes = 28;
            static const unsigned long __stl_prime_list[__stl_num_primes] =
            {
                53, 97, 193, 389, 769,
                1543, 3079, 6151, 12289, 24593,
                49157, 98317, 196613, 393241, 786433,
                1572869, 3145739, 6291469, 12582917, 25165843,
                50331653, 100663319, 201326611, 402653189, 805306457,
                1610612741
            };
            for (size_t i = 0; i < __stl_num_primes; i++)
            {
                if (__stl_prime_list[i] > prime)
                    return __stl_prime_list[i];
            }
            return __stl_prime_list[__stl_num_primes - 1];
        }

        HashTable()
        {
            ht_.resize(GetNextPrime(1), nullptr);
        }

        ~HashTable()
        {
            for (size_t i = 0; i < ht_.size(); i++)
            {
                Node* cur = ht_[i];
                while (cur)
                {
                    Node* del = cur;
                    cur = cur->next_;
                    delete del;
                }
                ht_[i] = nullptr;
            }
        }

        pair<iterator, bool> Insert(const T& data)
        {
            KeyOfT kot;
            iterator it = Find(kot(data));
            if (it != end())
            {
                return make_pair(it, false);
            }

            HashFunc hf;
            if (n_ == ht_.size())
            {
                size_t newSize = GetNextPrime(ht_.size());
                vector<Node*> newHt(newSize, nullptr);
                for (size_t i = 0; i < ht_.size(); i++)
                {
                    Node* cur = ht_[i];
                    while (cur)
                    {
                        Node* next = cur->next_;
                        size_t hashi = hf(kot(cur->data_)) % newSize;
                        cur->next_ = newHt[hashi];
                        newHt[hashi] = cur;
                        cur = next;
                    }
                    ht_[i] = nullptr;
                }
                ht_.swap(newHt);
            }

            size_t hashi = hf(kot(data)) % ht_.size();
            Node* newNode = new Node(data);
            newNode->next_ = ht_[hashi];
            ht_[hashi] = newNode;
            n_++;
            return make_pair(iterator(newNode, this), true);
        }

        iterator Find(const K& key)
        {
            HashFunc hf;
            KeyOfT kot;
            size_t hashi = hf(key) % ht_.size();
            Node* cur = ht_[hashi];
            while (cur)
            {
                if (kot(cur->data_) == key)
                {
                    return iterator(cur, this);
                }
                cur = cur->next_;
            }
            return end();
        }

        bool Erase(const K& key)
        {
            HashFunc hf;
            KeyOfT kot;
            size_t hashi = hf(key) % ht_.size();
            Node* cur = ht_[hashi];
            Node* prev = nullptr;
            while (cur)
            {
                if (kot(cur->data_) == key)
                {
                    if (prev == nullptr)
                    {
                        ht_[hashi] = cur->next_;
                    }
                    else
                    {
                        prev->next_ = cur->next_;
                    }
                    delete cur;
                    n_--;
                    return true;
                }
                prev = cur;
                cur = cur->next_;
            }
            return false;
        }

        void Print()
        {
            KeyOfT kot;
            for (size_t i = 0; i < ht_.size(); i++)
            {
                printf("[%zu]->", i);
                Node* cur = ht_[i];
                while (cur)
                {
                    cout << kot(cur->data_) << "->";
                    cur = cur->next_;
                }
                printf("NULL\n");
            }
            cout << endl;
        }

    private:
        vector<Node*> ht_;
        size_t n_ = 0;
    };
}
