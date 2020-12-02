#define _CRT_SECURE_NO_WARNINGS 1

#include "test.h"

//1.交换两个整型变量的值
//int main()
//{
//	int a, b;
//	printf("输入a b的值：\n");
//	scanf("%d %d", &a, &b);
//	Swap(&a, &b);
//	printf("交换后 a=%d b=%d：\n", a, b);
//
//	return 0;
//}
//void Swap(int* p1, int* p2)
//{
//	int temp;
//	temp = *p1;
//	*p1 = *p2;
//	*p2 = temp;
//}


//2.随机生成指定长度的字符串
//int main()
//{
//	int len;
//	char* buffer = NULL;
//	srand(time(0));    //设置随机数种子
//	printf("你想要多长的串？");
//	scanf("%d", &len);
//
//	buffer = (char*)malloc(len + 1);   //动态分配len+1个字节空间
//	if (buffer == NULL)exit(1);   //exit(1)分配失败 终止进程 返回0给操作系统
//
//	for (int i = 0; i < len; i++)    //产生随机串
//	{
//		buffer[i] = rand() % 26 + 'a';
//	}
//	buffer[len] = '\0';
//
//	printf("随机串：%s\n", buffer);
//	free(buffer);   //释放空间
//
//	return 0;
//}

//3.与指定数字相同的个数
//int main()
//{
//	int n;
//	int* a = NULL;
//	printf("输入n为多长的数字串？\n");
//	scanf("%d", &n);
//	a = (int*)malloc(n * sizeof(int)); //分配n个整型空间
//	printf("输入n个数字（每次输入一个后按回车）：\n");
//	for (int i = 0; i < n; i++)
//	{
//		scanf("%d", &a[i]);
//	}
//	
//	int x, sum = 0;
//	printf("输入要查找的数字：");
//	scanf("%d", &x);
//	for (int i = 0; i < n; i++)
//		if (x == a[i])
//			sum++;
//	printf("%d\n", sum);
//	free(a);
//
//	return 0;
//}

//4.在数组中查找元素
//int main()
//{
//	int m = 10;
//	int a[10];
//	printf("输入一个元素为10的数组：\n");
//	for (int i = 0; i < m; i++)
//		scanf("%d", &a[i]);
//	int x;
//	printf("输入要查找的元素：");
//	scanf("%d", &x);
//	int k = search(a, 6, x);
//	if (k == -1)
//		printf("未找到！\n");
//	else
//		printf("找到了，是数组中的第%d个元素：", k + 1);
//
//	return 0;
//}
//int search(const int* p, int n, int x)
//{
//	int pos = -1;
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


//5.