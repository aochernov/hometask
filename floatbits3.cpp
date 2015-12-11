#include <iostream>
#include <stdio.h>

using namespace std;

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
    float input;
    scanf("%f %f", &input, &input1);
    input = input/input1;
    int sign, exp = 0, mantissa = 0;
    int* input_pointer;
    input_pointer = (int*)&input;
    sign = *input_pointer;
    sign = sign >> 31;
    sign = sign & 1;
    exp = *input_pointer;
    exp = exp & ~(1 << 31);
    exp = exp >> 23;
    mantissa = *input_pointer;
    mantissa = mantissa & ~(511 << 31);
    printfloat(sign, mantissa, exp);
    return 0;
}
