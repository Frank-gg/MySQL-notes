//青蛙过河

#include <stdio.h>
#include "test1109.h"

int main(void)
{
	int h, y;
	scanf_s("%d %d", &h, &y);
	printf("%ld\n", f(h, y));

	return 0;
}

long long f(int h, int y);
{
	long long result = y + 1;//河中石墩数为0时
	for (int i = 1; i <= h; i++)
	{
		result = 2 * result;//直接自底向上推导
	}

	return result;
}