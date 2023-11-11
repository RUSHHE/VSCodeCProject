#include <stdio.h>
typedef struct
{
    float realpart;
    float imagpart;
} complex;

void sub(complex z1, complex z2, complex &z)
{
    z.realpart = z1.realpart * z2.realpart - z1.imagpart * z2.imagpart;
    z.imagpart = z1.realpart * z2.imagpart + z1.imagpart * z2.realpart;
}

int main()
{
    complex a, b, z;
    a.realpart = 2;
    a.imagpart = 1;
    b.realpart = 0;
    b.imagpart = 2;
    sub(a, b, z);
    printf("%f, %f", z.realpart, z.imagpart);
    return 0;
}