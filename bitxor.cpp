#include <iostream>

using namespace std;
int bitXor(int x, int y)
{
	int z, a, b, t;
	a = ~x;
	b = ~y;
	z = x & y;
	t = a & b;
	z = ~z;
	t = ~t;
	z = z & t;
	return (z);
}
int main()
{
    return 0;
}
