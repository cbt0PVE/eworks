//
// Created by helta on 2026/5/13.
//
#ifndef STACK_QUEUE_STACK_H
#define STACK_QUEUE_STACK_H

#include<deque>

namespace helta {
    //容器适配器
    template<class T,class Container = std::deque<T>>
    class stack
    {
        public:
        void push(const T& x);

        void pop();
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
class A
{
    public:
    void func1(int i);
    void func2();
};
template<class T,class Container>
void stack<T,Container>::push(const T& x)
{
    con_.push_back(x);
}
template<class T,class Container>
void stack<T,Container>::pop()
{
    con_.pop_back();
}
}

#endif //STACK_QUEUE_STACK_H
