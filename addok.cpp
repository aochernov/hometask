#include <iostream>

using namespace std;
int addOK(int x, int y)
{
	int a = 1, n = 1, x1, y1, x2, y2, z, q, c;
	c = a << 31;
	c = ~c;
	x1 = c & x;
	y1 = c & y;
	z = x1 + y1;
	z = z >> 31;
	z = z & n;
	x2 = x >> 31;
	y2 = y >> 31;
	x2 = x2 & n;
	y2 = y2 & n;
	q = x2 | y2;
	q = z & q;
	return(q);
}
int main()
{
    return 0;
}
