#include <iostream>

using namespace std;
int addOK(int x, int y)
{
	int a, x1, y1, b;
    a = x + y;
    x1 = x >> 31;
    y1 = y >> 31;
    b = a >> 31;
    x1 = x1 ^ b;
    y1 = y1 ^ b;
    a = x1 & y1;
    a = !a;
    return (a);
}
int main()
{
    return 0;
}
