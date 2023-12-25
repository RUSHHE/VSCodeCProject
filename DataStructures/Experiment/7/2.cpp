/**
 * 做不了，太恶心了
*/
#include <stdio.h>
#define LISTINCREMENT 10 // 线性表增加分配空间的量
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAXSIZE 50
typedef int KeyType;
typedef int Status;
typedef struct
{
    char country[20]; // 国家名字
    KeyType mileage[20];
    int year[20];
    int growth[20];
    int index[20];
} RecType;

typedef struct
{
    RecType r[MAXSIZE]; // 不带监视哨
    int length;
} SqList;

Status ReadFiles(SqList &L, char filename[])
{
    FILE *fp = NULL;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("%s文件打开失败!\n", filename);
        return ERROR;
    }
    else
    {
        printf("%s\n已成功打开\n", filename);
        int n = 0;
        while (true)
        {
            fscanf(fp, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", L.r[n].country,
                   &L.r[n].year[0], &L.r[n].mileage[0], &L.r[n].year[1], &L.r[n].mileage[1], &L.r[n].year[2], &L.r[n].mileage[2], &L.r[n].year[3], &L.r[n].mileage[3],
                   &L.r[n].year[4], &L.r[n].mileage[4], &L.r[n].year[5], &L.r[n].mileage[5], &L.r[n].year[6], &L.r[n].mileage[6], &L.r[n].year[7], &L.r[n].mileage[7],
                   &L.r[n].year[8], &L.r[n].mileage[8], &L.r[n].year[9], &L.r[n].mileage[9], &L.r[n].year[10], &L.r[n].mileage[10], &L.r[n].year[11], &L.r[n].mileage[11],
                   &L.r[n].year[12], &L.r[n].mileage[12], &L.r[n].year[13], &L.r[n].mileage[13], &L.r[n].year[14], &L.r[n].mileage[14], &L.r[n].year[15], &L.r[n].mileage[15],
                   &L.r[n].year[16], &L.r[n].mileage[16], &L.r[n].year[17], &L.r[n].mileage[17]);
            if (L.r[n].year[1] - L.r[n].year[0] != 1)
            {
                break;
            }
            n++;
        }
        fclose(fp);
        L.length = n;
        for (int i = 0; i < L.length; i++)
        {
            for (int j = 0; j < L.length; j++)
            {
                L.r[i].index[j] = j;
            } 
        }
        return OK;
    }
}

void showOriginData(SqList L)
{
    printf("国家\t");
    for (int i = 0; i < L.length; i++)
    {
        if (L.r[0].year[i] - L.r[0].year[i - 1] != 1)
        {
            break;
        }
        printf("%d\t", L.r[i].year[i]);
    }
    printf("\n");
    for (int i = 0; i < L.length; i++)
    {
        printf("%s", L.r[i].country);
        for (int j = 0; j < L.length; j++)
        {
            printf("\t%d", L.r[i].mileage[j]);
        }
        printf("\n");
    }
}

void calculateGrowth(SqList &L)
{
    for (int i = 0; i < L.length; i++)
    {
        for (int j = 1; j < L.length; j++)
        {
            L.r[i].growth[j] = L.r[i].mileage[j] - L.r[i].mileage[j - 1];
        }
    }
}

// void sortByYear(SqList &L)
// {
//     SqList temp;
//     for (int i = 0; i < L.length; i++)
//     {
//         bool flag = FALSE;
//         for (int j = L.length - 1; j > i; j--)
//         {
//             if (L.r[j - 1].mileage)
//             {
//                 /* code */
//             }
            
//         }
//     }
// }

// void bubbleSort(SqList &L)
// {
//     for (int i = 0; i < L.length - 1; i++)
//     {
//         bool flag = FALSE;
//         for (int j = L.length - 1; j > i; j--)
//         {
//             if (L.r[j - 1].key > L.r[j].key)
//             {
//                 int temp = L.r[j - 1].key;
//                 L.r[j - 1].key = L.r[j].key;
//                 L.r[j].key = temp;
//                 flag = TRUE;
//             }
//         }
//         if (flag == FALSE)
//         {
//             return;
//         }
//     }
// }

int main()
{
    // while (true)
    // {
    //     printf("*****高铁里程系统*****\n");
    //     printf("1.导入数据\n");
    //     printf("2.查询数据\n");
    //     int choice;
    //     scanf("%d", &choice);
    //     switch (choice)
    //     {
    //     case 1:
    //         scanf("%s");
    //         break;
        
    //     default:
    //         break;
    //     }
    // }
    SqList L;
    ReadFiles(L, "/Users/rushhe/VSCodeCProject/DataStructures/Experiment/7/6_2_3_inputdata.txt");
    showOriginData(L);
    calculateGrowth(L);
    return 0;
}