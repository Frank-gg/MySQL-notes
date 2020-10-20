#include <stdio.h>

int main()
{
	//三个数从大到小排序
	//int a = 0;
	//int b = 0;
	//int c = 0;
	//scanf_s("%d%d%d", &a, &b, &c);
	//if (a < b)
	//{
	//	int temp = a;
	//	a = b;
	//	b = temp;
	//}
	//if (a < c)
	//{
	//	int temp = a;
	//	a = c;
	//	c = temp;
	//}
	//if (b < c)
	//{
	//	int temp = c;
	//	c = b;
	//	b = temp;
	//}
	//printf_s("%d %d %d\n", a, b, c);

	//判断100内3的倍数
	/*int i = 0;
	int j = 0;
	while (i <= 100)
	{
		j = j++;
		i = j * 3;
		printf("%d\n", i);
	}*/

	//判断素数
	int i = 0;
	int count = 0;
	for (i = 100; i <= 200; i++)
	{
		int j = 0;
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				break;
			}
		}
		if (j == i)
		{
			count++;
			printf("%d", i);
		}
	}
	printf("\nconut=%d\n", count);
	return 0;
}