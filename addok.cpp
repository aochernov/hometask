#include <iostream>

using namespace std;
int addOK(int x, int y)
{
	int a=255, b, x1, y1, x2, y2, z, q;
	b=a<<8;
	b=a|b;
	x1=b&x;
	y1=b&y;
	z=x1+y1;
	z=z>>16;
	x2=x>>16;
	y2=y>>16;
	x2=x2&b;
	y2=y2&b;
	q=x2+y2;
	q=z+q;
	q=q>>16;
	q=!q;
	return(q);
}
int main()
{
    return 0;
}
