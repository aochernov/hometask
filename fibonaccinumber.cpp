#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	int F1 = 1, F2 = 2, F3 = 3, n, i;
	scanf ("%d", &n);
	if (n > 3)
	{
		for (i = 4; i <= n; i++)
		{
			F1 = F2;
			F2 = F3;
			F3 = F1 + F2;
		}
		printf ("%d", F3);
	}
	else
	{
		printf ("%d", n);
	}
    return 0;
}
