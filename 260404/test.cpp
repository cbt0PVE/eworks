#include<vector>
#include<cassert>

using namespace std;

class Solution1
{
public: 
	int removeDuplicates(vector<int>& nums)
	{
		if (nums.empty())
		{
			return 0;
		}
		int slow = 0;
		for (int fast = 1; fast < nums.size(); ++fast)
		{
			if (nums[fast] != nums[slow])
			{
				nums[++slow] = nums[fast];
			}
		}
		return slow + 1;
	}
};

//int main()
//{
//	Solution1 s;
//	vector<int> nums1 = { 1,1,2 };
//	int k1 = s.removeDuplicates(nums1);
//	vector<int> expected1 = { 1,2 };
//	assert(k1 == expected1.size());
//	for (int i = 0; i < k1; i++)
//	{
//		assert(nums1[i] == expected1[i]);
//	}
//
//	vector<int> nums2 = { 2,2,2,2 };
//	int k2 = s.removeDuplicates(nums2);
//	vector<int> expected2 = { 2 };
//	assert(k2 == expected2.size());
//	for (int i = 0; i < k2; i++)
//	{
//		assert(nums2[i] == expected2[i]);
//	}
//
//	vector<int> nums3 = { 1,2,3,4 };
//	int k3 = s.removeDuplicates(nums3);
//	vector<int> expected3 = { 1,2,3,4 };
//	assert(k3 == expected3.size());
//	for (int i = 0; i < k3; ++i)
//	{
//		assert(nums3[i] == expected3[i]);
//	}
//
//	vector<int> nums4;
//	int k = s.removeDuplicates(nums4);
//	assert(k == 0);
//
//	return 0;
//
//}

class Solution
{
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		int i = m - 1;
		int j = n - 1;
		int k = m + n - 1;

		while (i >= 0 && j >= 0)
		{
			if (nums1[i] > nums2[j])
			{
				nums1[k--] = nums1[i--];
			}
			else
			{
				nums1[k--] = nums2[j--];
			}
		}
		while (j >= 0)
		{
			nums1[k--] = nums2[j--];
		}
	}
};