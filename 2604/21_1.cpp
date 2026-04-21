#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
//leetcode 104
class Solution104 {
public:
    int maxDepth(TreeNode* root)
    {
        if (root == nullptr) return 0;

        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }
};

//leetcode 226
class Solution226 {
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (root == nullptr)return nullptr;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode* node = q.front();
            q.pop();
            swap(node->left, node->right);
            if (node->left) q.push(node->left);
            if (node->right)q.push(node->right);
        }
        return root;
    }
};

//leetcode 100
class Solution100 {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) 
    {
        if (p == nullptr && q == nullptr)return true;
        if (q == nullptr || p == nullptr)return false;
        if (p->val != q->val)return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

//leetcode 144
class Solution144
{
public:
    vector<int> preorderTraversal(TreeNode* root)
    {
        vector<int> res;
        if (!root) return res;

        stack<TreeNode*> stk;
        stk.push(root);

        while (!stk.empty())
        {
            TreeNode* node = stk.top();
            stk.pop();
            res.push_back(node->val);
            if (node->right)stk.push(node->right);
            if (node->left)stk.push(node->left);
        }
        return res;
    }
};

//leetcode 101
class Solution101 {
public:
    bool isSymmetric(TreeNode* root)
    {
        if (!root)return true;
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);

        while (!q.empty())
        {
            TreeNode* left = q.front(); q.pop();
            TreeNode* right = q.front(); q.pop();

            if (!left && !right)continue;
            if (!left || !right || left->val != right->val)return false;

            q.push(left->left);
            q.push(right->right);
            q.push(left->right);
            q.push(right->left);
        }
        return true;
    }
};

//leetcode 572
class Solution572 
{
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) 
    {
        if (!subRoot)return true;
        if (!root)return false;
        return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
private:
    bool isSameTree(TreeNode* q, TreeNode* p)
    {
        if (!q && !p)return true;
        if (!q || !p)return false;
        if (p->val != q->val) return false;

        return isSameTree(q->left, p->left) && isSameTree(q->right, p->right);
    }
};

//TSINGK110 
//#include <iostream>
//#include<string>
//using namespace std;
//
//struct TreeNode
//{
//    char val;
//    TreeNode* left;
//    TreeNode* right;
//    TreeNode(char c) :val(c), left(nullptr), right(nullptr) {}
//};
//TreeNode* buildTree(const string& s, int& index)
//{
//    if (index >= s.size() || s[index] == '#')
//    {
//        ++index;
//        return nullptr;
//    }
//    TreeNode* root = new TreeNode(s[index]);
//    index++;
//    root->left = buildTree(s, index);
//    root->right = buildTree(s, index);
//    return root;
//}
//
//void inorderTraversal(TreeNode* root)
//{
//    if (!root)return;
//    inorderTraversal(root->left);
//    cout << root->val << " ";
//    inorderTraversal(root->right);
//}
//
//void destroyTree(TreeNode* root)
//{
//    if (!root)return;
//    destroyTree(root->left);
//    destroyTree(root->right);
//    delete root;
//}
//
//int main()
//{
//    string s;
//    while (cin >> s)
//    {
//        int index = 0;
//        TreeNode* root = buildTree(s, index);
//        inorderTraversal(root);
//        cout << endl;
//        destroyTree(root);
//    }
//    return 0;
//}

