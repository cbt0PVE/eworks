#include"List.h"

ListNode::ListNode(LTDataType x)
	:data_(x), next_(nullptr), prev_(nullptr) {}

ListNode* List::BuyListNode(LTDataType x)
{
	return new ListNode(x);
}
List::List()
{
	head_ = BuyListNode(0);
	head_->next_ = head_;
	head_->prev_ = head_;
}
List::~List()
{
	ListNode* cur = head_->next_;
	while (cur != head_)
	{
		ListNode* next = cur->next_;
		delete cur;
		cur = next;
	}
	delete head_;
	head_ = nullptr;
}

void List::Print()
{
	ListNode* cur = head_->next_;
	std::cout << "List:";
	while (cur != head_)
	{
		std::cout << cur->data_ << " ";
		cur = cur->next_;
	}
	std::cout << std::endl;
}

void List::Insert(ListNode* pos, LTDataType x)
{
	assert(pos != nullptr);
	ListNode* newnode = BuyListNode(x);
	ListNode* prev = pos->prev_;
	prev->next_ = newnode;
	newnode->prev_ = prev;
	newnode->next_ = pos;
	pos->prev_ = newnode;
}

void List::Erase(ListNode* pos)
{
	assert(pos != nullptr && pos != head_);
	ListNode* prev = pos->prev_;
	ListNode* next = pos->next_;
	prev->next_= next;
	next->prev_ = prev;
	delete pos;
}

void List::PushBack(LTDataType x)
{
	Insert(head_, x);
}
void List::PopBack()
{
	Erase(head_->prev_);
}
void List::PushFront(LTDataType x)
{
	Insert(head_->next_, x);
}
void List::PopFront()
{
	Erase(head_->next_);
}
ListNode* List::Find(LTDataType x)
{
	ListNode* cur = head_->next_;
	while (cur != head_)
	{
		if (cur->data_ == x)
			return cur;
		cur = cur->next_;
	}
	return nullptr;
}
