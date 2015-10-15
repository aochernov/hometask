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
    int i, myint, mant, exp, sign;
    union floatbits1 convert;
    scanf("%f", &input);
    convert.float_float = input;
    myint = convert.float_int;
    mant = myint & ~(511 << 31);
    exp = myint >> 23;
    exp = exp & 255;
    sign = myint >> 31;
    sign = sign & 1;
    printf("f = (-1)^%d * 1.%d * 2^(%d-127)", sign, mant, exp);
    return 0;
}
