#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

enum Colour{ RED, BLACK };

template<class K,class V>
struct RBTreeNode{
    RBTreeNode* left_;
    RBTreeNode* right_;
    RBTreeNode* parent_;
    pair<K,V> kv_;
    Colour colour_;

    RBTreeNode(const pair<K,V>& kv)
        :kv_(kv)
        ,left_(nullptr)
        ,right_(nullptr)
        ,parent_(nullptr)
        ,colour_(RED)
        {}
};

template<class K,class V>
class RBTree{
public:
    typedef RBTreeNode<K,V> Node;
    bool Insert(const pair<K,V>& kv)
    {
        if(root_ == nullptr)
        {
            root_ = new Node(kv);
            root_->colour_ = BLACK;
            return true;
        }
        Node* parent = nullptr;
        Node* cur = root_;
        while(cur)
        {
            if(kv.first < cur->kv_.first) { parent = cur; cur = cur->left_; }
            else if(kv.first > cur->kv_.first) { parent = cur; cur = cur->right_; }
            else return false;
        }
        Node* new_node = new Node(kv);
        if(kv.first < parent->kv_.first) parent->left_ = new_node;
        else parent->right_ = new_node;
        new_node->parent_ = parent;
        cur = new_node;

        // 调整平衡
        while(parent && parent->colour_ == RED)
        {
            Node* grandparent = parent->parent_;
            if(grandparent == nullptr) break; 

            if(parent == grandparent->left_)
            {
                Node* uncle = grandparent->right_;
                if(uncle && uncle->colour_ == RED)
                {
                    // 情况1
                    parent->colour_ = BLACK;
                    uncle->colour_ = BLACK;
                    grandparent->colour_ = RED;
                    
                    // 修正：成对向上更新
                    cur = grandparent; 
                    parent = cur->parent_;
                }
                else
                {
                    // 情况2：修正判定，cur 是 parent 的右孩子才是折线
                    if(cur == parent->right_)
                    {
                        RotateL(parent);
                        swap(cur, parent); 
                    }
                    // 情况3
                    RotateR(grandparent);
                    grandparent->colour_ = RED;
                    parent->colour_ = BLACK;
                    break; 
                }
            }
            else // parent == grandparent->right_
            {
                Node* uncle = grandparent->left_;
                if(uncle && uncle->colour_ == RED)
                {
                    // 情况1
                    parent->colour_ = BLACK;
                    uncle->colour_ = BLACK;
                    grandparent->colour_ = RED;
                    
                    // 修正：成对向上更新
                    cur = grandparent;
                    parent = cur->parent_;
                }
                else
                {
                    // 情况2：修正判定与旋转对象，cur 是 parent 的左孩子才是折线
                    if(cur == parent->left_)
                    {
                        RotateR(parent); // 修正：是对 parent 右旋，而不是 cur
                        swap(cur, parent); 
                    }
                    // 情况3
                    RotateL(grandparent);
                    grandparent->colour_ = RED;
                    parent->colour_ = BLACK;
                    break; 
                }
            }
        }
        root_->colour_ = BLACK;
        return true;
    }

    bool IsBalance() { return IsBalance(root_); }
    int Height() { return Height(root_); }
    int _rotateCount = 0;

private:
    void RotateL(Node* parent)
    {
        _rotateCount++;
        Node* cur = parent->right_;
        Node* subL = cur->left_;

        parent->right_ = subL;
        if(subL) subL->parent_ = parent;
        cur->left_ = parent;
        Node* pnode = parent->parent_;
        parent->parent_ = cur;
        if(parent == root_)
        {
            root_ = cur;
            cur->parent_ = nullptr;
        }
        else
        {
            if(pnode->left_ == parent) pnode->left_ = cur;
            else pnode->right_ = cur;
            cur->parent_ = pnode;
        }
    }

    void RotateR(Node* parent)
    {
        _rotateCount++;
        Node* cur = parent->left_;
        Node* subR = cur->right_;

        parent->left_ = subR;
        if(subR) subR->parent_ = parent;
        cur->right_ = parent;
        Node* pnode = parent->parent_;
        parent->parent_ = cur;
        if(parent == root_)
        {
            root_ = cur;
            cur->parent_ = nullptr;
        }
        else
        {
            if(pnode->left_ == parent) pnode->left_ = cur;
            else pnode->right_ = cur;
            cur->parent_ = pnode;
        }
    }

    bool IsBalance(Node* node)
    {
        if(node == nullptr) return true;
        if(root_->colour_ != BLACK) return false; // 补充基本校验
        int black_count = 0;
        int benchmark = -1;
        return CheckColour(node, black_count, benchmark);
    }

    bool CheckColour(Node* root, int black_count, int& benchmark)
    {
        if(root == nullptr)
        {
            if(benchmark == -1) benchmark = black_count;
            else return benchmark == black_count;
            return true;
        }
        if (root->colour_ == RED && root->parent_ && root->parent_->colour_ == RED)
        {
            cout << "错误：节点 " << root->kv_.first << " 与其父节点连续为红！" << endl;
            return false;
        }
        if(root->colour_ == BLACK) black_count++;
        return CheckColour(root->left_, black_count, benchmark) && CheckColour(root->right_, black_count, benchmark);
    }

    int Height(Node* node)
    {
        if(node == nullptr) return 0;
        int left_height = Height(node->left_);
        int right_height = Height(node->right_);
        return max(left_height, right_height) + 1;
    }
    Node* root_ = nullptr;
};