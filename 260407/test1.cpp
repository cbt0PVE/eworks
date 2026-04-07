#include<iostream>
#include<unordered_map>
using namespace std;
struct ListNode1 {
	int val;
	ListNode1* next;
	ListNode1(int x) : val(x), next(NULL) {}
};

//leetcode 142
class Solution1
{
public:
	ListNode1* detectCycle(ListNode1* head)
	{
		if (head == nullptr || head->next == nullptr)
		{
			return nullptr;
		}
		ListNode1* slow = head;
		ListNode1* fast = head;

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
	Node* copyRandomList(Node* head)
	{
		if (!head)
			return nullptr;

		std::unordered_map<Node*, Node*> map;
		Node* cur = head;

		while (cur)
		{
			map[cur] = new Node(cur->val);
			cur = cur->next;
		}

		cur = head;
		while (cur)
		{
			map[cur]->next = map[cur->next];
			map[cur]->random = map[cur->random];
			cur = cur->next;
		}

		return map[head];
	}
};

//