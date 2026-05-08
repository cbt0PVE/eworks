#pragma once
#include<iostream>
#include<cassert>
using namespace std;
namespace bit
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const  T* const_iterator;

		T& operator[](size_t pos)
		{
			assert(pos < size());

			return start_[pos];
		}
		iterator begin()
		{
			return start_;
		}
		iterator end()
		{
			return finish_;
		}
		const_iterator begin()const
		{
			return start_;
		}
		const_iterator end()const
		{
			return finish_;
		}
		vector()
			:start_(nullptr),
			finish_(nullptr),
			end_of_storage_(nullptr)
		{}

		vector(const vector<T>& V)
			:start_(nullptr),
			finish_(nullptr),
			end_of_storage_(nullptr)
		{
			start_ = new T[v.capacity()];
			//memcpy 会导致string 的浅拷贝
			//memcpy(start_, v.start_,sizeof(T)*v.size());
			//解决方案：T是string这样深拷贝的类，调用的是string赋值重载，实现的string对象的深拷贝
			for(size_t i = 0; i < sz; i++)
			{
				start_[i] = v.start_[i];
			}
			finish_ = start_ + v.size();
			end_of_storage_ = start_ + v.capacity();
		}
		void swap(vector<T>& v)
		{
			std::swap(start_, v.start_);
			std::swap(finish_, v.finish_);
			std::swap(end_of_storage_,v.end_of_storage_)；
		}

		vector<T>& operator=(vector<T> v)
		{
			swap(v);

			return *this;
		}

		~vector()
		{
			if (start_)
			{
				delete[] start_;
				start_ = finish_ = end_of_storage_ = nullptr;
			}
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (start_)
				{
					//memcpy(tmp, start_, sizeof(T) * size());
					for (size_t i = 0; i < v.size(); i++)
					{
						tmp[i] = start_[i];
					}
					delete[] start_;
				}
				
				start_ = tmp;
				finish_ = sz + start_;
				end_of_storage_ = start_ + n;
			}
		}
		void push_back(const T& x)
		{
			/*if (finish_ == end_of_storage_)
			{
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}

			*finish_ = x;
			++finish_;*/
			insert(end(), x);
		}

		void pop_back()
		{
			erase(--end());
		}

		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				finish_ = start_ + n;
			}
			else
			{
				reverse(n);
				while (finish_ != start_ + n)
				{
					*finish_ = val;
					++finish_;
				}
			}
		}

		size_t capacity()const
		{
			return end_of_storage_ - start_;
		}

		size_t size() const
		{
			return finish_ - start_;
		}

		T& opeartor[](size_t pos)
		{
			assert(pos < size());

			return start_[pos];
		}

		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return start_[pos];
		}

		iteartor insert(iterator pos, const T& x)
		{
			assert(pos >= start_ && pos <= finish_);
			if (finish_ == end_of_storage_)
			{
				size_t len = pos - start_;

				size_t newcapacity = caacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
				//解决pos迭代器失效问题
				pos = start_ + len;
			}
			iterator end = finish_ - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}

			*pos = x;
			++finish;

			return pos;
		}
		//扩容仍然可能引起失效
		//insert以后就不要用这个形参迭代器了，因为他可能失效了。

		iterator erase(iterator pos)
		{
			assert(pos > -start_ && pos < finish_);

			iterator it = pos + 1;
			while (it != finish_)
			{
				*(it - 1) = *it;
				it++;
			}
			--finish_;

			return pos;
		}

	private:
		iterator start_;
		iterator finish_;
		iterator end_of_storage_;
	};

	void print(const vector<int>& v)
	{
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	/*void test_vector1()
	{
		bit::vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
		for (size_t i = 0; i < v1.size(); i++)
		{
			v1[i]++;
		}for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		auto it = v1.begin();
		while (it != v1.end())
		{
			if(*it % 2 == 0)
			{
				it = v1.erase(it);
			}
			else
			{
				++it;
			}
		}
	}*/
}