//
// Created by helta on 2026/5/13.
//
#ifndef STACK_QUEUE_STACK_H
#define STACK_QUEUE_STACK_H

#include<vector>
#include<list>
using namespace std;

namespace helta {
    //容器适配器
    template<class T,class Container = vector<T>>
    class stack
    {
        public:
        void push(const T& x)
        {
            con_.push_back(x);
        }

        void pop()
        {
            con_.pop_back();
        }
        T& top()
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

#endif //STACK_QUEUE_STACK_H
