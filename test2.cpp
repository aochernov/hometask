#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX_LENGTH 20

using namespace std;

int removesymbol (void)
{
    char symbol, input = ' ';
    printf("Please enter the symbol:\n");
    scanf("%c", &symbol);
    printf("Please enter the string:");
    while (input != '\0')
    {
        scanf("%c", &input);
        if (input != symbol && tolower(input) != symbol && toupper() != symbol)
        {
            printf("%c", input);
        }
    }
    return 0;
}

int compare (void)
{
    char char1[MAX_LENGTH] = "1010", char2[MAX_LENGTH] = "1010";
    int int1 = 0, int2 = 0, i, tmp;
    for (i = 0; i < MAX_LENGTH; i++)
    {
        if (char1[i] == '0')
        {
            tmp = 0;
        }
        if (char1[i] == '1')
        {
            tmp = 1;
        }
        int1 = int1 + tmp * pow(2, i);
        if (char2[i] == '0')
        {
            tmp = 0;
        }
        if (char2[i] == '1')
        {
            tmp = 1;
        }
        int2 = int2 + tmp * pow(2, i);
    }
    if(int1 > int2)
    {
        printf("Первое число больше");
    }
    if(int1 < int2)
    {
        printf("Второе число больше");
    }
    if(int1 == int2)
    {
        printf("Числа равны");
    }
    return 0;
}

int printcomments(void)
{
    FILE *fo;
    int i, flag = 0;
    char input[MAX_LENGTH], symbol;
    fo = fopen("file.txt", "r");
    if(fo == NULL)
    {
        printf("Error");
        return 0;
    }
    else
    {
        while(feof(fo))
        {
            fgets(*input, MAX_LENGTH, fo);
            while(symbol != '\0')
            {
                if (input[i] == '/' && input[i + 1] == '/')
                {
                    flag = 1;
                }
                if (flag == 1)
                {
                    printf("%c", input[i]);
                }
                i++;
            }
        flag = 0;
        printf("\n");
        }
        fclose(fo);
        return 0;
    }
}

int main()
{
    return 0;
}
