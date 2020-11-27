#define _CRT_SECURE_NO_WARNINGS 1
#define CN 3
#define SN 10

#include <stdio.h>
#include <string.h>


//1.多个班级某课程的成绩管理
//int main()
//{
//	int cs[CN + 1][SN + 1];//存放CN个班级学生的成绩
//	double sum[CN + 1] = { 0 }, ave[CN + 1];  //存放各班学生总分、平均分
//
//	printf("输入%d个班级%d个学生的成绩：\n", CN, SN);
//	for (int i = 1; i <= CN; i++)
//	{
//		for (int j = 1; j <= SN; j++)
//		{
//			scanf("%d", &cs[i][j]);
//			sum[i] += cs[i][j];
//		}
//	}
//
//	int max[CN + 1], maxk[CN + 1];
//	for (int i = 1; i <= CN; i++)
//	{//求各班级的平均分，假设第一名成绩为最高分
//		max[i] = cs[i][1];
//		maxk[i] = 1;
//		ave[i] = sum[i] / SN;
//	}
//	for (int i = 1; i <= CN; i++)
//	{//找出各班级最高分
//		for (int j = 2; j <= SN; j++)
//		{
//			if (cs[i][j] > max[i])
//			{
//				max[i] = cs[i][j];
//				maxk[i] = j;
//			}
//		}
//	}
//
//	int cmax, cmaxk, avemaxk;//分别存放所有学生的最高分、最高分班号、平均成绩最高的班号
//	//求出所有学生的最高分及最高分所在班号，同时求出平均成绩最高的班号
//	cmax = max[1], cmaxk = 1, avemaxk = 1;
//	for (int i = 2; i <= CN; i++)
//	{
//		if (max[i] > cmax)
//		{
//			cmax = max[i];
//			cmaxk = i;
//		}
//		if (ave[i] > ave[avemaxk])
//			avemaxk = i;
//	}
//	
//	//输出各个班级的班号、平均成绩、最高分同学的序号及分数
//	printf("班级的班号\t平均成绩\t最高分\t最高分序号\n");
//	for (int i = 1; i <= CN; i++)
//		printf(" %4d\t\t%.2f\t\t%d\t%4d\n", i, ave[i], max[i], maxk[i]);
//	//输出几个班级中的最高分所在的班级、其在班级的序号及其分数
//	printf("最高分%d班 序号是%d 分数为%d\n", cmaxk, maxk[cmaxk], cmax);
//	//输出平均成绩最高的班级的班号及其平均成绩
//	printf("平均成绩最高的班号为：%d 平均成绩为：%.2f\n", avemaxk, ave[avemaxk]);
//
//	return 0;
//}

//2.字符串的简单加密
//int main()
//{
//	char text[80];
//	int len;
//
//	printf("输入要加密的字符串:");
//	gets(text);
//	len = strlen(text);
//	for (int i = 0; i < len; i++)
//	{//加密处理
//		if (text[i] >= 'a' && text[i] < 'z' || text[i] >= 'A' && text[i < 'Z'])
//			text[i]++;
//		else if (text[i] == 'z')
//			text[i] = 'a';
//		else if (text[i] == 'z')
//			text[i] = 'A';
//	}
//	printf("加密后字符串为:  %s\n", text);
//
//	return 0;
//}

//3.系统登陆验证的实现
int main()
{//正确的id号和密码分别为：“fggg”，“123456”
	char id[31], psw[21];  //存放输入id与密码
	int n = 3, f = 0;   //存放输入id、密码次数、以及是否正确输入（0表示不正确）
	do
	{
		n--;
		printf("输入你的id：");
		gets(id);
		printf("输入你的密码：");
		gets(psw);
		if (strcmp(id, "fggg") == 0 && strcmp(psw, "123456") == 0)
		{
			printf("welcome!\n");
			f = 1;
			break;
		}
		else
		{
			if (n > 0)
				printf("你还有%d次机会输入id与密码！\n", n);
		}
	} while (n > 0);
	if (f == 0)
		printf("sorry!bye!\n");

	return 0;
}