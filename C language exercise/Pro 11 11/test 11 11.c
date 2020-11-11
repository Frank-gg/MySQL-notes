#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//int main()
//{
//	int arr[10] = { 0 };
//	int* p = arr;//数组名-首元素地址
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		*(p + i) = 1;
//	}
//
//	return 0;
//}

//int* test()
//{
//	int a = 10;
//	return &a;
//}
//int main()
//{
//	int* p = test();
//	printf("%d\n", *p);
//
//	return 0;
//}

//交换两个数
//int main()
//{
//	int x = 4, y = 6;
//	swap(&x, &y);
//	printf("x=%d y=%d\n", x, y);
//	
//	return 0;
//}
//
//int swap(int* p1, int* p2)
//{
//	int temp = *p1;
//	*p1 = *p2;
//	*p2 = temp;
//}

//随机生成指定长度的字符串
//int main()
//{
//	int len;
//	char* buffer = NULL;
//	srand(time(0));  //用当前时间来设定rand函数所用的随机数产生演算法的种子值//srand设置随机数种子，Time(0)是得到当前时时间值
//	printf("你想要多长的串？");
//	scanf("%d", &len);
//
//	buffer = (char*)malloc(len + 1);
//	if (buffer == NULL)exit(1);
//
//	for (int i = 0; i < len; i++)
//	{
//		buffer[i] = rand() % 26 + 'a';
//	}
//	buffer[len] = '\0';
//
//	printf("随机串：%s\n", buffer);
//	free(buffer);
//
//	return 0;
//}

//int main()
//{
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int i = 0;
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int* p = arr;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d  ", *p);
//		p = p + 1;
//	}
//
//	return 0;
//}

//求字符串长度
//int main()
//{
//	//strlen -求字符串长度
//	//递归-模拟实现strlen-计数器的方式1，递归的方式2
//
//	char arr[] = "bit";
//	int len = my_strlen(arr);
//	printf("%d\n", len);
//
//	return 0;
//}
//
//int my_strlen(char* str)
//{
//	char* start = str;
//	char* end = str;
//	while (*end != '\0')
//	{
//		end++;
//	}
//	return end - start;
//}

//int main()
//{
//	int arr[10] = { 0 };
//	printf("%p\n", arr);//地址-首元素的地址
//	printf("%p\n", &arr[0]);
//	//1.&arr—&数组名-数组名不是首元素地址-数组名表示整个数组(整个数组的地址)
//	//2.sizeof(arr)-sizeof(数组名)-数组名表示整个数组-sizeof(arr)计算整个数组的大小
//	//其余时刻 arr表示首地址
//
//	return 0;
//}

//与指定数字相同的数的个数
int main()
{
	int n;
	int* a = NULL;
	scanf("%d", &n);
	a = (int*)malloc(n * sizeof(int));   //动态分配n个整型空间
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int x, sum = 0;
	scanf("%d", &x);
	for (int i = 0; i < n; i++)
		if (x == a[i])
			sum++;
	printf("%d\n", sum);
	free(a);                      //释放a指针指向的n个整型空间

	return 0;
}