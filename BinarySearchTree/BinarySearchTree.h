#pragma once
namespace key
{
    template<class K>
    struct BSTreeNode
    {
        K key_;
        BSTreeNode* left_;
        BSTreeNode* right_;

        BSTreeNode(const K& key)
            : key_(key)
            , left_(nullptr)
            , right_(nullptr)
        {}
    };

    template<class K>
    class BSTree
    {
        typedef BSTreeNode<K> Node;
        public:
        BSTree()
        :root_(nullptr)
        {}
        BSTree(const K& t)
        {
            root_ = Copy(t.root_);
        } 
        BSTree<K>& operator=(const BSTree<K>& t)
        {
            if(this != &t)
            {
                BSTree<K> copy(t);
                swap(root_,copy.root_);
            }
            return *this;
        }
        ~BSTree()
        {
            Clear(root_);
        }
        bool Insert(const K& key)
        {
            if(root_ == nullptr)
            {
                root_ = new Node(key);
                return true;
            }
            Node* parent = nullptr;
            Node* cur = root_;
            while(cur)
            {
                if(cur->key_ == key)
                return false;
                else if(cur->key_ > key)
                {
                    parent = cur;
                    cur = cur->left_;
                }
                else
                {
                    parent = cur;
                    cur = cur->right_;
                }
            }
            cur = new Node(key);
            if(parent->key_ > key)
            {
                parent->left_ = cur;
            }
            else
            {
                parent->right_ = cur;
            }
            return true;
        }
        bool Find(const K& key)
        {
            Node* cur = root_;
            while(cur)
            {
                if(cur->key_ > key)
                {
                    cur = cur->left_;
                }
                else if(cur->key_ < key)
                {
                    cur = cur->right_;
                }
                else
                {
                    return true;
                }
            }
        }
        bool Erase(const K& key)
        {
            Node* parent = nullptr;
            Node* cur = root_;
            while(cur)
            {
                if(cur->key_ > key)
                {
                    parent = cur;
                    cur = cur->left_;
                }
                else if(cur->key_ < key)
                {
                    parent = cur;
                    cur = cur->right_;
                }
                else
                {
                    //左为空右不为空
                    if(cur->left_ == nullptr)
                    {
                        if(cur == root_)
                        {
                            root_ = cur->right_;
                        }
                        else if(parent->left_ == cur)
                        {
                            parent->left_ = cur->right_;
                        }
                        else
                        {
                            parent->right_ = cur->right_;
                        }
                    }
                    //右为空左不为空
                    else if(parent->right_ == cur)
                    {
                        if(cur == root_)
                        {
                            root_ = cur->left_;
                        }
                        else if(parent->left_ == cur)
                        {
                            parent->left_ = cur->left_;
                        }
                        else
                        {
                            parent->right_ = cur->left_;
                        }
                    }
                    else
                    {
                        Node* parent = cur;
                        Node* leftMax = cur->Left_;
                        while(leftMax->right_)
                        {
                            parent = leftMax;
                            leftMax = leftMax->right_;
                        }

                        swap(cur->key_,leftMax->key_);
                        if(parent->left_ == leftMax)
                        {
                            parent->left_ = leftMax->left_;
                        }
                        else
                        {
                            parent->right_ = leftMax->left_;
                        }
                        cur = leftMax;
                    }
                    delete cur;
                    return true;
                }
            }
            return false;
        }

        void InOrder()
        {
            InOrder_(root_);
            std::cout << std::endl;
        }
        		bool FindR(const K& key)
		{
			return FindR_(root_, key);
		}

		bool InsertR(const K& key)
		{
			return InsertR_(root_, key);
		}

		bool EraseR(const K& key)
		{
			return EraseR_(root_, key);
		}

        private:
        Node* Copy(Node* root)
        {
            if(root == nullptr)
            {
                return nullptr;
            }
            Node* copyroot = new Node(root->key_);
            copyroot->left_ = Copy(root->left_);
            copyroot->right_ = Copy(root->right_);
            return copyroot;
        }
        void Clear(Node* root)
        {
            if(root == nullptr)
            {
                return;
            }
            Clear(root->left_);
            Clear(root->right_);
            delete root;
            root = nullptr;
        }
        bool EraseR_(Node* root, const K& key)
        {
            if(root == nullptr)
            {
                return false;
            }
            if(root->key_ > key)
            {
                return EraseR_(root->left_,key);
            }
            else if(root->key_ < key)
            {
                return EraseR_(root->right_,key);
            }
            else
            {
                Node* del = root;
                if(root->left_ == nullptr)
                {
                    root = root->right_;
                }
                else if(root->right_ == nullptr)
                {
                    root = root->left_;
                }
                else
                {
                    Node* leftMax = root->left_;
                    while(leftMax->right_)
                    {leftMax = leftMax->right_;}
                    swap(root->key_,leftMax->key_);
                    return EraseR_(root->left_,key);
                }

                delete del;
                del = nullptr;
                return true;
            }
        }
        bool FindR_(Node* root,const K& key)
        {
            if(root == nullptr)
            return false;
            if(root->key_ > key)
            {
                return FindR_(root->left_,key);
            }
            if(root->key_ < key)
            {
                return FindR_(root->right_,key);
            }
            return true;
        }
        bool InsertR_(Node* root,const K& key)
        {
            if(root == nullptr)
            {
                root = new Node(key);
                return true;
            }
            if(root->key_ > key)
            {
                return InsertR_(root->left_,key);
            }
            else if(root->key_ < key)
            {
                return InsertR_(root->right_,key);
            }
            else
            {
                return false;
            }
        }

        void InOrder_(Node* root)
        {
            if(root == nullptr)
            {
                return;
            }
            Inorder_(root->left_);
            std::cout << root->key_ << " ";
            Inorder_(root->right_);
        }
        private:
        Node* root_;
    };
}

namespace key_value
{
    template<class K,class V>
    struct BSTreeNode
    {
        BSTreeNode<K,V>* left_;
        BSTreeNode<K,V>* right_;
        K key_;
        V value_;

        BSTreeNode(const K& key,const V& value)
        :key_(key)
        ,value_(value)
        ,left_(nullptr)
        ,right_(nullptr)
        {}
    };
}