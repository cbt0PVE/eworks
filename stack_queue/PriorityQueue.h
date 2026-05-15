#include<vector>
#include<functional>

//仿函数/函数对象
template<class T>
class Less
{
    public:
    bool operator()(const T& left,const T& right)
    {
        return left < right;
    }
};

template<class T>
class Greater
{
public:
	bool operator()(const T& x, const T& y)
	{
		return x > y;
	}
};

namespace helta
{
    template<class T, class Container = std::vector<T>, class Compare = std::less<T>>
    class priority_queue
    {
        private:
        void AdjustDown(int parent)
        {
            size_t child = parent * 2 + 1;
            while(child < con_.size())
            {
                if(child + 1 < con_.size() && Compare()(con_[child], con_[child + 1]))
                {
                    ++child;
                }
                if(Compare()(con_[parent], con_[child]))
                {
                    std::swap(con_[parent], con_[child]);
                    parent = child;
                    child = parent * 2 + 1;
                }
                else
                {
                    break;
                }
            }
        }
        void AdjustUp(int child)
        {
            int parent = (child - 1) / 2;
            while(child > 0)
            {
                if(Compare()(con_[parent], con_[child]))
                {
                    std::swap(con_[parent], con_[child]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }
        public:
        priority_queue()
        {}
        template<class InputIterator>
        priority_queue(InputIterator first, InputIterator last)
        {
            while(first != last)
            {
                con_.push_back(*first);
                ++first;
            }
            for(int i = (int(con_.size()) - 2) / 2; i >= 0; --i)
            {
                AdjustDown(i);
            }
        }
        void pop()
        {
            std::swap(con_[0], con_[con_.size() - 1]);
            con_.pop_back();
            AdjustDown(0);
        }

        void push(const T& x)
        {
            con_.push_back(x);
            AdjustUp(con_.size() - 1);
        }
        const T& top()
        {
            return con_[0];
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
}
