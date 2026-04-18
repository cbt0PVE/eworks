#include<iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	bool isUnivalTree(TreeNode* root)
	{
		if (!root)return true;
		int val = root->val;
		return check(root, val);
	}
private:
	bool check(TreeNode* node, int target)
	{
		if (!node) return true;
		if (node->val != target)return false;
		return check(node->left, target) && check(node->right, target);
	}
};