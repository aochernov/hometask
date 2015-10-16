#include <iostream>
#include <stdio.h>
#define N 20

using namespace std;

int main()
{
	int i, n = 0, A[N];
	for (i = 0; i < N; i++)
	{
		scanf("%d", &A[i]);
	}
	for (i = 0; i < (N - 1) / 2; i++)
	{
		if (A[i] != A[N - 1 - i])
		{
			printf ("Не является симметричным массивом");
			break;
        }
        if (i == (N - 1) / 2 - 1)
        {
            printf ("Является симметричным массивом");
        }
	}
    return 0;
}
