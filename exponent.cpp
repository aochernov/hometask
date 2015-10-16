#include <iostream>
#include <stdio.h>

using namespace std;
int exp(int x, int n)
{
	int y;
	if (n > 2 && n % 2 == 0)
	{
		y = exp(x, n / 2) * exp(x, n / 2);
	}
	if (n > 2 && n % 2 == 1)
	{
		y = exp(x, n / 2) * exp(x, n / 2) * x;
	}
	if (n == 2)
	{
		y = x * x;
	}
	if (n == 1)
	{
		y = x;
	}
	return (y);
}

int main()
{
	int x, n, y;
	scanf ("%d", &x);
	scanf ("%d", &n);
	y = exp(x, n);
	printf ("%d", y);
    return 0;
}
