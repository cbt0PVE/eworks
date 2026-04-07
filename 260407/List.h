#pragma once
#ifndef __LIST_H_
#define __LIST_H_

#include <iostream>
#include <cassert>

typedef int LTDataType;

struct ListNode
{
	LTDataType data_;
	ListNode* next_;
	ListNode* prev_;

	ListNode(LTDataType x = 0);
};

class List
{
private:
	ListNode* head_;
	ListNode* BuyListNode(LTDataType x);

public:
	List();
	~List();

	void Print();
	void Insert(ListNode* pos, LTDataType x);
	void Erase(ListNode* pos);

	void PushBack(LTDataType x);
	void PopBack();
	void PushFront(LTDataType x);
	void PopFront();

	ListNode* Find(LTDataType x);
};
#endif