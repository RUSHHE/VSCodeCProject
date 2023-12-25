#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define LISTINCREMENT 10 // 线性表增加分配空间的量
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAXSIZE 50 // 顺序表的最大长度
typedef int Status;
typedef int KeyType; // 将关键字类型定义为整型
// 各国高铁里程信息类型
typedef struct
{
	char courtry[20];	 // 国家名称
	KeyType mileage[20]; // 历年高铁里程
	int year[20];		 // 年度，时间跨度为20年
	int growth[20];		 // 年建设里程
	int index[20];		 // 年度排行索引，某一排名对应的数据在r[ ]中的位置序号
} RecType;
typedef struct
{
	RecType r[MAXSIZE + 1]; // 一般情况将r[0]闲置
	int length;				// 顺序表长度
} SqList;

int HSR_Menu_Show()
// 显示菜单选项，读取菜单选择输入，判断其输入值是否在0-8之间，HSR：High-Speed Railway
{
	int key, flag = 1;
	printf("\n===================世界高铁里程排名系统=======================\n");
	printf("*                                                            *\n");
	printf("*  1:导入数据         2:显示原始数据      3:计算年建设里程   *\n");
	printf("*  4:按年排序         5:显示排序结果      6:显示年建设里程   *\n");
	printf("*  7:保存年建设里程   8:保存排序结果      0:退出             *\n");
	printf("*                                                            *\n");
	printf("==============================================================\n");
	printf("根据菜单提示进行输入：");
	while (flag)
	{
		scanf("%d", &key);
		if (key >= 0 && key <= 8)
		{
			flag = 0;
			return key;
		}
		else
		{
			printf("请先读入数据！\n");
		}
	}
}

int HSR_SqList_Read(SqList &L, char fileName[])
// 文本文档数据导入，HSR：High-Speed Railway
{
	FILE *fp = NULL;
	int i, n = 0, k;
	int flag = 1;
	if ((fp = fopen(fileName, "r")) == NULL)
	{
		printf("%s文件打开失败!", fileName);
		return ERROR;
	}
	else
	{
		printf("文件打开成功!");
		while (flag)
		{
			n++;
			fscanf(fp, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", L.r[n].courtry,
				   &L.r[n].year[0], &L.r[n].mileage[0], &L.r[n].year[1], &L.r[n].mileage[1], &L.r[n].year[2], &L.r[n].mileage[2], &L.r[n].year[3], &L.r[n].mileage[3],
				   &L.r[n].year[4], &L.r[n].mileage[4], &L.r[n].year[5], &L.r[n].mileage[5], &L.r[n].year[6], &L.r[n].mileage[6], &L.r[n].year[7], &L.r[n].mileage[7],
				   &L.r[n].year[8], &L.r[n].mileage[8], &L.r[n].year[9], &L.r[n].mileage[9], &L.r[n].year[10], &L.r[n].mileage[10], &L.r[n].year[11], &L.r[n].mileage[11],
				   &L.r[n].year[12], &L.r[n].mileage[12], &L.r[n].year[13], &L.r[n].mileage[13], &L.r[n].year[14], &L.r[n].mileage[14], &L.r[n].year[15], &L.r[n].mileage[15],
				   &L.r[n].year[16], &L.r[n].mileage[16], &L.r[n].year[17], &L.r[n].mileage[17]);
			if (L.r[n].year[1] - L.r[n].year[0] != 1) // 判断中止条件，年没有连续
			{
				flag = 0;
			}
		}
		fclose(fp);
		L.length = n - 1;
		for (k = 0; k < 20; k++) // 遍历给索引数组赋值为原数组的下标
		{
			for (i = 1; i <= L.length; i++)
			{
				L.r[i].index[k] = i;
			}
		}
		return OK;
	}
}

void HSR_SqList_Output_GR(SqList &L)
// 显示各国高铁年建设里程数
{
	int i, k, num_year;
	for (i = 0; i < 20; i++) // 将年度值转化为年度数组索引值
	{
		{
			if (L.r[1].year[i] == 0)
			{
				num_year = i;
				break;
			}
		}
		for (k = 0; k < num_year; k++)
		{
			printf("\n%d年世界各国高铁年建设里程数\n", L.r[1].year[k]);
			printf("序号     国家           年建设里程数（公里）\n");
			for (i = 1; i <= L.length; i++)
			{
				printf("%-2d  %-15s    %-6d%\n", i, L.r[i].courtry, L.r[i].growth[k]);
			}
		}
	}
}

