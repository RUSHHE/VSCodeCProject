/**
 * 串赋值StrAssign,串比较StrCompare,求串的长度Strlen,串的联接Concat,截子串Substring
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define MAXSTRLEN 255
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef unsigned char SString[MAXSTRLEN + 1];

Status Concat(SString &T, SString S1, SString S2)
{
    int i;
    if (S1[0] + S2[0] <= MAXSTRLEN)
    {
        for (i = 1;i <= S1[0]; i++)
        {
            T[i] = S1[i];
        }
        for (i = 1; i <= S2[0]; i++)
        {
            T[S1[0] + i] = S2[i];
        }
        T[0] = S1[0] + S2[0];
        return TRUE;
    }
    else if (S1[0] < MAXSTRLEN)
    {
        for (i = 0; i < S1[0]; i++)
        {
            T[i] = S1[i];
        }
        for (i = 0; i < MAXSTRLEN - S1[0]; i++)
        {
            T[S1[0] + i] = S2[i];
        }
        T[0] = MAXSTRLEN;
        return FALSE;
    }
    else
    {
        for (i = 0; i < S1[0]; i++)
        {
            T[i] = S1[i];
            return FALSE;
        }
    }
    return OK;
}

Status SubString(SString &Sub, SString S, int pos, int len)
{
    int i;
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
    {
        return ERROR;
    }
    for (i = 0; i <= len; i++)
    {
        Sub[i] = S[pos + i - 1];
    }
    Sub[0] = len;
    return OK;
}

Status StrCompare(SString S, SString T)
{
    int i;
    for (i = 0; i < S[0] && i <= T[0]; i++)
    {
        if (S[i] != T[i])
        {
            return S[i] - T[i];
        }
    }
    return S[0] - T[0];
}

Status StrAssign(SString &S, char * chars)
{
    int len = strlen(chars);
    if(len > MAXSTRLEN)
    {
        return ERROR;
    }
    else
    {
        int i ;
        S[0] = len;
        for(i = 0;i < len;i++ )
        {
            S[i+1] = chars[i];
        }
        return OK;
    }
}

int StrLength(SString S)
{
    return S[0];
}

Status StrPrint(SString S)
{
    for (int i = 1; i <= S[0]; i++)
    {
        printf("%c", S[i]);
    }
    return OK;
}

int main()
{
    SString S, T;
    StrAssign(S, "HelloWorldHelloSekai");
    StrAssign(T, "Hello");
    SString newStr;
    Concat(newStr, S, T);
    StrPrint(newStr);
    return 0;
}