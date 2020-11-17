#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

//1.求两个数的最大公约数
//int main()
//{
//    int m, n, temp, i;
//    printf("输入两个正整数，中间空一格:");
//    scanf("%d%d", &m, &n);
//    if (m < n)  /*比较大小，使得m中存储大数，n中存储小数*/
//    { /*交换m和n的值*/
//        temp = m;
//        m = n;
//        n = temp;
//    }
//    //for (i = n; i > 0; i--)  /*按照从大到小的顺序寻找满足条件的自然数*/
//    //    if (m % i == 0 && n % i == 0)
//    //    {/*输出满足条件的自然数并结束循环*/
//    //        printf("%d 和 %d 最大公约数是 : %d\n", m, n, i);
//    //        break;
//    //    }
//    while (1)
//    {
//        temp = m % n;
//        if (temp != 0)
//        {
//            m = n;
//            n = temp;
//        }
//        else
//            printf("最大公约数为：%d", n);
//            break;
//    }
//    return 0;
//}

//2.将一个整数 逆序后输出
//int main()
//{
//	int m, n, p, q, r;
//	printf("请输入要逆序的4位整数m：\n");
//	scanf("%d", &m);
//
//	n = m % 10;
//	p = m / 10 % 10;
//	q = m / 100 % 10;
//	r = m / 1000 % 10;
//	m = r + q * 10 + p * 100 + n * 1000;
//	printf("逆序后的整数m为：%d", m);
//
//	return 0;
//}

//3.判断闰年
//int main()
//{
//	int year;
//	printf("请输入年份year：\n");
//	scanf("请输入年份：%d", &year);
//	//闰年是400的倍数 或者 是4的倍数但不是100的倍数
//	if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
//		printf("%d年是闰年！", year);
//	else
//		printf("%d年不是闰年！", year);
//
//	return 0;
//}

//4.求三个数中的最大值并按从小到大的顺序输出
//int main()
//{
//	int a, b, c, temp;
//	printf("请输入要比较的数a,b,c\n");
//	scanf("%d%d%d", &a, &b, &c);
//
//	if (a > b)
//	{
//		temp = a;
//		a = b;
//		b = temp;
//	}
//	if (a > c)
//	{
//		temp = a;
//		a = c;
//		c = temp;
//	}
//	if (b > c)
//	{
//		temp = b;
//		b = c;
//		c = temp;
//	}
//	printf("从大到小输出：%d %d %d\n", a, b, c);
//
//	return 0;
//}

//5.输入日期y年m月n日，输出今天是y年的第几天
//int main()
//{
//	int y, m, n, days;
//	int arr[12] = { 31,60,91,121,152,182,213,244,274,305,335,366 };
//	printf("输入日期（格式2000年5月6日--》2000 5 6）\n");
//	scanf("%d%d%d", &y, &m, &n);
//
//	if (y % 400 == 0 || y % 4 == 0 && y % 100 != 0)
//		days = arr[m - 2] + n;
//	else
//		days = arr[m - 2] + n - 1;
//	printf("%d年%d月%d日是今年的第%d天", y, m, n, days);
//
//	return 0;
//}

