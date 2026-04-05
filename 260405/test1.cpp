#include<iostream>
using namespace std;

typedef int SLTDataType;

typedef struct SListNode
{
	SLTDataType data;
	SListNode* next;

	SListNode(SLTDataType x)
		:data(x), next(nullptr) {}
}SLNode,*pSLNode;

void SListPrint(pSLNode plist)
{
	pSLNode cur = plist;
	while (cur)
	{
		cout << cur->data << "->";
		cur = cur->next;
	}
	cout << "nullptr" << endl;
}

void SListPushBack(pSLNode& pplist,SLTDataType x)
{
	pSLNode newnode = new SListNode(x);
	if (!pplist)
	{
		pplist = newnode;
		return;
	}
	pSLNode tail = pplist;
	while (tail->next)
		tail = tail->next;
	tail->next = newnode;
}

void SListPushFront(pSLNode& pplist, SLTDataType x)
{
	pSLNode newnode = new SListNode(x);
	newnode->next = pplist;
	pplist = newnode;
}

void SListPopBack(pSLNode& pplist)
{
	if (!pplist)
		return;
	if (!pplist->next)
	{
		delete pplist;
		pplist = nullptr;
		return;
	}
	pSLNode tail = pplist;
	while (tail->next->next)
		tail = tail->next;
	delete tail->next;
	tail->next = nullptr;
}

void SListPopFront(pSLNode& pplist)
{
	if (!pplist)
		return;
	pSLNode next = pplist->next;
	delete pplist;
	pplist = next;
}

SLNode* SListFind(pSLNode plist, SLTDataType x)
{
	pSLNode cur = plist;
	while (cur)
	{
		if (cur->data == x)
			return cur;
		cur = cur->next;
	}
	return nullptr;
}

void SListInsertAfter(pSLNode pos, SLTDataType x)
{
	if (!pos)
		return;
	pSLNode newnode = new SListNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}

void SListEraseAfter(pSLNode pos)
{
	if (!pos || !pos->next)
		return;
	pSLNode del = pos->next;
	pos->next = del->next;
	delete del;
}

void SListInsert(pSLNode& pplist, pSLNode pos, SLTDataType x)
{
	if (!pos || pos == pplist)
	{
		SListPushFront(pplist, x);
		return;
	}
	pSLNode prev = pplist;
	while (prev->next != pos)
		prev = prev->next;
	pSLNode newnode = new SListNode(x);
	newnode->next = pos;
	prev->next = newnode;
}

void SListErase(pSLNode& pplist, pSLNode pos)
{
	if (!pplist || !pos)
		return;
	if (pplist == pos)
	{
		SListPopFront(pplist);
		return;
	}
	pSLNode prev = pplist;
	while (prev->next != pos)
		prev = prev->next;
	prev->next = pos->next;
	delete pos;
}

void SListDestroy(pSLNode& plist)
{
	pSLNode cur = plist;
	while (cur)
	{
		pSLNode next = cur->next;
		delete cur;
		cur = next;
	}
	plist = nullptr;
}
//LeetCode ÒÆ³ýÁ´±íÔªËØ
//class Solution
//{
//public:
//	ListNode* removeElements(ListNode* head, int val)
//	{
//		ListNode* dummy = new ListNode(0);
//		dummy->next = head;
//
//		ListNode* cur = dummy;
//		while (cur->next != nullptr)
//		{
//			if (cur->next->val == val)
//			{
//				ListNode* del = cur->next;
//				cur->next = del->next;
//				delete del;
//			}
//			else
//				cur = cur->next;
//		}
//		ListNode* newHead = dummy->next;
//		delete dummy;
//		return newHead;
//	}
//	
//};
//test
int main()
{
	pSLNode head = nullptr;
	{
		SListPushBack(head, 1);
		SListPushBack(head, 2);
		SListPushBack(head, 3);
		SListPrint(head);//1->2->3->nullptr

		SListPushFront(head, 0);
		SListPrint(head);//0->etc.

		pSLNode pos = SListFind(head, 2);
		SListInsertAfter(pos, 22);
		SListPrint(head);//0->1->2->22->3->nullptr

		SListEraseAfter(pos);
		SListPrint(head);//0->etc.

		SListErase(head, pos);
		SListPrint(head);//0->etc.(exceot 2)

		SListPopBack(head);
		SListPopFront(head);
		SListPrint(head);//1->nullptr

		SListDestroy(head);
		return 0;
	}
}