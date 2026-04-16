#include<iostream>
#include<vector>
#include<algorithm>
#include<stdexcept>

using HPDataType = int;
class Heap
{
private:
	std::vector<HPDataType> a_;
	int size_;
	int capacity_;
	//向上调整
	void AdJustUp(int child)
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (a_[child] > a_[parent])
			{
				std::swap(a_[child], a_[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
	void AdJustDown(int parent)
	{
		int child = 2 * parent + 1;
		while (child < size_)
		{
			if (child + 1 < size_ && a_[child + 1] > a_[child])
			{
				child++;
			}
			if (a_[child] > a_[parent])
			{
				std::swap(a_[child], a_[parent]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				break;
			}
		}
	}
public:
	Heap()
		:size_(0),
		capacity_(4)
	{
		a_.resize(capacity_);
	}

	~Heap() = default;

	void HeapPush(HPDataType x)
	{
		if (size_ == capacity_ * 2)
		{
			a_.resize(capacity_ * 2);
			capacity_ *= 2;
		}
		a_[size_++] = x;
		AdJustUp(size_ - 1);
	}

	void HeapPop()
	{
		if (HeapEmpty())
		{
			throw std::runtime_error("Heap is empty,cannot pop~!");
		}
		std::swap(a_[0], a_[size_ - 1]);
		size_--;
		AdJustDown(0);
	}

	HPDataType HeapTop()
	{
		if (HeapEmpty())
		{
			throw std::runtime_error("Heap is empty, no top element");
		}
		return a_[0];
	}

	int HeapSize()
	{
		return size_;
	}

	bool HeapEmpty()
	{
		return size_ == 0 ;
	}
};