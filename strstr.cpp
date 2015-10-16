#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{
	char S[100], S1[100];
	int i, n = 0, j, l, l1, q;
	gets(S);
	gets(S1);
	l = strlen(S);
	l1 = strlen(S1);
	for (i = 0; i < l - 1; i++)
	{
		if (S[i] == S1[0])
		{
			for (j = i + 1; j - i < l1; j++)
			{
				if (S[j] != S1[j - i])
				{
                    break;
				}
                if (j - i == l1 - 1)
                {
                    n++;
                }
            }
		}
	}
	printf ("%d", n);
    return 0;
}
