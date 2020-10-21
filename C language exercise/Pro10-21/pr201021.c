#include <stdio.h>
#include <string.h>

//
//int main()
//{
//	//二分查找
//	//一个有序数组中查找具体的某个数
//	//如果找到了返回这个数的下标，找不到返回-1.
//
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//	int k = 7;
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	//传过来的只是数组arr首元素的地址
//	int ret = binary_search(arr, k, sz);
//	if (ret == -1)
//	{
//		printf("找不到指定的数字\n");
//	}
//	else
//	{
//		printf("找到了，下标是：%d\n", ret);
//	}
//	return 0;
//}
//int binary_search(int arr[], int k, int sz)//本质上arr只是一个指针
//{
//	//int sz = sizeof(arr) / sizeof(arr[0]);//不能在函数内部这样计算
//	int left = 0;
//	int right = sz - 1;
//
//	while (left <= right)
//	{
//		int mid = (left + right) / 2;
//		if (arr[mid] < k)
//		{
//			left = mid + 1;
//		}
//		else if (arr[mid] > k)
//		{
//			right = mid - 1;
//		}
//		else
//		{
//			return mid;
//		}
//	}
//
//}



////递归打印1234
//void print(int n)
//{
//	if (n > 9)
//	{
//		print(n / 10);
//	}
//	printf("%d  ", n % 10);
//}
//
//int main()
//{
//	int num = 1234;
//	print(num);
//	return 0;
//}



//1.求字符串长度
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

//2.递归的方法
//int my_strlen(char* str)
//{
//	if (*str != '\0')
//		return 1 + my_strlen(str + 1);
//	else
//		return 0;
//}
//
//int main()
//{
//	char arr[] = "bit";
//	//int len = strlen(arr);//求字符串长度
//	
//	//模拟实现strlen函数
//	int len = my_strlen(arr);//arr是数组，数组传参，传过去的不是整个数组，而是数组首个元素的地址
//	printf("%d\n", len);
//	
//	return 0;
//}

//求n的阶乘
//int main()
//{
//	int n = 0;
//	int ret = 0;
//	scanf_s("%d", &n);
//	ret = Fac1(n);//循环的方式
//	printf("%d\n", ret);
//
//	return 0;
//}
//
//int Fac1(int n)
//{
//	int i = 0;
//	int ret = 1;
//	for (i = 1; i <= n; i++)
//	{
//		ret *= i;
//	}
//	return ret;
//}
//
//int Fac2(int n)
//{
//	if (n <= 1)
//		return 1;
//	else
//		return n * Fac(n - 2);
//}


//描述第n个斐波那契数1 1 2 3 5 8 13
//int main()
//{
//	int n = 0;
//	int ret = 0;
//	scanf_s("%d", &n);
//	//TDD-测试驱动开发
//	ret = Fib(n);
//	printf("%d", ret);
//
//	return 0;
//}
//递归的方式
//int Fib(int n)
//{
//	if (n <= 2)
//		return 1;
//	else
//		return Fib(n - 1) + Fib(n - 2);
//
//}
//循环的方式
//int Fib(int n)
//{
//	int a = 1;
//	int b = 1;
//	int c = 0;
//
//	while (n > 2)
//	{
//		c = a + b;
//		a = b;
//		b = c;
//		n--;
//	}
//	return c;
//}

//汉诺塔问题与青蛙跳台阶问题（递归）