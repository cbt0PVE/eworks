#include<vector>
#include<list>
using namespace std;

namespace helta {
    //容器适配器
    template<class T,class Container = vector<T>>
    class queue
    {
        public:
        void push(const T& x)
        {
            con_.push_back(x);
        }

        void pop()
        {
            con_.pop_front();
        }
        T& front()
        {
            return con_.front();
        }
        T& back()
        {
            return con_.back();
        }
        size_t size()
        {
            return con_.size();
        }
        bool empty()
        {
            return con_.empty();
        }

        private:
        Container con_;
    };
};