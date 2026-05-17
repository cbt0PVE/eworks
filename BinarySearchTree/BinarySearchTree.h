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
}