#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

using namespace std;

int main()
{
	int i, j, k, n = 0;
	char A[100];
	gets(A);
	k = strlen(A);
	for (i = 0; i < k; i++)
	{
		A[i] = tolower(A[i]);
		if (A[i] == ' ')
		{
			for (j = i + 1; j <= k; j++)
			{
				A[j-1] = A[j];
			}
            k = strlen(A);
            i--;
		}
	}
	for (i = 0; i < k / 2; i++)
	{
		if (A[i] != A[k - 1 - i])
		{
			printf ("Не является палиндромом");
			break;
		}
		if (i == (k / 2) - 1)
		{
            printf ("Является палиндромом");
		}
	}
    return 0;
}
