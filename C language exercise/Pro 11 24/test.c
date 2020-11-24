#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>

//1.打印斐波那契数列
//int main()
//{
//	int f1, f2, f;
//	f1 = f2 = 1;
//	printf("%5d %5d", f1, f2);
//	for (int i = 3; i <= 20; i++)
//	{
//		f = f1 + f2;
//		printf("%5d", f);
//		if (i % 5 == 0)
//			printf("\n");
//		f1 = f2;
//		f2 = f;
//	}
//
//	return 0;
//}

//2.将正整数m与n能被17整除的数累加
//int main()
//{
//	int m, n, i, sum = 0;
//
//	printf("输入m与n的值（0<m<n<1000）:\n");
//	scanf_s("%d %d", &m, &n);
//	
//	for (i = m; i <= n; i++)
//	{
//		if (i % 17 == 0)
//		{
//			sum += i;
//		}
//	}
//	printf("%d与%d之间能被17整除的整数和为：%d", m, n, sum);
//
//	return 0;
//}

//3.利用函数，求1-n的和
//int main()
//{
//	int n, s;
//	printf("请输入n值\n");
//	scanf_s("%d", &n);
//
//	s = sumN(n);
//
//	printf("1到%d的和是：%d", n, s);
//	return 0;
//}
//int sumN(int n)
//{
//	int sum = 0;
//	int i;
//	for (i = 1; i <= n; i++)
//	{
//		sum += i;
//	}
//
//	return sum;
//}

//4.利用函数交换值
//int main()
//{
//	int x = 5, y = 10;
//	printf("交换前x=%d，y=%d", x, y);
//	swap(&x, &y);
//	printf("交换后x=%d，y=%d", x, y);
//
//	return 0;
//}
//int swap(int* x, int* y)
//{
//	int temp;
//	temp = *x;
//	*x = *y;
//	*y = temp;
//}

