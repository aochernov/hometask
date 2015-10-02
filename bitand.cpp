#include <iostream>

using namespace std;
int bitAnd(int x, int y)
{
	int z;
	x=~x;
	y=~y;
	z=x|y;
	z=~z;
	return(z);
}
int main()
{
    return 0;
}
