#include<iostream>
#include<vector>

void insertSort(int* a, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int tmp = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > tmp)
		{
			a[j + 1] = a[j--];
		}
		a[j + 1] = tmp;
	}
}

void ShellSort(int* a, int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i++)
		{
			int tmp = a[i];
			int j = i - gap;
			while (j >= 0 && a[j] > tmp)
			{
				a[j + gap] = a[j];
				j -= gap;
			}
			a[j + gap] = tmp;
		}
	}
}