#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int Status;
typedef char SElemType[50];

typedef struct
{
    char provincer[20];
    char assistance[50];
} Friends;

Friends group[100];
int indx = 0;

typedef struct SNode
{
    SElemType data;
    struct SNode * next;
}SNode, * LinkStack;

Status InitStack(LinkStack &L)
{
    L = (LinkStack)malloc(sizeof(SNode));
    if (!L)
    {
        return ERROR;
    }
    L->next = NULL;
    return OK;
}

Status Push(LinkStack &S, SElemType e)
{
    LinkStack p = (LinkStack)malloc(sizeof(SNode));
    if (!p)
    {
        return ERROR;
    }
    strcpy(p->data, e);
    p->next = S;
    S = p;
    return OK;
}

Status Pop(LinkStack &S, SElemType &e)
{
    if (S == NULL)
    {
        printf("The Stack is NULL!\n");
        return ERROR;
    }
    LinkStack p = S;
    strcpy(e, p->data);
    S = p->next;
    free(p);
    return OK;
}

Status GetTop(LinkStack S, SElemType &e)
{
    if (S == NULL)
    {
        return ERROR;
    }
    strcpy(e, S->data);
    return OK;
}

Status EmptyStack(LinkStack S)
{
    if (S == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Status ReadFile()
{
    FILE * fp;
    fp = fopen("/Users/rushhe/VSCodeCProject/DataStructures/Experiment/3/2_2_5_inputdata.txt", "r"); // 对接省市的绝对路径
    int i = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s %s", group[i].provincer, group[i].assistance);
        i++;
        if (getc(fp) == EOF)
        {
            break;
        }  
    }
    indx = i;
    fclose(fp); 
    return OK; 
}

Status SearchInGroup(SElemType e, char a[])
{
    for (int i = 0; i <= indx; i++)
    {
        if (strcmp(group[i].assistance, e) == 0)
        {
            strcpy(a, group[i].provincer);
            break;
        }
    }
    return OK;
}

Status Handle_str1(char s[])
{
    char t1[20], t2[20], z[20], str[20];
    SElemType e1, e2, e;
    int i = 0, j = 0, t = 1;
    LinkStack top = NULL;
    for (i = 0; s[i] != '#'; i++)
    {
        if (s[i] != ' ')
        {
            t1[j] = s[i];
            j += 1;
        }
        else if (s[i] == ' ')
        {
            t1[j] = '\0';
            strcpy(e1, t1);
            Push(top, e1);
            j = 0;
        }
    }
    if (s[i] == '#')
    {
        if (i != 0)
        {
            t1[j] = '\0';
            strcpy(e1, t1);
            Push(top, e1);
            j = 0;
        }
    }
    for (i++; i <= strlen(s); i++)
    {
        if (s[i] != ' ' && s[i] != '\0')
        {
            t2[j] = s[i];
            j += 1;
        }
        else
        {
            if (j != 0)
            {
                t2[j] = '\0';
                strcpy(e2, t2);
                if (EmptyStack(top))
                {
                    printf("对接不成功\n");
                    printf("%s缺少对口省市\n", e2);
                    t = 0;
                    break;
                }
                GetTop(top, e);
                SearchInGroup(e2, str);
                if (strcmp(str, e) != 0)
                {
                    printf("对接不成功\n");
                    printf("%s不是%s的对口地区,%s的对接省市应为%s\n", e2, e, e2, str);
                    t = 0;
                }
                Pop(top, e);
                j = 0;
            }
            else
            {
                GetTop(top, e);
                printf("对接不成功\n");
                printf("%s缺少对口援助地区\n", e);
                Pop(top, e);
                t = 0;
            }   
        }
    }
    if (EmptyStack(top) && t)
    {
        printf("全部对接成功\n");
    }
    else if (!EmptyStack(top))
    {
        GetTop(top, e);
        printf("对接不成功\n");
        printf("%s缺少对口援助地区\n", e);
    }  
    return OK;
}

int main()
{
    ReadFile();
    char a[100];
    gets(a);
    Handle_str1(a);
    return 0;
}