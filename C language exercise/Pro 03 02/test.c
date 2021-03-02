#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<stdlib.h>  
#include<math.h>

//1.写函数—判断正整数n是否为质数
//int isPrime(int n);
//
//int main()
//{
//	int i, j, k;
//	printf("输入需要判断的数：");
//	scanf("%d", &i);
//	j = isPrime(i);
//	if (j == 0)
//		printf("%d为质数", &i);
//	else
//		printf("%d不是质数", &i);
//	
//	return 0;
//}
//
//int isPrime(int n)
//{
//	if (n < 2)
//		return 0;
//	for (int i = 2; i < n; i++)
//	{
//		if (n % i == 0)
//			return 0;
//	}
//
//	return 1;
//}

//2.函数输出1-n的和
int sum(int n);

int main()
{
	int n;
	scanf("%d", &n);
	printf("和为%d", sum(n));

	return 0;
}

int sum(int n)
{
	int s = 0;

	for (int i = 1; i <= n; i++)
	{
		s = s + i;
	}

	return s;
}