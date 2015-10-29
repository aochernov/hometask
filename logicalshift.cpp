#include <iostream>

using namespace std;
int logicalShift(int x, int n)
{
	int z = 1;
	x = x >> n;
	z = z << 31;
	z = ~z;
	z = z >> n;
	z = z << 1;
	z = z + 1;
	z = z & x;
	return(z);
}
int main()
{
    return 0;
}
