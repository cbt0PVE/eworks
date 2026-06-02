#include "Mymap.h"
#include "Myset.h"
#include <string>
#include <vector>

void TestSet()
{
    cout << "Testing Set..." << endl;
    helta::Set<int> s;
    int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
    for (auto e : a)
    {
        s.Insert(e);
    }

    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl << endl;
}

void TestMap()
{
    cout << "Testing Map..." << endl;
    helta::map<string, string> dict;
    dict.Insert(make_pair("sort", "排序"));
    dict.Insert(make_pair("left", "左边"));
    dict.Insert(make_pair("right", "右边"));

    for (auto& kv : dict)
    {
        cout << kv.first << ":" << kv.second << endl;
    }
    cout << endl;
    
    // Test operator[]
    dict["insert"] = "插入";
    dict["left"] = "左边 (modified)";
    
    for (auto& kv : dict)
    {
        cout << kv.first << ":" << kv.second << endl;
    }
    cout << endl;
}

int main()
{
    TestSet();
    TestMap();
    return 0;
}
