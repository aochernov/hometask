#include <iostream>
#include <stdio.h>
#define N 20

using namespace std;

int main()
{
	int i, c = 0, A[N];
	for (i = 0; i < N; i++)
	{
		scanf ("%d", &A[i]);
	}
	for (i = 0; i < N; i++)
	{
		if (A[i] == 0)
		{
			c = c + 1;
		}
	}
	printf ("%d", c);
    return 0;
}
