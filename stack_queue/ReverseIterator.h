#pragma once
namespace helta
{
    template<class T,class Ref,class Ptr>
    struct ReverseIterator
    {
        typedef ReversrIterator<T,Ref,Ptr> Self;
        Iterator it_;

        ReverseIterator(Iterator it)
            :it_(it)
            {}
        Ref operator*()
        {
            Iterator tmp = it_;
            return *(--tmp);
        }
        Ptr operator->()
        {
            return &(operator*());
        }
        Self& operator++()
        {
            --it_;
            return *this;
        }
        Self operator--()
        {
            ++it_;
            return *this;
        }
        bool operator!=(const Self& s)
        {
            return it != s.it_;
        }
    };
}