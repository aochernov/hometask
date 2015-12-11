#include <iostream>
#include <stdio.h>

using namespace std;
union floatbits1
{
    int float_int;
    float float_float;
};

int printfloat (int sign, int mant, int exp)
{
    if (exp == 255 && mant != 0)
    {
        printf("NaN");
    }
    if (exp == 255 && mant == 0 && sign == 1)
    {
        printf("-inf");
    }
    if (exp == 255 && mant == 0 && sign == 0)
    {
        printf("+inf");
    }
    else
    {
        printf("f = (-1)^%d * 1.%d * 2^(%d-127)", sign, mant, exp);
    }
}

int main()
{
    float input, input1;
    int i, myint, mant, exp, sign;
    union floatbits1 convert;
    scanf("%f %f", &input, &input1);
    input = input/input1;
    convert.float_float = input;
    myint = convert.float_int;
    mant = myint & ~(511 << 31);
    exp = myint >> 23;
    exp = exp & 255;
    sign = myint >> 31;
    sign = sign & 1;
    printfloat(sign, mant, exp);
    return 0;
}
