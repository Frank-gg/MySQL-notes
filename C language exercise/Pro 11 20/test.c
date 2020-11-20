#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

//1.判断一个整数m是否是素数（质数）,并输出判断结果
//int main()
//{
//	int m, i;
//	printf("请输入需要判断的数m:\n");
//	scanf("%d", &m);
//
//	for (i = m - 1; i > 2; i--)
//	{
//		if (m % i != 0)
//		{
//			continue;
//		}
//		else
//			printf("%d不是质数", m);
//	}
//	printf("%d是质数", m);
//
//	return 0;
//}

//2.输出1~100之间的素数
//int main()
//{
//    int i, j;
//    for (i = 1; i <= 100; i++)
//    {
//        for (j = 2; j < i; j++)
//        {
//            if (i % j == 0)
//                break;
//        }
//        if (i == j)
//            printf("%d ", i);
//    }
//
//    return 0;
//}

//3.输出所有水仙花
//int main()
//{
//	int m, g, s, b;
//
//	for (m = 100; m < 1000; m++)
//	{
//		g = m % 10;
//		s = m / 10 % 10;
//		b = m / 100 % 10;
//		if (m == g * g * g + s * s * s + b * b * b)
//			printf("%4d", m);
//	}
//
//	return 0;
//}

//4.找零钱问题
//int main()
//{
//	int x;
//	int ones, twos, fives;
//
//	printf("输入钱数：\n");
//	scanf("%d", &x);
//	printf("找零方案有：\n");
//	for (ones = 1; ones < x * 10; ones++)
//	{
//		for (twos = 1; twos < x * 10 / 2; twos++)
//		{
//			for (fives = 1; twos < x * 10 / 5; fives++)
//			{
//				if (ones + twos * 2 + fives * 5 == x * 10)
//				{
//					printf("1角%d枚，2角%d枚，5角%d枚\n", ones, twos, fives);
//				}
//			}
//		}
//	}
//
//	return 0;
//}