#include<iostream>
#include<vector>
#include<list>
//#include<algorithm>
using namespace std;
//
//void test_list1()
//{
//	list<int> lt;
//	lt.push_back(1);
//	lt.push_back(2);
//	lt.push_back(3);
//	lt.push_back(4);
//
//	lt.push_front(10);
//	lt.push_front(20);
//
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	//v.insert(v.begin(),10);
//	//lt.insert(lt.begin(), 5);
//	auto it = lt.begin();
//	for (size_t i = 0; i < 5; i++)
//	{
//		++it;
//	}
//	lt.insert(it, 100);
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	it = find(lt.begin(), lt.end(), 3);
//	if (it != lt.end())
//	{
//		lt.insert(it, 30);
//	}
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	it = lt.begin();
//	while (it != lt.end())
//	{
//		if (*it % 2 == 0)
//		{
//			lt.erase(it);
//		}
//		else 
//		{
//			++it;
//		}
//	}
//
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//}
//
//void test_list2()
//{
//	list<int> lt;
//	lt.push_back(1);
//	lt.push_back(2);
//	lt.push_back(3);
//	lt.push_back(4);
//
//	lt.push_front(10);
//	lt.push_front(20);
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	reverse(lt.begin(), lt.end());
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	lt.reverse();
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	sort(lt.begin(), lt.end());
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	lt.sort();
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//}
//void test_op()
//{
//	srand(time(0));
//	const int N = 100000;
//	vector<int> v;
//	v.reserve(N);
//	list<int> lt1;
//	for (int i = 0; i < N; ++i)
//	{
//		auto e = rand();
//		v.push_back(e);
//		lt1.push_back(e);
//	}
//	int begin1 = clock();
//	sort(v.begin(), v.end());
//	int end1 = clock();
//
//	int begin2 = clock();
//	lt1.sort();
//	int end2 = clock();
//
//	printf("vector sort: %d\n", end1 - begin1);
//	printf("list sort:%d\n", end2 - begin2);
//}

#include"list.h"
int main()
{
	//test_list1();
	//test_list2();
	//test_op();
	helta::test_list1();
	return 0;
}