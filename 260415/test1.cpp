#include<iostream>
#include<vector>
using namespace std;

class MyCircularQueue 
{
private:
    vector<int> data;
    int front;
    int rear;
    int capacity;
public:
    MyCircularQueue(int k)
    {
        capacity = k + 1;
        data.resize(capacity);
        front = 0;
        rear = 0;
    }
    //入队
    bool enQueue(int value) 
    {
        if (isFull())
        {
            return false;
        }
        data[rear] = value;
        rear = (rear + 1) % capacity;
        return true;

    }
    //出队
    bool deQueue() 
    {
        if (isEmpty())
        {
            return false;
        }
        front = (front + 1) % capacity;
        return true;
    }

    int Front() 
    {
        if (isEmpty())
        {
            return - 1;
        }
        return data[front];
    }

    int Rear() 
    {
        if (isEmpty())
        {
            return -1;
        }
        return data[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty() 
    {
        return front == rear;
    }

    bool isFull()
    {
        return (rear + 1) % capacity == front;
    }
};

int main()
{
    return 0;
}