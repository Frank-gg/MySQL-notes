#define _CRT_SECURE_NO_WARNINGS 1
#define N 10

#include "test.h"

//1.求平均年龄及大于平均年龄的学生
//int main()
//{
//	int age[N], n, k;  //分别储存年龄、学生人数、大于平均分的学生人数
//	double ave;
//
//	n = Input(age);
//	ave = GetAverage(age, n);
//	k = Count(age, n, ave);
//	printf("平均年龄是：%.1f\n 大于平均年龄的学生人数：%d\n", ave, k);
//
//	return 0;
//}
//int Input(int arr[])
//{
//	int n = 0, a;
//
//	while (1)
//	{
//		scanf("%d", &a);
//		if (a <= 0)
//			break;
//		arr[n++] = a;
//	}
//	
//	return n;
//}
//double GetAvergae(int arr[], int size)
//{
//	int i;
//	double ave, sum = 0;
//	
//	for (i = 0; i < size; ++i)
//	{
//		sum += arr[i];
//	}
//	ave = sum / size;
//
//	return ave;
//}
//int Count(int arr[], int size, double ave)
//{
//	int k = 0, i;
//	for (i = 0; i < size; i++)
//	{
//		if (arr[i] > ave)
//			k++;
//	}
//
//	return k;
//}

//2.输入n（n<=10）及n个整数，输出最大整数及其位序
//int main()
//{
//	int n, i, max1;
//	int arr[N];
//
//	printf("输入整数个数n为：");
//	scanf("%d", &n);
//
//	for (i = 0; i < n; i++)
//	{
//		printf("给第%d个整数赋值为：", i + 1);
//		scanf("%d", &arr[i]);
//	}
//
//	max1 = 0;
//	for (int i = 1; i < n; i++)
//	{
//		if (arr[i] > arr[max1])
//			max1 = i;
//	}
//	printf("最大整数为：%d，位序为：%d\n", arr[max1], max1 + 1);
//
//	return 0;
//}

//3.利用排序法将n个整数排列成非递减序列
//int main()
//{
//	int a[N];
//
//	//输入N个元素
//	printf("输入%d个整数：\n", N);
//	for (int i = 0; i < N; i++)
//		scanf("%d", &a[i]);
//	SelectSort(a, N);
//
//	printf("排序后的结果为：\n");
//	for (int i = 0; i < N; i++)
//		printf("%d ", a[i]);
//	printf("\n");
//
//	return 0;
//}
//void SelectSort(int r[], int n)
//{
//	int i, j, mink;
//	for (i = 0; i < n - 1; i++)
//	{
//		mink = i;
//		for (j = i + 1; j < n; j++)
//		{
//			if (r[mink] > r[j])
//				mink = j;
//		}
//		if (mink != i)
//		{
//			int t;
//			t = r[i];
//			r[i] = r[mink];
//			r[mink] = t;
//		}
//	}
//}

//4.输入成绩 在10个学生中查找是否有相同的值
//int main()
//{
//	int cScore[N], x, t;
//
//	printf("输入数组cScore的%d个元素：\n", N);
//	Input(cScore, N);
//	printf("请输入要查找的数据x：");
//	scanf("%d", &x);
//	t = Search(cScore, N, x);
//	if (t != -1)
//		printf("查找%d成功，他的序号为%d\n", x, t);
//	else
//		printf("查找%d失败");
//
//	return 0;
//}
//void Input(int a[], int n)
//{
//	int i;
//	for (i = 0; i < n; i++)
//		scanf("%d", &a[i]);
//}
//int Search(int a[], int n, int x)
//{
//	int i;
//	i = 0;
//	while (i < n)
//	{
//		if (a[i] == x)
//			break;
//		i++;
//	}
//	if (i < n)
//		return i + 1;
//	return -1;
//}