#pragma once
#include<vector>
using namespace std;
namespace helta
{
    class HeltaSet
    {
        public:
        void set(size_t x)
        {
            size_t i = x/32;
            size_t j = x%32;

        }
        void reset(size_t x)
        {

        }
        private:
        vector<int> a_;
    };
}