#include<stdio.h>
#include<Windows.h>
//int main()
//{
//    int i = 0, k = 0;
//    int count = 0;
//    for (i = 100; i <= 200; i++)
//    {
//        for (k = 2; k < i; k++)
//        {
//            if (i % k == 0)
//                break;
//        }
//        if (k == i)
//        {
//            printf("%d是素数\n", i);
//            count++;
//        }
//    }
//    printf("\n%4d", count);
//    system("pause");
//    return 0;
//}

//int main()
//{
//    int i = 0, k = 0;
//    int count = 0;
//    for (i = 101; i <= 200; i += 2)
//    {
//        for (k = 2; k < i; k++)
//        {
//            if (i % k == 0)
//                break;
//        }
//
//        if (k == i)
//        {
//            printf("%d是素数\n", i);
//            count++;
//        }
//    }
//    printf("\n%4d", count);
//    system("pause");
//    return 0;
//}

//int main()
//{
//    int i = 0, k = 0;
//    int count = 0;
//    for (i = 100; i <= 200; i += 2)
//    {
//        for (k = 2; k < i / 2; k++)
//        {
//            if (i % k == 0)
//                break;
//        }
//        if (k == i)
//        {
//            printf("%d是素数\n", i);
//            count++;
//        }
//    }
//    printf("\n%4d", count);
//    system("pause");
//    return 0;
//}

//int main()
//{
//    int i = 0;
//    int count = 0;
//    for (i = 100; i <= 200; i++)
//    {
//        int j = 0;
//        for (j = 2; j <= sqrt(i); j++)
//        {
//            if (i % j == 0)
//                break;
//        }
//        if (j > sqrt(i))
//        {
//            printf("%d ", i);
//            count++;
//        }
//    }
//    printf("\ncount = %d\n", count);
//    return 0;
//}


//int main()
//{
//    int i = 0;
//    int count = 0;
//    for (i = 101; i <= 200; i += 2)
//    {
//        int j = 0;
//        for (j = 2; j <= sqrt(i); j++)
//        {
//            if (i % j == 0)
//                break;
//        }
//        if (j > sqrt(i))
//        {
//            count++;
//            printf("%d ", i);
//        }
//    }
//    printf("\ncount = %d\n", count);
//    return 0;
//}

int main()
{
	int i, j, a[100], e;
	for (i = 0; i < 100; i++)
		a[i] = i + 1;
	for (i = 0; i < 100; i++)
	{
		j = i - 1;
		while (j > 1)
		{
			e = a[i] % j;
			if (e == 0)a[i] = 0;
			j = j - 1;
		}
	}
	for (j = 1; j < 100; j++)
	{
		if (a[j] != 0)
		{
			printf("%2d ", a[j]);
		}
	}
	return 0;
}