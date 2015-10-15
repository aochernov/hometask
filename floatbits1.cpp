#include <iostream>
#include <stdio.h>

using namespace std;
union floatbits1
{
    int float_int;
    float float_float;
};
int main()
{
    float input;
    int i, myint, mantissa[23], exp[8];
    union floatbits1 convert;
    scanf("%f", &input);
    convert.float_float = input;
    myint = convert.float_int;
    if (myint < 0)
    {
        printf("Знак: 1\n");
        myint = myint & ~(1 << 31);
    }
    else
    {
        printf("Знак: 0\n");
    };
    for (i = 22; i >= 0; i--)
    {
        mantissa[i] = myint % 2;
        myint = myint / 2;
    };
    for (i = 7; i >= 0; i--)
    {
        exp[i] = myint % 2;
        myint = myint / 2;
    };
    printf("Экспонента: ");
    for (i = 0; i < 8; i++)
    {
        printf("%d", exp[i]);
    }
    printf("\nМантисса: ");
    for (i = 0; i < 23; i++)
    {
        printf("%d", mantissa[i]);
    }
    return 0;
}
