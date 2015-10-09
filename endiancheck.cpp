#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
	union check
	{
		int x;
		char bytes[sizeof(int)];
	};
	union check c;
	c.x = 1;
	if(c.bytes[0] == 1)
	{
		printf("Little endian");
	}
	else
	{
		printf("Big endian");
	}
	return 0;
}
