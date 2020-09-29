#include <stdio.h>
#include <limits.h>

int main()
{
	int arr[] = { 1,2,3,4,5,4,3,2,1 };
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);//计算arr数组的大小

	for (i = 0; i < sz; i++)
	{
		//统计arr[i]在arr数组中出现了几次
		int j = 0;
		int count = 0;//计数器
		for (i = 0; i < sz; j++)
		{
			if (arr[i] == arr[j])
			{
				count++;
			}
		}
		if (count == 1)
		{
			printf("单身狗：%d\n", arr[i]);
			break;
		}
	}
	return 0;
}