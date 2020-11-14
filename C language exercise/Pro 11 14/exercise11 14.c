#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <math.h>

//struct corrd
//{
//	int x;
//	int y;
//}c1,c2;
//
//int main() 
//{
//	double distance;//两点间的距离
//
//	printf("请输入第一个点坐标：");
//	scanf("%d %d", &c1.x, &c1.y);
//	printf("请输入第二个点坐标：");
//	scanf("%d %d", &c2.x, &c2.y);
//
//	int xdiff = c1.x - c2.x;
//	int ydiff = c1.y - c2.y;
//	distance = sqrt(xdiff * xdiff + ydiff * ydiff);
//	printf("两点间的距离是：%f\n", distance);
//
//	return 0;
//}

//计算结构体变量内存空间大小并输出结构成员的起始地址
struct Smaple
{
	short int n;
	char c[10];
	float f;
	double b;
}s;

int main()
{
	printf("变量s所占字节数为：%d个字节\n", sizeof(s));
	printf("结构成员  地址\n");
	printf("   n  %X\n", &s.n);
	printf("   c  %X\n", s.c);
	printf("   f  %X\n", &s.f);
	printf("   b  %X\n", &s.b);

	return 0;
}