#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

//1.计算圆的面积
//int main()
//{
//	double radius, aera;
//	printf("请输入一个圆的半径：\n");
//	scanf("%lf", &radius);
//
//	aera = 3.14159 * radius * radius;//计算圆的面积
//
//	printf("半径为%.2f的圆的面积是：%.2f\n", radius, aera);
//
//	return 0;
//}

//2.计算1 - n的和
//int main()
//{
//	int sum = 0, n;
//	printf("请输入n的值：\n");
//	scanf("%d", &n);
//
//	sum = (n + 1) * n / 2;
//
//	printf("1到%d的和为：%d", n, sum);
//
//	return 0;
//}

//3.在数组中查找元素
//int main()
//{
//	int a[6] = { 1,5,2,3,9,7 };
//	int x;
//	printf("请输入要查找的元素：");
//	scanf("%d", &x);
//	int k = search(a, 6, x);
//	if (k == -1)
//	{
//		printf("未找到！\n");
//	}
//	else
//		printf("找到了，是数组中第%d个元素：", k + 1);
//
//	return 0;
//}
//int search(const int* p, int n, int x)
//{//在数组中找元素为x的元素
// //若找到了返回下标；找不到，返回-1
//	int pos;
//	for (int i = 0; i < n; i++)
//	{
//		if (p[i] == x)
//		{
//			pos = i;
//			break;
//		}
//	}
//	return pos;
//}

