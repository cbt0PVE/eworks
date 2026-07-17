#pragma once
#include<bitset>
#include<string>

struct BKDRHash
{
    size_t operator()(const std::string& str) const
    {
        size_t hash = 0;
        for(char ch:str)
        {
            hash = hash * 131 + ch;
        }   
        return hash;
    }
};

struct APHash
{
    size_t operator()(const std::string &str) const
{
    size_t hash = 0;
    for(size_t i = 0; i < str.size(); ++i)
    {
         size_t ch = str[i];
         if((i & 1) == 0)
         {
            hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
         }
         else
         {
            hash ^= (~(hash << 11)^ch^(hash >> 5));
         }

    }
    return hash;
}

};

struct DJBHash
{
    size_t operator()(const std::string& str)
    {
        size_t hash = 5381;
        for(auto ch : str)
        {
            hash += (hash << 5) + ch;
        }

        return hash;
    }
};

template<size_t N,
    class K = std::string,
    class Hash1 = BKDRHash,
    class Hash2 = APHash,
    class Hash3 = DJBHash>
class BloomFilter
{
    public: 
    void Set(const K& key)
    {
        size_t hash1 = Hash1()(key) % N;
        bs_.set(hash1);

        size_t hash2 = Hash2()(key) % N;
        bs_.set(hash2);

        size_t hash3 = Hash3()(key) % N;
        bs_.set(hash3);
    }
    bool Test(const K& key)
    {
        size_t hash1 = Hash1()(key) % N;
        if(bs_.test(hash1) == false)
        return false;

        size_t hash2 = Hash2()(key) % N;
        if(bs_.test(hash2) == false)
        return false;

        size_t hash3 = Hash3()(key) % N;
        if(bs_.test(hash3) == false)
        return false;

        return true;
    }
    
    private:
    bitset<N> bs_;
};