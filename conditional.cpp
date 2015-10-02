#include <iostream>

using namespace std;
int conditional(int x, int y, int z)
{
    int p, q, n;
    p=!x;
    p=p<<31;
    p=p>>31;
    q=~p;
    p=p&z;
    q=q&y;
    n=q|p;
    return(n);
}
int main()
{
    return 0;
}
