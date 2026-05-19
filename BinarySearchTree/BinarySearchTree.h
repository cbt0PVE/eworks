#pragma once
#include<iostream>
using namespace std;
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
                        Node* leftMax = cur->left_;
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
            InOrder_(root->left_);
            std::cout << root->key_ << " ";
            InOrder_(root->right_);
        }
        private:
        Node* root_;
    };
    	void TestBSTree1()
	{
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		BSTree<int> t;
		for (auto e : a)
		{
			t.InsertR(e);
		}

		t.InOrder();

		t.Erase(4);
		t.InOrder();

		t.EraseR(6);
		t.InOrder();

		t.EraseR(7);
		t.InOrder();

		t.EraseR(3);
		t.InOrder();

		for (auto e : a)
		{
			t.EraseR(e);
		}
		t.InOrder();
	}

	void TestBSTree2()
	{
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		BSTree<int> t;
		for (auto e : a)
		{
			t.InsertR(e);
		}

		BSTree<int> t1(t);

		t.InOrder();
		t1.InOrder();
	}
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
    template<class K,class V>
    class BSTree
    {
        typedef BSTreeNode<K,V> Node;
        public:
        BSTree()
        :root_(nullptr)
        {}
        void InOrder()
        {
            InOrder_(root_);
            std::cout << std::endl;
        }

        Node* FindR(const K& key)
        {
            return FindR_(root_,key);
        }
        bool InsertR(const K& key, const V& value)
		{
			return InsertR_(root_, key, value);
		}

		bool EraseR(const K& key)
		{
			return EraseR_(root_, key);
		}
        private:
        bool EraseR_(Node* root,const K& key)
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
                {
                    leftMax = leftMax->right_;
                }
                swap(root->key_,leftMax->key_);
                swap(root->value_,leftMax->value_);
                return EraseR_(root->left_,key);
                }
                delete del;
                del = nullptr;
                return true;
            }
        }
        Node* FindR_(Node* root,const K& key)
        {
            if(root == nullptr)
            return nullptr;
            if(root->key_ > key)
            {
                return FindR_(root->left_,key);
            }
            else if(root->key_ < key)
            {
                return FindR_(root->right_,key);
            }
            else
            {
                return root;
            }
        }
        bool InsertR_(Node* root,const K& key,const V& value)
        {
            if(root == nullptr)            {
                root = new Node(key,value);
                return true;
            }
            if(root->key_ > key)
            {
                return InsertR_(root->left_,key,value);
            }
            else if(root->key_ < key)
            {    return InsertR_(root->right_,key,value);
            }
            else
            {
                return false;
            }       
        }
        void InOrder_(Node* root)
        {
            if(root == nullptr)            {
                return;
            }
            InOrder_(root->left_);
            std::cout << root->key_ << ":" << root->value_ << " ";
            InOrder_(root->right_);
        }       
    
        private:
        Node* root_;
    };
    	void TestBSTree1()
	{
		//BSTree<string, Date> carTree;

		BSTree<std::string, std::string> dict;
		dict.InsertR("insert", "插入");
		dict.InsertR("sort", "排序");
		dict.InsertR("right", "右边");
		dict.InsertR("date", "日期");

		std::string str;
		while (std::cin>>str)
		{
			BSTreeNode<std::string, std::string>* ret = dict.FindR(str);
			if (ret)
			{
				std::cout << ret->value_ << std::endl;
			}
			else
			{
				std::cout << "无此单词" << std::endl;
			}
		}
	}

	void TestBSTree2()
	{
		// 11:44继续
		// 统计水果出现的次数
		std::string arr[] = { "西瓜", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
		BSTree<std::string, int> countTree;
		for (auto& str : arr)
		{
			auto ret = countTree.FindR(str);
			if (ret == nullptr)
			{
				countTree.InsertR(str, 1);
			}
			else
			{
				ret->value_++;
			}
		}

		countTree.InOrder();
        
	}
}