void HSR_SqList_Output(SqList &L)
// 显示各国高铁里程数排名
{
	int i, k, num_year;
	for (i = 0; i < 20; i++) // 将年度值转化为年度数组索引值
		if (L.r[1].year[i] == 0)
		{
			num_year = i;
			break;
		}
	for (k = 0; k < num_year; k++)
	{
		printf("\n%d年世界各国高铁里程排名\n", L.r[1].year[k]);
		printf("排名     国家           里程数(公里)\n");
		for (i = 1; i <= L.length; i++)
		{
			printf(" %-6d  %-12s      %-6d\n", i, L.r[L.r[i].index[k]].courtry, L.r[L.r[i].index[k]].mileage[k]);
		}
	}
}

void HSR_SqList_Output_OR(SqList &L)
// 显示各国高铁里程原始读入数据，所有年度数据
{
	int i, num_char, k, num_year;
	for (k = 0; k < 20; k++) // 查找数据中年度信息
	{
		if (L.r[1].year[k] == 0)
		{
			num_year = k;
			break;
		}
	}
	for (k = 0; k < num_year; k++)
	{
		printf("\n世界各国高铁里程%d年:\n", L.r[1].year[k]);
		printf("序号     国家           里程数(公里)\n");
		for (i = 1; i <= L.length; i++)
		{
			printf(" %-6d  %-12s      %-6d\n", i, L.r[i].courtry, L.r[i].mileage[k]);
		}
	}
}

void HSR_Bubble_Sort(SqList &L)
// 在冒泡排序的基础上采用索引排序的方式对表L进行各年度里程数的排序
{
	int i, j, k, temp;
	for (k = 0; k < 20; k++) // 逐年进行排序
	{
		for (i = 1; i <= L.length; i++) // 控制每趟排序
		{								// 每趟排序开始时设置交换标志变量值为假
			for (j = 1; j <= L.length - i; j++)
			{
				if (L.r[L.r[j].index[k]].mileage[k] < L.r[L.r[j + 1].index[k]].mileage[k]) // 如果小于后者，则交换
				{
					temp = L.r[j].index[k];
					L.r[j].index[k] = L.r[j + 1].index[k];
					L.r[j + 1].index[k] = temp;
				}
			}
		}
	}
}

int HSR_SqList_Calculate(SqList &L)
// 计算表L中各年建设里程数
{
	int i, k;
	for (k = 1; k < 19; k++)
	{
		for (i = 1; i <= L.length; i++)
		{
			L.r[i].growth[k] = L.r[i].mileage[k] - L.r[i].mileage[k - 1]; // 计算年建设里程
		}
	}
	return OK;
}

void HSR_SqList_Save(SqList &L, char *fileName, char *fileName_saved)
// 保存排序结果到本地磁盘
{
	FILE *fp = NULL;
	int i, num_char, k, num_year;
	num_char = strlen(fileName);
	strncpy(fileName_saved, fileName, num_char - 4);
	strcat(fileName_saved, "_Sorted.txt"); // 保存结果到磁盘txt文本文件中，名称为当前txt文本文档增加后缀 _sorted
	if ((fp = fopen(fileName_saved, "w")) == NULL)
	{
		printf("文件打开失败!");
	}
	else
	{							 // 保存结果到磁盘txt文本文件中
		for (k = 0; k < 20; k++) // 查找数据中年度信息
		{
			if (L.r[1].year[k] == 0)
			{
				num_year = k;
				break;
			}
		}
		for (k = 0; k < num_year; k++)
		{
			fprintf(fp, "\n%d年世界各国高铁里程排名\n", L.r[1].year[k]);
			fprintf(fp, "排名     国家           里程数(公里)\n");
			for (i = 1; i <= L.length; i++)
			{
				fprintf(fp, " %-6d  %-12s      %-6d\n", i, L.r[L.r[i].index[k]].courtry, L.r[L.r[i].index[k]].mileage[k]);
			}
		}
		fclose(fp);
	}
}

