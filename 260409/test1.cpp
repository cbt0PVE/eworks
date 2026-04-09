#include<iostream>
#include<queue>
#include<stack>

using namespace std;

//leetcode 225
class MyStack
{
private:
	queue<int> q;

public:
	MyStack() {}

    void push(int x) 
    {
        int size = q.size();
        q.push(x);
        for (int i = 0; i < size; ++i)
        {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() 
    {
        int topVal = q.front();
        q.pop();
        return topVal;
    }

    int top() 
    {
        return q.front();
    }

    bool empty() 
    {
        return q.empty();
    }

};

//leetcode 232
class MyQueue 
{
private:
    stack<int> inStack;
    stack<int> outStack;

    void inToOut() 
    {
        if (outStack.empty())
        {
            while (!inStack.empty())
            {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
    }
public:
    MyQueue() {}

    void push(int x)
    {
        inStack.push(x);
    }

    int pop() 
    {
        inToOut();
        int val = outStack.top();
        outStack.pop();
        return val;
    }

    int peek()
    {
        inToOut();
        return outStack.top();
    }

    bool empty() 
    {
        return inStack.empty() && outStack.empty();
    }
};