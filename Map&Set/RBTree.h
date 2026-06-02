#pragma once
#include<iostream>
using namespace std;

enum Colour { RED,BLACK };
template<typename T>
struct Node
{
    Node<T>* left_;
    Node<T>* right_;
    Node<T>* parent_;
    T data_;
    Colour colour_;
    Node(const T& data)
        :left_(nullptr)
        ,right_(nullptr)
        ,parent_(nullptr)
        ,data_(data)
        ,colour_(RED)
        {}
};

template<class T,class Ptr,class Ref>
struct RBTreeIterator
{
    typedef Node<T> Node;
    typedef RBTreeIterator<T,Ptr,Ref> Self;
    typedef RBTreeIterator<T,T*,T&> iterator;
    typedef RBTreeIterator<T,const T*,const T&> const_iterator;
    RBTreeIterator(const iterator& it)
        :node_(it.node_)
    {}
    Node* node_;
    RBTreeIterator(Node* node)
        :node_(node)
    {}
    Ref operator*()
    {
        return node_->data_;
    }
    Ptr operator->()
    {
        return &(node_->data_);
    }
    bool operator != (const Self& it)
    {
        return node_ != it.node_;
    }
    bool operator == (const Self& it)
    {
        return node_ == it.node_;
    }
    Self& operator--()
    {
        if(node_->left_)
        {
            Node* subRight = node_->left_;
            while(subRight->right_)
            {
                subRight = subRight->right_;
            }
            node_ = subRight;
        }
        else
        {
            Node* cur = node_;
            Node* parent = node_->parent_;
            while(parent && cur == parent->left_)
            {
                cur = cur->parent_;
                parent = parent->parent_;
            }
            node_ = parent;
        }
        return *this;
    }
    Self& operator++()
    {
        if(node_->right_)
        {
            Node* subLeft = node_->right_;
            while(subLeft->left_)
            {
                subLeft = subLeft->left_;
            }
            node_ = subLeft;
        }
        else
        {
            Node* cur = node_;
            Node* parent = node_->parent_;
            //找孩子是父亲左子树的结点
            while(parent && cur == parent->right_)
            {
                cur = cur->parent_;
                parent = parent ->parent_;
            }
            node_ = parent;
        }
        return *this;
    }
};

template<class K,class T,class KeyOfT>
class RBTree
{
    typedef Node<T> Node;
    public:
    typedef RBTreeIterator<T,T*,T&> iterator;
    typedef RBTreeIterator<T,const T*,const T&> const_iterator;

    iterator begin()
    {
        Node* leftMin = root_;
        while(leftMin && leftMin->left_)
        {
            leftMin = leftMin->left_;
        }
        return iterator(leftMin);
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    const_iterator begin() const
    {
        Node* leftMin = root_;
        while(leftMin && leftMin->left_)
        {
            leftMin = leftMin->left_;
        }
        return const_iterator(leftMin);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }
    bool IsBalance()
    {
        return IsBalance(root_);
    }
    int Height()
    {
        return Height(root_);
    }
    Node* Find(const K& key)
    {
        Node* cur =root_;
        KeyOfT kot;
        while(cur)
        {
            if(kot(cur->data_) < key) cur = cur->right_;
            else if(kot(cur ->data_) > key) cur = cur->left_;
            else return cur;
        }
        return nullptr;
    }
    pair<iterator,bool> Insert(const T& data)
    {
        if(root_ == nullptr)
        {
            root_ = new Node(data);
            root_->colour_ = BLACK;
            return make_pair(iterator(root_),true);
        }
        Node* parent = nullptr;
        Node* cur = root_;
        KeyOfT kot;
        while(cur)
        {
            if(kot(cur->data_) < kot(data)) {parent = cur; cur = cur->right_;}
            else if(kot(cur->data_) > kot(data)){parent = cur;cur = cur->left_;}
            else return make_pair(iterator(cur),false);
        }
        Node* newNode = new Node(data);
        newNode->colour_ = RED;
        if(kot(newNode->data_) < kot(parent->data_)) 
        {
            parent->left_ = newNode;
        }
        else
        {
            parent->right_ = newNode;
        }
        newNode->parent_ = parent;
        
        cur = newNode;
        while(parent && parent->colour_ == RED)
        {
            Node* grandparent = parent->parent_;
            if(parent == grandparent->left_)
            {
                Node* uncle = grandparent->right_;
                if(uncle && uncle->colour_ == RED)
                {
                    parent->colour_ = uncle->colour_ = BLACK;
                    grandparent->colour_ = RED;
                    cur = grandparent;
                    parent = cur->parent_;
                }
                else
                {
                    if(cur == parent->right_)
                    {
                        RotateL(parent);
                        swap(parent, cur);
                    }
                    RotateR(grandparent);
                    parent->colour_ = BLACK;
                    grandparent->colour_ = RED;
                    break;
                }
            }
            else
            {
                Node* uncle = grandparent->left_;
                if(uncle && uncle->colour_ == RED)
                {
                    parent->colour_ = uncle->colour_ = BLACK;
                    grandparent->colour_ = RED;
                    cur = grandparent;
                    parent = cur->parent_;
                }
                else
                {
                    if(cur == parent->left_)
                    {
                        RotateR(parent);
                        swap(parent, cur);
                    }
                    RotateL(grandparent);
                    parent->colour_ = BLACK;
                    grandparent->colour_ = RED;
                    break;
                }
            }
        }
        root_->colour_ = BLACK;
            
        return make_pair(iterator(newNode),true);
    }
    
    private:
    void RotateL(Node* parent)
    {
        rotate_count_++;
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
        rotate_count_++;
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
    bool CheckColour(Node* root,int black_count,int benchmark)
    {
        if(root == nullptr)
        {
            if(benchmark == -1) benchmark = black_count;
            else return benchmark == black_count;
            return true;
        }
        if(root->colour_ == RED && root->parent_ && root->parent_->colour_ == RED) return false;
        if(root->colour_ == BLACK) black_count++;
        return CheckColour(root->left_,black_count,benchmark) && CheckColour(root->right_,black_count,benchmark);
    }
    bool IsBalance(Node* node)
    {
        if(node == nullptr) return true;
        if(root_->colour_ != BLACK) return false;
        int black_count = 0;
        int benchmark = -1;
        return CheckColour(node,black_count,benchmark);
    }
    int Height(Node* node)
    {
        if(node == nullptr) return 0;
        int left_height = Height(node->left_);
        int right_height = Height(node->right_);
        return left_height > right_height ? left_height + 1 : right_height + 1;
    }
    Node* root_ = nullptr;
    public: 
    int rotate_count_ = 0;
};