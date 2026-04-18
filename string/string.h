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
			//strcpy(str_, str);
			memcpy(str_, str,size_ +1);
		}

		string(const string& s)
		{
			str_ = new char[s.capacity_ + 1];
			//strcpy(str_, s.str_);
			memcpy(str_, s.str_,s.size_ +1);
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
				//strcpy(tmp, str_);
				memcpy(tmp, str_, size_ + 1);
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

			//strcpy(str_ + size_, str);
			memcpy(str_ + size_, str, len + 1);
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
			memcpy(str_, str.str_,len +1);
			return *this;
		}

		
		void resize(size_t n,char ch = '\0')
		{
			if (n < size_)
			{
				size_ = n;
				str_[size_] = '\0';
			}
			else
			{
				reserve(n);
				for (size_t i = size_; i < n; i++)
				{
					str_[i] = ch;
				}
				size_ = n;
				str_[size_] = '\0';
			}
		}

		void clear()
		{
			str_[0] = '\0';
			size_ = 0;
		}

		//bool operator<(const string& s)
		//{
		//	size_t i = 0;
		//	size_t j = 0;
		//	while (i < size_ && j < s.size_)
		//	{
		//		if (str_[i] < str_[j])
		//		{
		//			return true;
		//		}
		//		else if (str_[i] > s.str_[j])
		//			return false;
		//		else
		//		{
		//			++i;
		//			++j;
		//		}
		//	}
		//	//return i == size_ && j != s.size_;
		//	return size_ < s.size_;
		//}

		bool operator<(const string& s)const
		{
			int ret = memcmp(str_, s.str_, size_ < s.size_ ? size_ : s.size_);

			return ret == 0 ? size_ < size_ < s.size_ : ret < 0;
		}

		bool operator==(const string& s)const
		{
			return size_ == s.size_ &&
				memcmp(str_, s.str_, size_) == 0;
		}

		bool operator<=(const string& s)const
		{
			return *this < s || *this == s;
		}

		bool operator>(const string& s)const
		{
			return !(*this <= s);
		}

		bool operator>=(const string& s)const
		{
			return !(*this < s);
		}

		bool operator!=(const string& s)const
		{
			return !(*this == s);
		}



	private:
		size_t size_;
		size_t capacity_;
		char* str_;


		const static size_t npos;
		//const static size_t npos = -1;???
		//const static double x = 1.1;????
		//inline static double x = 1.1;
	};

	const size_t string::npos = -1;
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}

	istream& operator>>(istream& in, string& s)
	{
		s.clear();
		char ch = in.get();
		//处理缓冲区前
		while (ch == ' ' || ch == '\n')
		{
			ch = in.get();
		}
		char buffer[128];
		int i = 0;
		//in >> ch;
		while (ch != ' ' && ch != '\n')
		{
			//s += ch;
			// 扩容调用太多
			buffer[i++] = ch;
			if (i == 127)
			{
				buffer[i] = '\0';
				s += buffer;
				i = 0;
			}

			//in >> ch;
			ch = in.get();
		}
		if (i != 0)
		{
			buffer[i] = '\0';
			s += buffer;
		}
		return in;
	}
};
