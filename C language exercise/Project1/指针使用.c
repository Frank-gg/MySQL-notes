//#include <stdio.h>
//#include <string.h>
//
//struct Book
//{
//	char name[20];
//	short price;
//};
//
//int main()
//{
//	//利用结构体类型--创建一个该类型的结构体变量
//	struct Book b1 = { "C语言程序设计", 50 };
//	struct Book* pb = &b1;
//	//更改结构体类型中的变量
//	strcpy(b1.name, "C++");//字符串拷贝-库函数-string.h
//	b1.price = 15;
//	
//	printf("书名：%s\n", pb->name);
//	printf("价格：%d\n", pb->price);
//	//printf("书名：%s\n", (*pb).name);
//	//printf("价格：%d\n", (*pb).price);
//	//printf("书名：%s\n", b1.name);
//	//printf("价格：%d\n", b1.price);
//	
//	return 0;
//}