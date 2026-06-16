#pragma once
#include<vector>
using namespace std;
namespace helta
{
    template<size_t N>
    class HeltaSet
    {
        public:
        
        HeltaSet()
        {
            a_.resize(N / 32 + 1);
        }
        void set(size_t x)
        {
            size_t i = x/32;
            size_t j = x%32;
            a_[i] |= (1 << j);

        }
        void reset(size_t x)
        {
            size_t i = x/32;
            size_t j = x%32;
            a_[i] &= (~(1 << j));
        }
        bool test(size_t x)
        {
            size_t i = x/32;
            size_t j = x%32;
            return a_[i] & (1 << j);
        }
        private:
        vector<int> a_;
    };
    template<size_t N>
    class twoheltaset
    {
        public:
        void set(size_t x)
        {
            //00->01
            if(!hs1_.test(x) && !hs2_.test(x))
            {
                hs2_.set(x);
            }
            else if(!hs1_.test(x) && hs2_.test(x))
            {
                hs1_.set(x);
                hs2_.reset(x);
            }
        }
        bool is_once(size_t x)
        {
            return !hs1_.test(x) && hs2_.test(x);
        }
        private:
        HeltaSet<N> hs1_;
        HeltaSet<N> hs2_;
    };
}