void HSR_SqList_Save_GR(SqList &L, char *fileName, char *fileName_saved)
// 保存年建设里程到本地磁盘
{
	FILE *fp = NULL;
	int i, num_char, k, num_year;
	num_char = strlen(fileName);
	strncpy(fileName_saved, fileName, num_char - 4);
	strcat(fileName_saved, "_Growth.txt"); // 保存结果到磁盘txt文本文件中，名称为当前txt文本文档增加后缀 _sorted
	if ((fp = fopen(fileName_saved, "w")) == NULL)
	{
		printf("文件打开失败!");
	}
	else
	{							 // 保存结果到磁盘txt文本文件中
		for (k = 0; k < 20; k++) // 查找数据中年度信息
		{
			if (L.r[1].year[k] == 0)
			{
				num_year = k;
				break;
			}
		}
		for (k = 0; k < num_year; k++)
		{
			fprintf(fp, "\n%d年世界各国高铁年建设里程数\n", L.r[1].year[k]);
			fprintf(fp, "序号     国家           年建设里程数（公里）\n");
			for (i = 1; i <= L.length; i++)
			{
				fprintf(fp, "%-2d        %-15s    %-6d%\n", i, L.r[i].courtry, L.r[i].growth[k]);
			}
		}
		fclose(fp);
	}
}

int main(int argc, char **argv)
{
	char fileName[300], fileName_saved[310], fileName_saved_GR[310];
	int status, year, flag = 1, key;
	SqList L; // 定义线性表，分配预定义大小的空间
	while (flag)
	{
		key = HSR_Menu_Show(); // 读取键盘的输入
		switch (key)
		{
		case 1:
			printf("请输入读取文件路径和名称：\n");
			scanf("%s", fileName);
			getchar();							   // 去掉输入流中的回车符
			status = HSR_SqList_Read(L, fileName); // 读取数据
			if (status == OK)
			{
				printf("数据读取完成，根据提示进行操作。\n");
			}
			break;
		case 2:
			if (L.r[1].year[0] == 0)
			{
				printf("请先读入数据！\n");
			}
			else
			{
				HSR_SqList_Output_OR(L);
			}
			break;
		case 3:
			if (L.r[1].year[0] == 0)
			{
				printf("请先读入数据！\n");
			}
			else
			{
				status = HSR_SqList_Calculate(L);
				if (status == OK)
				{
					printf("年建设里程计算完成，根据提示进行操作。\n");
				}
			}
			break;
		case 4:
			if (L.r[1].year[0] == 0)
			{
				printf("请先读入数据！\n");
			}
			else
			{
				HSR_Bubble_Sort(L);
				printf("按年排序完成，根据提示进行操作。\n");
			}
			break;
		case 5:
			if (L.r[1].year[0] == 0)
			{
				printf("请先读入数据！\n");
			}
			else
			{
				HSR_SqList_Output(L);
				printf("世界各国高铁排名显示完成，根据提示进行操作。\n");
			}
			break;
		case 6:
			if (L.r[1].year[0] == 0)
			{
				printf("请先读入数据！\n");
			}
			else
			{
				HSR_SqList_Output_GR(L);
				printf("世界各国高铁年建设里程显示完成，根据提示进行操作。\n");
			}
			break;
		case 7:
			if (L.r[1].year[0] == 0)
			{
				printf("请先读入数据！\n");
			}
			else
			{
				HSR_SqList_Save_GR(L, fileName, fileName_saved_GR);
				printf("世界各国高铁年建设里程保存完成，路径为：\n");
				printf("%s\n", fileName_saved_GR);
			}
			break;
		case 8:
			if (L.r[1].year[0] == 0)
			{
				printf("请先读入数据！\n");
			}
			else
			{
				HSR_SqList_Save(L, fileName, fileName_saved);
				printf("世界各国高铁里程排名保存完成，路径为：\n");
				printf("%s\n", fileName_saved);
			}
			break;
		case 0:
			flag = 0;
			printf("退出系统。");
			break;
		default:
			printf("菜单选择输入错误，请重新输入");
		}
	}
	return OK;
}