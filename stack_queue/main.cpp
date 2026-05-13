#include <iostream>
#include <vector>
#include "Queue.h"
#include"Stack.h"
#include<deque>
using namespace std;
//leetcode 036
/*class Solution
{
public:
    int evalRPN(vector<string>& tokens)
    {
        stack<int> st;
        for (auto str : tokens)
        {
            if (str == "+"||str == "-" || str == "*" || str == "/") {
                int right = st.top();
                st.pop();

                int left = st.top();
                st.pop();
                switch (str[0]) {
                    case '+':
                        st.push(left + right);
                        break;
                    case '-':
                        st.push(left - right);
                        break;
                        case '*':
                        st.push(left * right);
                        break;
                        case '/':
                        st.push(left / right);
                        break;

                }

            }
            else {
                st.push(stoi(str));
            }


        }
    return st.top();
    }
};*/
//leetcode 102
/*struct TreeNode {
        int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
class Solution {
public:
    vector< vector<int> > levelOrder(TreeNode* root) {
        vector< vector<int> > vv;
    queue<TreeNode*> q;
        int levelSize = 0;

        if (root) {
            q.push(root);
            levelSize = 1;
        }

        while (!q.empty()) {
            vector<int> v;
            for (int i = 0; i < levelSize; i++) {
                TreeNode* front = q.front();
                q.pop();

                v.push_back(front->val);
                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
            vv.push_back(v);
            levelSize = q.size();
        }

        return vv;
    }
};*/
void test_stack_queue() {

}
int main()
{
    return 0;
}