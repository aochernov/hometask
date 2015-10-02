#include <iostream>

using namespace std;
int logicalShift(int x, int n)
{
	int z=1;
	x=x>>n;
	z=z<<31;
	z=~z;
	z=z>>n+(~0);
	z=z&x;
	return(z);
}
int main()
{
    return 0;
}
