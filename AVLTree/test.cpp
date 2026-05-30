#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// 请确保这两个头文件名与你的本地文件名一致
#include "AVLTree.h"  
#include "RBTree.h"

using namespace std;

// 辅助函数：中序遍历打印，用来顺便验证它是不是一棵合格的“二叉搜索树”（即打印出来必须是有序的）
template<class Tree>
void InOrderPrint(typename Tree::Node* root)
{
    if (root == nullptr) return;
    InOrderPrint<Tree>(root->left_);
    cout << root->kv_.first << " ";
    InOrderPrint<Tree>(root->right_);
}

int main()
{
    // 设置随机种子，采用固定常数（如100），这样如果代码崩溃，每次崩溃的随机序列都一样，极方便Debug
    srand(100); 

    cout << "==================================================" << endl;
    cout << "          ★ 自平衡树功能与压力测试平台 ★          " << endl;
    cout << "==================================================" << endl;

    // ---------------------------------------------------
    // 第一关：AVL树 基础功能与形态校验
    // ---------------------------------------------------
    cout << "\n[第 1 关：AVL树 常规测试]" << endl;
    AVLTree<int, int> avl;
    // 故意构造一个会连续触发单旋和双旋的序列
    vector<int> avl_data = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    for (auto e : avl_data)
    {
        avl.Insert(make_pair(e, e));
    }
    cout << "▶ 中序遍历结果（应升序）: ";
    // 注意：由于 root_ 是 private，测试时你可以临时把 root_ 改为 public，或者在类里封装一个公开的调用接口
    // 这里为了方便测试，若无法访问 root_ 可将下面这行注释掉
    // InOrderPrint<AVLTree<int, int>>(avl.GetRoot()); 
    cout << "\n▶ 树是否平衡 (1-是, 0-否) : " << avl.IsBalance() << endl;
    cout << "▶ 树的最终高度 : " << avl.Height() << endl;
    cout << "▶ 触发的总旋转次数 : " << avl._rotateCount << endl;


    // ---------------------------------------------------
    // 第二关：红黑树 基础功能与颜色校验
    // ---------------------------------------------------
    cout << "\n[第 2 关：红黑树 常规测试]" << endl;
    RBTree<int, int> rbtree;
    vector<int> rb_data = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
    for (auto e : rb_data)
    {
        rbtree.Insert(make_pair(e, e));
    }
    cout << "▶ 树是否满足红黑树性质 (1-是, 0-否) : " << rbtree.IsBalance() << endl;
    cout << "▶ 树的当前高度 : " << rbtree.Height() << endl;
    cout << "▶ 触发的总旋转次数 : " << rbtree._rotateCount << endl;


    // ---------------------------------------------------
    // 第三关：十万级大数据量 随机轰炸压力测试
    // ---------------------------------------------------
    cout << "\n[第 3 关：100,000级 随机暴击压测]" << endl;
    AVLTree<int, int> avl_stress;
    RBTree<int, int> rb_stress;
    
    const int TEST_SIZE = 100000;
    cout << "正在向两棵树分别疯狂插入 " << TEST_SIZE << " 个随机节点..." << endl;
    
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        int val = rand() % 1000000; // 产生 0 ~ 1000000 的随机数
        avl_stress.Insert(make_pair(val, val));
        rb_stress.Insert(make_pair(val, val));
    }

    cout << "\n★ 压测结果汇报 ★" << endl;
    cout << "① AVL树 是否依然保持完美的严格平衡？ -> " << (avl_stress.IsBalance() ? "【PASS】" : "【FAIL ❌】") << endl;
    cout << "② 红黑树 是否依然完美守住五大颜色规则？ -> " << (rb_stress.IsBalance() ? "【PASS】" : "【FAIL ❌】") << endl;


    // ---------------------------------------------------
    // 第四关：综合性能终极对比（数据说话）
    // ---------------------------------------------------
    cout << "\n[第 4 关：AVL树 vs 红黑树 终极各项指标切磋]" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "  指标项       |   AVL 树          |   红黑树        " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "  最终树高     |   " << avl_stress.Height() << "层             |   " << rb_stress.Height() << "层" << endl;
    cout << "  耗费旋转次数  |   " << avl_stress._rotateCount << "次          |   " << rb_stress._rotateCount << "次" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "提示：由于红黑树大量冲突靠“变色”解决，其旋转次数通常比 AVL 树少一大半！" << endl;
    cout << "==================================================" << endl;

    return 0;
}