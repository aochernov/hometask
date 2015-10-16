#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main()
{
	int i, n, q, j;
	scanf ("%d", &n);
	if (n > 1)
    {
        printf("2\n");
    }
	for (i = 1; i <= n; i++)
	{
		q = 0;
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				break;
			}
            if (j == i - 1)
            {
                printf ("%d\n", i);
            }
		}
	}
    return 0;
}
