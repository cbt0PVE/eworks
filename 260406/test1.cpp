#include<iostream>

using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Partition
{
public:
    ListNode* partition(ListNode* pHead, int x)
    {
        ListNode lessHead(0);
        ListNode greaterHead(0);
        ListNode* less = &lessHead;
        ListNode* greater = &greaterHead;

        ListNode* cur = pHead;
        while (cur != nullptr)
        {
            if (cur->val < x)
            {
                less->next = cur;
                less = less->next;
            }
            else
            {
                greater->next = cur;
                greater = greater->next;
            }
            cur = cur->next;
        }
        less->next = greaterHead.next;
        greater->next = nullptr;

        return lessHead.next;
    }
};

class PalindromeList {
public:
    bool chkPalindrome(ListNode* A)
    {
        if (A == nullptr || A->next == nullptr)
            return true;

        ListNode* slow = A;
        ListNode* fast = A;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* prev = nullptr;
        ListNode* cur = slow;
        while (cur != nullptr)
        {
            ListNode* nextTemp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nextTemp;
        }
        ListNode* left = A;
        ListNode* right = prev;
        while (right != nullptr)
        {
            if (left->val != right->val)
                return false;
            left = left->next;
            right = right->next;
        }
        return true;
    }
};

//leetcode 160
class Solution1
{
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        if (headA == nullptr || headB == nullptr)
        {
            return nullptr;
        }
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        while (p1 != p2)
        {
            p1 = (p1 != nullptr) ? p1->next : headB;
            p2 = (p2 != nullptr) ? p2->next : headA;
        }
        return p1;
    }
};

//leetcode 141
class Solution
{
public:
    bool hasCycle(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr)
            return false;
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                return true;
            }
        }
        return false;
    }
};