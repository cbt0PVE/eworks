#pragma once
#include<iostream>
#include<cassert>
#include<algorithm>
using namespace std;

template<class K,class V>
struct AVLNode{
    pair<K,V> kv_;
    AVLNode<K,V>* left_;
    AVLNode<K,V>* right_;
    AVLNode<K,V>* parent_;
    int height_;
    AVLNode(const pair<K,V>& kv)
        :kv_(kv)
        ,left_(nullptr)
        ,right_(nullptr)
        ,parent_(nullptr)
        ,height_(1)
        {}      
};

template<class K,class V>
class AVLTree{
    typedef AVLNode<K,V> Node;
public:
    bool Insert(const pair<K,V>& kv)
    {
        if(root_ == nullptr)
        {
            root_ = new Node(kv);
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

        // 调整平衡
        while(parent)
        {
            int old_height = parent->height_;
            UpdateHeight(parent);
            int balance_factor = GetBalanceFactor(parent);

            // 高度法安全且优雅的自平衡判定（左高 - 右高）
            if(balance_factor == 2 || balance_factor == -2)
            {
                if(balance_factor == 2 && GetBalanceFactor(parent->left_) == 1)
                {
                    RotateR(parent);
                }
                else if(balance_factor == -2 && GetBalanceFactor(parent->right_) == -1)
                {
                    RotateL(parent);
                }
                else if(balance_factor == 2 && GetBalanceFactor(parent->left_) == -1)
                {
                    RotateLR(parent);
                }
                else if(balance_factor == -2 && GetBalanceFactor(parent->right_) == 1)
                {
                    RotateRL(parent);
                }
                break; // 只要发生过旋转，子树高度完美恢复，直接退出
            }

            if(parent->height_ == old_height)
            {
                break; // 如果高度没发生任何改变，说明没有向上引发多米诺反应，安全退出
            }

            parent = parent->parent_;
        }
        return true;
    }

    bool IsBalance() { return IsBalance(root_); }
    int Height(){ return GetHeight(root_); }
    int _rotateCount = 0;

private:
    int GetHeight(Node* node){ return node ? node->height_ : 0; }
    
    void UpdateHeight(Node* node)
    {
        if(node)
        {
            int left_height = GetHeight(node->left_);
            int right_height = GetHeight(node->right_);
            node->height_ = max(left_height, right_height) + 1;
        }
    }
    
    int GetBalanceFactor(Node* node)
    {
        return node ? GetHeight(node->left_) - GetHeight(node->right_) : 0;
    }

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
        UpdateHeight(parent);
        UpdateHeight(cur);
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
        UpdateHeight(parent);
        UpdateHeight(cur);
    }

    void RotateLR(Node* parent)
    {
        RotateL(parent->left_);
        RotateR(parent);
    }
    void RotateRL(Node* parent)
    {
        RotateR(parent->right_);
        RotateL(parent);
    }

    bool IsBalance(Node* node)
    {
        if(node == nullptr) return true;
        int balance_factor = GetBalanceFactor(node);
        if(balance_factor > 1 || balance_factor < -1) return false;
        return IsBalance(node->left_) && IsBalance(node->right_);
    }
    Node* root_ = nullptr;
};