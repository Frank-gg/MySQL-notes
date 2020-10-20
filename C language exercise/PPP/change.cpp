#include <stdio.h>

int main()
{
	//交换两个整形变量
	int a = 3;
	int b = 5;
	printf("交换前：a=%d b=%d", a, b);

	a = a + b;
	b = a - b;
	a = a - b;
	printf("交换后：a=%d b=%d", a, b);

	return 0;
}