#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
typedef int KeyType;
typedef int InfoType;
typedef struct
{
    KeyType key;
    InfoType otherinfo;
} RecdType;
typedef struct
{
    RecdType *elem;
    int length;
} SSTable;

Status CreateSSTable(SSTable &ST, int n)
{
    ST.elem = (RecdType *)malloc(MAXSIZE * sizeof(RecdType));
    if (!ST.elem)
    {
        return OVERFLOW;
    }
    ST.length = n;
    for (int i = 0; i < ST.length; i++)
    {
        scanf("%d", &ST.elem[i].key);
    }
    return OK;
}

int SeqSearch(SSTable ST, KeyType key)
{
    for (int i = 0; i < ST.length; i++)
    {
        if (ST.elem[i].key == key)
        {
            return i;
        }
    }
    return -1;
}

int Bin_Search(SSTable ST, KeyType key)
{
    int low = 0, high = ST.length - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (ST.elem[mid].key == key)
        {
            return mid;
        }
        else if (ST.elem[mid].key < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

void BubbleSort(SSTable &ST)
{
    for (int i = 0; i < ST.length - 1; i++)
    {
        for (int j = ST.length - 1; j > i; j--)
        {
            if (ST.elem[j].key < ST.elem[j - 1].key)
            {
                KeyType temp = ST.elem[j].key;
                ST.elem[j].key = ST.elem[j - 1].key;
                ST.elem[j - 1].key = temp;
            }
        }
    }
}

void PrintSSTable(SSTable ST)
{
    for (int i = 0; i < ST.length; i++)
    {
        printf("%d ", ST.elem[i].key);
    }
    printf("\n");
}

int main()
{
    bool flag = false;
    bool sorted = false;
    int index;
    KeyType key;
    while (true)
    {
        int choice;
        printf("1.建立顺序查找表\n");
        printf("2.排序\n");
        printf("3.顺序查找\n");
        printf("4.二分查找\n");
        printf("0.退出\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            int n;
            printf("请输入表的长度:");
            scanf("%d", &n);
            SSTable ST;
            printf("请输入%d个元素:", n);
            CreateSSTable(ST, n);
            printf("建立成功！\n");
            printf("顺序查找表为：\n");
            PrintSSTable(ST);
            flag = true;
            break;
        case 2:
            if (!flag)
            {
                printf("请先建立顺序查找表！\n");
                break;
            }
            printf("排序前:");
            PrintSSTable(ST);
            printf("将进行冒泡排序\n");
            BubbleSort(ST);
            printf("排序完成！\n");
            printf("排序后:");
            PrintSSTable(ST);
            sorted = true;
            break;
        case 3:
            if (!flag)
            {
                printf("请先建立顺序查找表！\n");
                break;
            }
            printf("请输入要查找的关键字:");
            scanf("%d", &key);
            index = SeqSearch(ST, key);
            if (index == -1)
            {
                printf("未找到关键字！\n");
            }
            else
            {
                printf("在索引为%d的位置找到关键字%d!\n", index, key);
            }
            break;
        case 4:
            if (!flag)
            {
                printf("请先建立顺序查找表！\n");
                break;
            }
            if (!sorted)
            {
                printf("二分查找需要在排序过的表中进行!\n");
                break;
            }
            printf("请输入要查找的关键字:");
            scanf("%d", &key);
            index = Bin_Search(ST, key);
            if (index == -1)
            {
                printf("未找到关键字！\n");
            }
            else
            {
                printf("在索引为%d的位置找到关键字%d!\n", index, key);
            }
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("输入错误！\n");
            break;
        }
    }
    return 0;
}