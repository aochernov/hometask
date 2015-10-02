#include <iostream>

using namespace std;
int fitsBits(int x, int y)
{
    int p=1, z, q, n;
    p=~p;
    p=p<<(y+(~0)+(~0));
    z=x&p;
    z=z>>(y+(~0));
    q=~z;
    q=!q;
    z=!z;
    n=q|z;
    return (n);
}
int main()
{
    return 0;
}
