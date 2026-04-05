#include<iostream>

using namespace std;

//leetcode 206
class Solution1
{
public:
	ListNode* reverseList(ListNode* head)
	{
		ListNode* prev = nullptr;
		ListNode* cur = head;
		while (cur != nullptr)
		{
			ListNode* nextTemp = cur->next;
			cur->next = prev;               
			prev = cur;                     /
			cur = nextTemp;
		}
		return prev;
	}
	
};

//leetcode 876
class Solution2
{
public:
	ListNode* middleNode(ListNode* head)
	{
		ListNode* fast = head;
		ListNode* slow = head;
		while (fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}
};

//leetcode √Ê ‘ 02.02
class Solution3
{
public:
	int KthToLast(ListNode* head, int k)
	{
		ListNode* fast = head;
		ListNode* slow = head;
		for (int i = 0; i < k; i++)
		{
			fast = fast->next;
		}
		while (fast != nullptr)
		{
			slow = slow->next;
			fast = fast->next;
		}
		return slow->val;
	}
};

//leetcode 21
class Solution
{
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
	{
		ListNode* dummy = new ListNode(-1);
		ListNode* cur = dummy;
		
		while (list1 != nullptr && list2 != nullptr)
		{
			if (list1->val <= list2->val)
			{
				cur->next = list1;
				list1 = list1->next;
			}
			else
			{
				cur->next = list2;
				list2 = list2->next;
			}
			cur = cur->next;
		}
		cur->next = (list1 != nullptr) ? list1 : list2;
		return dummy->next;
	}
};