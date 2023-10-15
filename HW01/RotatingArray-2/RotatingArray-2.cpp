#include<iostream>
using namespace std;

void rotate(int* nums, int numLength, int k) {
	k %= numLength;
	int* num1 = (int*)malloc(numLength * sizeof(int));
	int h = 0;
	for (int i = numLength - k; i < numLength; i++)
	{
		num1[h] = nums[i];
		h++;
	}
	for (int i = 0; i < numLength - k; i++)
	{
		num1[i + k] = nums[i];
	}
	for (int i = 0; i < numLength; i++)
	{
		nums[i]=num1[i];
	}

	return;
}

int main()
{
	int numsLength = 0;
	int nums[100];
	int k = 0;
	cin >> numsLength >> k;
	for (int i = 0; i < numsLength; i++)
	{
		cin >> nums[i];
	}
	rotate(nums, numsLength, k);
	for (int i = 0; i < numsLength; i++)
	{
		cout << nums[i] << " ";
	}
	return 0;
}