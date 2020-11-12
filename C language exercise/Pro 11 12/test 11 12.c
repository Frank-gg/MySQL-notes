#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1.数组交换
//int main()
//{
//	int arr1[] = { 1,3,5,7,9 };
//	int arr2[] = { 2,4,6,8,0 };
//	int temp = 0, i = 0;
//	int sz = sizeof(arr1) / sizeof(arr1[0]);
//	for (i = 0; i < sz; i++)
//	{
//		temp = arr1[i];
//		arr1[i] = arr2[i];
//		arr2[i] = temp;
//	}
//
//	return 0;
//}


//2.写一个函数求a的二进制（补码）表示中有几个1
//int main()
//{
//	int a = 0;
//	scanf("%d", &a);
//	//写一个函数求a的二进制（补码）表示中有几个1
//	int count = count_bit_one(a);
//	printf("count = %d\n", count);
//	system("pause");//system库函数-执行系统命令-pause（暂停）
//	return 0;
//}
//int count_bit_one(int n)
//{
//	int count = 0;
//	/*while (n)
//	{
//		if (n % 2 == 1)
//		{
//			count++;
//		}
//		n = n / 2;
//	}*/
//	
//	/*int i = 0;
//	for (i = 0; i < 32; i++)
//	{
//		if (((n >> i) & 1) == 1)
//		{
//			count++;
//		}
//	}*/
//
//	while (n)
//	{
//		n = n & (n - 1);
//		count++;
//	}
//	return count;
//}


//3.求两个数二进制中不同位的个数
//int main()
//{
//	int m = 0, n = 0;
//	scanf("%d%d", &m, &n);
//	int count = get_diff_bit(m, n);
//	printf("count=%d\n", count);
//
//	return 0;
//}
//int get_diff_bit(int m, int n)
//{
//	int temp = m ^ n, count = 0;//异或 二进制位相同为零 相异为一
//	while (temp)
//	{
//		temp = temp & (temp - 1);
//		count++;
//	}
//	return count;
//}

//4.打印二进制的奇数位与偶数位
//int main()
//{
//	int m = 0;
//	scanf("%d", &m);
//	print(m);
//	return 0;
//}
//int print(int m)
//{
//	int i = 0;
//	printf("奇数位：\n");
//	for (i = 30; i >= 0; i -= 2)
//	{
//		printf("%d", (m >> i) & 1);
//	}
//	printf("\n");
//	printf("偶数位：\n");
//	for (i = 31; i >= 1; i -= 2)
//	{
//		printf("%d", (m >> i) & 1);
//	}
//	printf("\n");
//}

//5.用指针打印数组
//int main()
//{
//	int arr[] = { 1,2,3,4,5,6,7,8,9 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	print(arr, sz);
//
//	return 0;
//}
//int print(int* p, int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d  ", *(p + i));
//	}
//}

//6.打印输出乘法表
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	print_table(n);
//
//	return 0;
//}
//int print_table(int n)
//{
//	int i = 0;
//	int j = 0;
//	int q = 0;
//	for (i = 1; i <= n; i++)
//	{
//		for (j = 1; j <= i; j++)
//		{
//			q = i * j;
//			printf("%d*%d=%-3d   ", j, i, q);//nd：n代表的是列宽长度 -nd:-是左对齐 0nd:不足n位长度的左补齐0。
//		}
//		printf("\n");
//	}
//}


////7.将参数字符串中的字符反向排列
//int main()
//{
//	char arr[] = "abcdef";
//	reverse_string(arr);
//	printf("%s\n", arr);
//
//	return 0;
//}
//int my_strlen(char* str)
//{
//	int count = 0;
//	while (*str != '\0')
//	{
//		count++;
//		str++;
//	}
//	return count;
//}
//7.1直接求解
//int reverse_string(char arr[])
//{
//	int left = 0;
//	int right = my_strlen(arr) - 1;
//
//	while (left < right)
//	{
//		int temp = arr[left];
//		arr[left] = arr[right];
//		arr[right] = temp;
//		left++;
//		right--;
//	}
//}
//7.2递归求解
//int reverse_string(char arr[])
//{
//	char temp = arr[0];
//	int len = my_strlen(arr);
//	arr[0] = arr[len - 1];
//	arr[len - 1] = '\0';
//	if (my_strlen(arr + 1) >= 2)
//		reverse_string(arr + 1);
//	arr[len - 1] = temp;
//}

