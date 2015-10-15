#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    float input;
    scanf("%d", &input);
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
    printf("f = (-1)^%d * 1.%d * 2^(%d-127)", sign, mantissa, exp);
    return 0;
}
