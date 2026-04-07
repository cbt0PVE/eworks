#include<iostream>
#include<unordered_map>
using namespace std;
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};
//leetcode 142
class Solution1
{
public:
	ListNode* detectCycle(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr)
		{
			return nullptr;
		}
		ListNode* slow = head;
		ListNode* fast = head;

		while (fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)
			{
				break;
			}
		}
		if (fast == nullptr || fast->next == nullptr)
		{
			return nullptr;
		}
		slow = head;
		while (slow != fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
		return slow;
	}
};


class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};
//leetcode 138
class Solution
{
public:
	Node* copyRondomList(L)
};