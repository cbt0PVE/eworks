#pragma once
#include<cassert>
namespace helta
{
	template<class T>
	struct list_node
	{
		list_node<T>* next_;
		list_node<T>* prev_;
		T val_;

		list_node(const T& val = T())
			:next_(nullptr)
			,prev_(nullptr)
			,val_(val)
		{}
	};

	template <class T,class Ref,class Ptr>
	struct ListIterator
	{
		//typedef list_node<T> Node;
		using Node = list_node<T>;
		typedef ListIterator<T, Ref,Ptr> self;
		Node* node_;

		ListIterator(Node* node)
			:node_(node)
		{}
		//不需要析构函数

		 Ref operator*()
		{
			return node_->val_;
		}
		Ptr operator->()
		 {
			 return &node_->val_;
		 }
		self& operator++()
		{
			node_ = node_->next_;
			return *this;
		}
		self operator++(int)
		{
			self tmp(*this);
			node_ = node_->next_;
			return tmp;
		}
		self& operator--()
		{
			node_ = node_->prev_;
			return *this;
		}
		self operator--(int)
		{
			self tmp(*this);
			node_ = node_->prev_;
			return tmp;
		}
		bool operator!=(const self& it) const
		{
			return node_ != it.node_;
		}

		bool operator==(const self& it) const
		{
			return node_ == it.node_;
		}
	};

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef ListIterator<T,T&,T*> iterator;
		typedef ListIterator<T,const T&,const T*> const_iterator;
		//如何设计const 迭代器

		iterator begin()
		{
			return head_->next_;
			//return iterator(head_->next_)
			//单参数的函数支持隐式类型的转换
		}

		iterator end()
		{
			return head_;
		}
		const_iterator begin() const
		{
			return head_->next_;
			//return iterator(head_->next_)
			//单参数的函数支持隐式类型的转换
		}

		const_iterator end()const
		{
			return head_;
		}
		void empty_init()
		{
			head_ = new Node;
			head_->prev_ = head_;
			head_->next_ = head_;
		}
		list()
		{
			empty_init();
		}

		list(const list<T>& lt)
		{
			empty_init();
			for (auto& e : lt)
			{
				push_back(e);
			}
		}

		void swap(list<T>& lt)
		{
			std::swap(head_, lt.head_);
			std::swap(size_, lt.size_);
		}
		list<T>& operator=(list<T> lt)
		//list& operator=(list lt)
		{
			swap(lt);
			return *this;
		}
		~list()
		{
			clear();
			delete head_;
			head_ = nullptr;
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}
		void push_back(const T& x)
		{
			/*Node* tail = head_->prev_;
			Node* newnode = new Node(x);

			tail->next_ = newnode;
			newnode->prev_ = tail;

			newnode->next_ = head_;
			head_->prev_ = newnode;*/
			insert(end(), x);
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos.node_;
			Node* prev = cur->prev_;
			Node* newnode = new Node(x);

			prev->next_ = newnode;
			newnode->next_ = cur;

			cur->prev_ = newnode;
			newnode->prev_ = prev;

			return newnode;
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* cur = pos.node_;
			Node* prev = cur->prev_;
			Node* next = cur->next_;

			prev->next_ = next;
			next->prev_ = prev;

			delete cur;
			return next;
		}
		//或者增加一个成员
		size_t size()
		{
			size_t sz = 0;
			iterator it = begin()
				while (it != end())
				{
					++sz;
					++it;
				}
			return sz;
		}
	private:
		Node* head_;
			
	};
	void Print(const list<int>& lt)
	{
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	void test_list1()
		{
			list<int> lt;
			lt.push_back(1);
			lt.push_back(2);
			lt.push_back(3);
			lt.push_back(4);

			list<int>::iterator it = lt.begin();
			while (it != lt.end())
			{
				cout << *it << " ";
				++it;
			}
			cout << endl;

			for (auto e : lt)
			{
				cout << e << " ";
			}
			cout << endl;
		}
}
