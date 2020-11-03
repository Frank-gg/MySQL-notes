#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

//int main()
//{
//	//short s = 0;
//	//int a = 10;
//	//printf("%d\n", sizeof(s = a + 5));
//	//printf("%d\n", s);
//
//	//++a 前置++，先++，后使用
//	//a++ 后置++ 先使用 再++
//
//	//int a = (int)3.14;//强制类型转换（）
//
//	return 0;
//}

//int main()
//{
//	int arr[10] = { 0 };
//	char ch[10] = { 0 };
//	printf("%d\n", sizeof(arr));
//	printf("%d\n", sizeof(ch));
//	test1(arr);
//	test2(ch);
//
//	return 0;
//}
//int test1(int arr[])
//{
//	printf("%d\n", sizeof(arr));
//}
//int test2(char ch[])
//{
//	printf("%d\n", sizeof(ch));
//}

//int main()
//{
//	int i = 0, a = 0, b = 2, c = 3, d = 4;
//	i = a++ && ++b && d++;
//	//i = a++ || ++b || d++;
//	printf("a=%d\n b=%d\n c=%d\n d=%d\n", a, b, c, d);
//	return 0;
//}

//int main()
//{
//	int a = 10;
//	int b = 20;
//	int max = 0;
//
//	/*if (a > b)
//		max = a;
//	else
//		max = b;*/
//	max = (a > b ? a : b);
//
//	return 0;
//}

//创建一个结构体类型-struct stu
//struct stu
//{
//	char name[20];
//	int age;
//	char id[20];
//};
//int main()
//{
//	int a = 10;
//	//使用struct stu这个类型创建了一个学生对象s1，并初始化
//	struct stu s1 = { "张三",20,"20192021" };
//	struct stu* ps = &s1;
//	
//	printf("%s\n", ps->name);
//	printf("%d\n", ps->age);
//
//	/*printf("%s\n", s1.name);
//	printf("%d\n", s1.age);
//	printf("%s\n", s1.id);*/
//	
//	/*printf("%s\n", (*ps).name);
//	printf("%d\n", (*ps).age);*/
//
//
//	return 0;
//}

//整形提升实例
int main()
{
	char a = 0xb6;
	short b = 0xb600;
	int c = 0xb6000000;
	if (a == 0xb6)
		printf("a");
	if(b == 0xb600)
		printf("b");
	if(c == 0xb6000000)
		printf("c");

	return 0;
}