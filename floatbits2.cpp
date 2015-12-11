#include <iostream>
#include <stdio.h>

using namespace std;
struct floatbits2
{
    unsigned int mant : 23;
    unsigned int exp : 8;
    unsigned int sign : 1;
};
union converter
{
    float struct_float;
    struct floatbits2 struct_struct;
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
    float input;
    struct floatbits2 convert;
    union converter myconverter;
    sscanf("%f %f", &input, &input1);
    input = input/input1;
    myconverter.struct_float = input;
    convert = myconverter.struct_struct;
    printfloat(convert.sign, convert.mant, convert.exp);
    return 0;
}
