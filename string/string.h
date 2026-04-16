#pragma once
#include<cassert>
namespace bit
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return str_;
		}

		iterator end()
		{
			return str_ + size_;
		}

		const_iterator begin()const
		{
			return str_;
		}

		const_iterator end()const
		{
			return str_ + size_;
		}

		/*string()
			:size_(0)
			,capacity_(0)
			,str_(new char[1])
		{
			str_[0] = '\0';
		}
		string(const char* str)
			:size_(strlen(str))
			, capacity_(size_)
			,str_(new char[capacity_ + 1]) 
		{
			strcpy(str_, str);
		}*/
		string(const char* str = "")
		{
			size_=strlen(str);
			capacity_ = size_;
			str_ = new char[capacity_ + 1];
			strcpy(str_, str);
		}

		string(const string& s)
		{
			str_ = new char[s.capacity_ + 1];
			strcpy(str_, s.str_);
			size_ = s.size_;
			capacity_ = s.capacity_;
		}

		~string()
		{
			delete[] str_;
			str_ = nullptr;
			size_ = capacity_ = 0;
		}

		const char* c_str() const
		{
			return str_;
		}

		size_t size() const
		{
			return size_;
		}

		char& operator[](size_t pos)
		{
			assert(pos < size_);
			return str_[pos];
		}

		const char& operator[](size_t pos)const
		{
			assert(pos < size_);

			return str_[pos];
		}

		void reserve(size_t n)
		{
			if (n > capacity_)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, str_);
				delete[] str_;
				str_ = tmp;
				capacity_ = n;
			}
		}

		void push_back(char ch)
		{
			if (size_ == capacity_)
			{
				reserve(capacity_ == 0? 4:capacity_ * 2);
			}
			str_[size_] = ch;
			++size_;
			str_[size_] = '\0';
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			if (size_ + len > capacity_)
			{
				reserve(size_ + len);
			}

			strcpy(str_ + size_, str);
			size_ += len;
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		void insert(size_t pos,size_t n,char ch)
		{
			assert(pos <= size_);

			if (size_ + n > capacity_)
				reserve(size_ + n);

			size_t end = size_;
			//while (end >= pos)
			//{
			//	str_[end + n] = str_[end];
			//	--end;
			//	//如果pos = o?,end = -1,整型提升。
			//}
			//方法一
			/*while (end >= (int)pos)
			{
				str_[end + n] = str_[end];
				--end;
			}*/
			//方法二
			while (end >= pos && end != npos)
			{
				str_[end + n] = str_[end];
				--end;
			}

			for (size_t i = 0; i < n; i++)
			{
				str_[pos + i] = ch;
			}
			size_ += n;
		}

		void insert(size_t pos, const char* str)
		{
			assert(pos <= size_);
			size_t len = strlen(str);
			if (size_ + len > capacity_)
				reserve(size_ + len);
			size_t end = size_;
			while (end >= pos && end != npos)
			{
				str_[end + len] = str_[end];
				--end;
			}

			for (size_t i = 0; i < len; i++)
			{
				str_[pos + i] = str[i];
			}
			size_ += len;
		}
		void erase(size_t pos,size_t len = npos)
		{
			assert(pos <= size_);
			if (len == npos || pos + len >= size_)
			{
				str_[pos] = '\0';
				size_ = pos;
				str_[size_] = '\0';
			}
			else
			{
				size_t end = pos + len;
				while (end <= size_)
				{
					str_[pos++] = str_[end++];
				}
				str_ -= len;
			}
		}

		size_t find(char ch,size_t pos = 0)
		{
			assert(pos < size_);
			for (size_t i = pos; i < size_; i++)
			{
				if (str_[i] == ch)
				{
					return i;
				}
			}

			return npos;
		}

		size_t find(const char* str, size_t pos = 0)
		{
			assert(pos < size_);
			const char* ptr = strstr(str_ + pos, str);
			if (ptr)
				return ptr - str_;
			else
			return npos;
		}

		string substr(size_t pos = 0, size_t len = npos)const
		{
			assert(pos < size_);
			size_t n = len;
			if (len == npos || pos + len > size_)
			{
				n = size_ - pos;
			}
			string tmp;
			tmp.reserve(n);
			for (size_t i = pos; i < n + pos; i++)
			{
				tmp += str_[i];
			}

			return tmp;
		}

		string& operator=(const string& str)
		{
			if (this == &str)
			{
				return *this;
			}
			delete[] str_;

			size_t len = strlen(str.str_);
			str_ = new char[len + 1];
			strcpy(str_, str.str_);
			return *this;
		}



	private:
		size_t size_;
		size_t capacity_;
		char* str_;


		const static size_t npos;
		//const static size_t npos = -1;???
		//const static double x = 1.1;????
	};

	const size_t string::npos = -1;
};