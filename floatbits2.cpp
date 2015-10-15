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
int main()
{
    float input;
    struct floatbits2 convert;
    union converter myconverter;
    scanf("%f", &input);
    myconverter.struct_float = input;
    convert = myconverter.struct_struct;
    printf("f = (-1)^%d * 1.%d * 2^(%d-127)", convert.sign, convert.mant, convert.exp);
    return 0;
}
