#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

//1.用while语句实现1-100得和
//int main()
//{
//	int i = 100, sum = 0;
//	while (i--)
//	{
//		sum = sum + i;
//	}
//	printf("1-100的和为：%d", sum);
//	return 0;
//}


//2.已知两个正整数，求他们的最大公约数与最小公倍数
//int main()
//{
//	int m, n, r, p, q;
//	printf("请输入两个整数：m n\n");
//	scanf("%d%d", &m, &n);
//
//	//比较m与n的大小 m放入较大值
//	if (m < n)
//	{
//		q = m;
//		m = n;
//		n = q;
//	}
//	p = m;
//	q = n;
//	//求最大公约数
//	while (p % q)
//	{
//		r = p % q;
//		p = q;
//		q = r;
//	}
//	printf("%d和%d的最大公约数为：%d 最小公倍数为：%d", m, n, q, m * n / q);
//
//	return 0;
//}

//int main()
//{
//	int m, n, r;
//	printf("请输入两个整数：m n\n");
//	scanf("%d%d", &m, &n);
//
//	//比较m与n的大小 m放入较大值
//	if (m < n)
//	{
//		r = m;
//		m = n;
//		n = r;
//	}
//	r = n;
//	while (1)
//	{
//		if (m % r == 0 && n % r == 0)
//		{
//			printf("%d与%d最大公约数为：%d 最大公倍数为：%d", m, n, r, m * n / r);
//			break;
//		}
//		else
//			r--;
//	}
//
//	return 0;
//}

//3.计算一个不足十位数整数的位数
//int main()
//{
//	int m, n, count = 0;
//	printf("请输入一位位数小于10的整数：");
//	scanf("%d", &m);
//	n = m;
//	while (n / 10 != 0)
//	{
//		count = count + 1;
//	}
//	printf("%d的位数为：%d", m, count);
//
//	return 0;
//}

//4.输入n值，求1-1/2+1/3-...+(-1)^(n-1)*1/n
//int main()
//{
//	int n, i;
//	printf("请输入n值：");
//	scanf("%d", &n);
//	
//	double sum = 0.0, sign = 1.0, term;
//	for (i = 1; i <= n; i++)
//	{
//		term = sign / i;
//		sum = sum + term;
//		sign = sign * (-1);
//	}
//	printf("sum=%f\n", sum);
//
//	return 0;
//}

