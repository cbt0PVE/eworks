#include<iostream>
#include<cassert>
#include<queue>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
public:
	void preOrder(TreeNode* root)
	{
		if (!root)return;
		cout << root->val << " ";
		preOrder(root->left);
		preOrder(root->right);
	}

	void inOrder(TreeNode* root)
	{
		if (!root)return;
		inOrder(root->left);
		cout << root->val << " ";
		inOrder(root->right);
	}

	void postOrder(TreeNode* root)
	{
		if (!root)return;
		postOrder(root->left);
		postOrder(root->right);
		cout << root->val << " ";
	}

	void levelOrder(TreeNode* root)
	{
		if (!root) return;
		queue<TreeNode*> q;
		q.push(root);

		while (!q.empty())
		{
			auto node = q.front();
			q.pop();
			cout << node->val << " ";

			if (node->left)q.push(node->left);
			if (node->right)q.push(node->right);
		}
		cout << endl;
	}

	int maxDepth(TreeNode* root)
	{
		if (!root)return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}

	int countNodes(TreeNode* root)
	{
		if (!root)return 0;
		return 1 + countNodes(root->left) + countNodes(root->right);
	}

	int countLeaves(TreeNode* root)
	{
		if (!root) return 0;
		if (!root->left && !root->right) return 1;
		return countLeaves(root->left) + countLeaves(root->right);
	}

	int countLevelK(TreeNode* root, int k)
	{
		if (!root || k < 1)return 0;
		if (k == 1)return 1;
		return countLevelK(root->left, k - 1) + countLevelK(root->right, k - 1);
	}

	TreeNode* invertTree(TreeNode* root)
	{
		if (!root) return nullptr;
		swap(root->left, root->right);
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}

	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		if (!q && !p) return true;
		if (!q || !p)return false;
		return q->val == q->val
			&& isSameTree(q->left,p->left)
			&&isSameTree(q->right,p->right);
	}

	void destroy(TreeNode*& root)
	{
		if (!root) return;
		destroy(root->left);
		destroy(root->right);
		delete root;
		root = nullptr;
	}
};

int main()
{
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);

	BinaryTree tree;

	cout << "前序遍历: ";
	tree.preOrder(root); cout << endl;

	cout << "中序遍历: ";
	tree.inOrder(root); cout << endl;

	cout << "后序遍历: ";
	tree.postOrder(root); cout << endl;

	cout << "层序遍历: ";
	tree.levelOrder(root);

	cout << "最大深度: " << tree.maxDepth(root) << endl;
	cout << "总结点数量: " << tree.countNodes(root) << endl;
	cout << "叶子节点数: " << tree.countLeaves(root) << endl;
	cout << "第3层节点数: " << tree.countLevelK(root, 3) << endl;

	// 翻转树
	tree.invertTree(root);
	cout << "翻转后层序遍历: ";
	tree.levelOrder(root);

	// 销毁
	tree.destroy(root);
	return 0;
}