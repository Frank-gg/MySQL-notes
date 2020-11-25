#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <math.h>

//1.利用递归求1-n的和
//int main()
//{
//	int s, n, i;
//	printf("请输入n的值\n");
//	scanf("%d", &n);
//	i = n;
//
//	s = sum(n);
//
//	printf("1-%d得和为：%d", i, s);
//
//	return 0;
//}
//int sum(int n)
//{
//	if (n == 1)
//		return 1;
//	else
//		return n + sum(n - 1);
//}

//2.利用递归求a^n
//int main()
//{
//	double a;
//	int n;
//	double i;
//	printf("请输入a与n的值：\n");
//	scanf("%lf %d", &a, &n);
//	
//	i = pows(a, n);
//	printf("%lf的%d次方为：%lf\n", a, n, i);
//
//	return 0;
//}
//double pows(double a, int n)
//{
//	if (n == 0)
//		return 1;
//	if (n == 1)
//		return a;
//	return pows(a, n / 2) * pows(a, n - n / 2);
//}

//3.递归实行输入整数abc，输出a b c
//int main()
//{
//	int n;
//	printf("输入想操作的整数n：");
//	scanf("%d", &n);
//
//	deal(n);
//
//	return 0;
//}
//int deal(int n)
//{
//	int i;
//	if (n != 0)
//	{
//		i = n % 10;
//		n = n / 10;
//		printf("%d ", i);
//	}
//	
//	return deal(n);
//}
//int main()
//{
//	int n;
//
//	printf("请输入一个整数：");
//	scanf("%d", &n);
//
//	p(n);
//}
//int p(int n)
//{
//	if (n / 10 == 0)
//	{
//		printf("%d ", n);
//		return;
//	}
//	p(n / 10);
//	printf("%d ", n % 10);
//}

//4.将一组数逆序
//#define N 10
//
//int main()
//{
//	int a[N];
//	int n;
//
//	printf("输入整数个数：");
//	scanf("%d", &n);
//	for (int i = 0; i < n; i++)
//	{
//		printf("输入第%d个数:", i+1);
//		scanf("%d", &a[i]);
//	}
//	for (int i = 0; i < n / 2; i++)
//	{
//		int t;
//		t = a[i];
//		a[i] = a[n - 1 - i];
//		a[n - 1 - i] = t;
//	}
//	for (int i = 0; i < n; i++)
//	{
//		printf("%d", a[i]);
//	}
//
//	return 0;
//}