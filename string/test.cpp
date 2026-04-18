#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include "string.h"
using namespace std;

void test1()
{
	bit::string s1("hello world\n");
	cout << s1.c_str() << endl;

	bit::string s2;
	cout << s2.c_str() << endl;

	for (size_t i = 0; i < s1.size(); i++)
	{
		s1[i]++;
	}
	cout << endl;

	for (size_t i = 0; i < s1.size(); i++)
	{
		cout << s1[i] << " ";
	}
	cout << endl;
	const bit::string s3("hello world");
	s3[0];

	bit::string::iterator it = s1.begin();
	while (it != s1.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto ch : s1)
	{
		cout << ch << " ";
	}
	cout << endl;

	//bit::string::const_iterator cit = s3.begin();
	auto cit = s3.begin();
	while (cit != s3.end())
	{
		//*cit +=1;
		cout << *cit << " ";
		++cit;
	}
	cout << endl;


}
void test2()
{
	bit::string s1("hello world\n");
	cout << s1.c_str() << endl;

	s1.push_back(' ');
	s1.push_back('!');
	s1.append("helta");
	cout << s1.c_str() << endl;

	bit::string s2("hello world\n");
	cout << s2.c_str() << endl;

	s2 += ' ';
	s2 += ' !';
	s2 += "helta";
	cout << s2.c_str() << endl;
}

void test3()
{
	bit::string s1("hello world\n");
	cout << s1.c_str() << endl;

	s1.insert(6, 3, '!');
	cout << s1.c_str() << endl;

	s1.insert(0, 3, '!');
	cout << s1.c_str() << endl;

	bit::string s2("hello world\n");
	s2.insert(5, "!!!!!");
	cout << s2.c_str() << endl;
	s2.erase(5);
	cout << s2.c_str() << endl;
	s2.resize(8,'!');
	cout << s2.c_str() << endl;
	s2.resize(13, '!');
	cout << s2.c_str() << endl;
}

int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}