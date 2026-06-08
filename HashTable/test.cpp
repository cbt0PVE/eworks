#include <iostream>
#include <string>
#include <vector>
#include "UnorderedMap.h"
#include "UnorderedSet.h"

using namespace std;

void test_unordered_set()
{
    cout << "Testing UnorderedSet..." << endl;
    helta::UnorderedSet<int> s;
    s.Insert(1);
    s.Insert(3);
    s.Insert(2);
    s.Insert(20);
    s.Insert(2); // Duplicate

    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;

    auto it = s.Find(3);
    if (it != s.end())
    {
        cout << "Found 3" << endl;
    }
    else
    {
        cout << "Did not find 3" << endl;
    }

    s.Erase(3);
    it = s.Find(3);
    if (it != s.end())
    {
        cout << "Found 3 after erase" << endl;
    }
    else
    {
        cout << "Did not find 3 after erase" << endl;
    }
}

void test_unordered_map()
{
    cout << "\nTesting UnorderedMap..." << endl;
    helta::UnorderedMap<string, string> dict;
    dict.Insert(make_pair("sort", "排序"));
    dict.Insert(make_pair("string", "字符串"));
    dict.Insert(make_pair("insert", "插入"));

    cout << "dict[\"sort\"]: " << dict["sort"] << endl;
    dict["sort"] = "排序!!!";
    cout << "dict[\"sort\"] after change: " << dict["sort"] << endl;

    for (auto& kv : dict)
    {
        cout << kv.first << ":" << kv.second << endl;
    }

    auto it = dict.Find("string");
    if (it != dict.end())
    {
        cout << "Found string: " << it->second << endl;
    }

    dict.Erase("insert");
    if (dict.Find("insert") == dict.end())
    {
        cout << "insert erased successfully" << endl;
    }
}

int main()
{
    test_unordered_set();
    test_unordered_map();
    return 0;
}
