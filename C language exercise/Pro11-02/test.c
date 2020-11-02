#include <stdio.h>

//交换两个变量的值
//int mian()
//{
//	int a = 3;
//	int b = 5;
//	//1.创建临时变量
//	//int tmp = 0;
//	//printf("%d%d", a, b);
//	//tmp = a;
//	//a = b;
//	//b = tmp;
//
//	//2.加减法-可能会溢出
//	//a = a + b;
//	//b = a - b;
//	//a = a - b;
//
//	//3.异或的方法
//	a = a ^ b;
//	b = a ^ b;
//	a = a ^ b;
//
//	printf("a=%d b=%d\n", a, b);
//	return 0;
//}

//求一个整数存储在内存中的二进制中1的个数
//方法1
//int main()
//{
//	int num = 0;
//	int count = 0;
//	scanf_s("%d", &num);
//	//统计num的补码中有几个1
//	while (num)
//	{
//		if (num % 2 == 1)
//			count++;
//		num = num / 2;
//	}
//	printf("%d\n", count);
//	return 0;
//}

//方法2
int main()
{
	int num = -1;
	int i = 0;
	int count = 0;
	/*for (i = 0; i < 32; i++)
	{
		if (((num >> i) & 1) == 1)
			count++;
	}*/
	while (num)
	{
		count++;
		num = num & (num - 1);
	}
	printf("%d\n", count);
	return 0;
}