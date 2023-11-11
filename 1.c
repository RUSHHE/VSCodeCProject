#include <stdio.h>
int main()
{
    int a = 0;
    int b = 00;
    char c = (char)a;
    char d = (char)b;
    printf("这是c%c\n", c);
    printf("这是d%c\n", d);
    printf("%d", a ==  b);
    return 0;
}