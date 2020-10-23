#include <stdio.h>

//int main()
//{
//	//创建一个数组
//	int arr[10] = { 1,2,3 };
//	char arr2[5] = { 'a',89 };
//	char arr3[5] = "ab";
//	char arr4[] = "abcdef";
//	printf("%d\n", sizeof(arr4));
//	//sizeof计算所占空间大小=char 7*1=7
//	printf("%d\n", strlen(arr4));
//	//strlen求字符串长度--'\0'之前的字符个数
//	//[a b c d e f \0]
//	return 0;
//
//	//1.strlen与sizeof没有什么关联
//	//2.strlen是求字符串长度的-只能对字符串求长度-库函数-使用得引头文件
//	//3.sizeof 计算变量、数组、类型的大小-单位是字节-操作符
//}

//int mian()
//{
//	char arr[] = "abcdef";
//	int i = 0;
//	int len = strlen(arr);
//	for (i = 0; i < len; i++);
//	{
//		printf("%c", arr[i]);
//	}
//	int arr[] = { 1,2,3,4,5,6,7,8,9 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d\n", arr[i]);
//	}
//
//	return 0;
//}

int main()
{
	int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);
	//对arr进行排序，排成升序
	bubble_sort(arr, sz);//冒泡排序函数
	for (i = 0; i < sz; i++)
	{
		printf("&d", arr[i]);
	}

	return 0;
}

void bubble_sort(int arr[],int sz)
{
	//确认冒泡排序的趟数
	int i = 0;
	for (i = 0; i < sz - 1; i++)
	{
		//每一趟冒泡排序
		int j = 0;
		for (j = 0; j < sz-1-i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}