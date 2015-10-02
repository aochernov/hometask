#include <iostream>

using namespace std;
int sign(int x)
{
	int a=1, b, z;
	a=a<<31;
	b=a&x;
	z=!x;
	z=!z;
	b=b>>31;
	z=z|b;
	return(z);
}
int main()
{
    return 0;
}
