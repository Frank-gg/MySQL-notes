#include <stdio.h>
#include <math.h>

int main()
{
	int num = 0;
	while (num <= 100)
	{
		if (num % 2 != 0)
			printf("%dÊÇÆæÊý\n", num);
		num++;
	}

	return 0;
}
