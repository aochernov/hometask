#include <iostream>

using namespace std;
int getByte(int x, int n)
{
	int z = 255;
	n = n << 3;
	x = x >> n;
	x = x & z;
	return (x);
}

int main()
{
    return 0;
}
