#include <iostream>

using namespace std;
int thirdBits(void)
{
	int x=36, y, z;
	y=x<<6;
	z=y|x;
	y=z<<12;
	y=y|z;
	z=y<<6;
	z=z|x;
	return(z);
}
int main()
{
    int x;
    x=thirdBits();
    printf("%d", x);
    return 0;
}
