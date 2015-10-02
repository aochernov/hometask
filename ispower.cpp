#include <iostream>

using namespace std;
int isPower2(int x)
{
    int c=1, z, y, d;
    d=!x;
    d=!d;
    c=c<<31;
    c=c&x;
    c=!c;
    y=x+(~0);
    z=x&y;
    z=!z;
    z=z&c;
    z=z&d;
    return(z);
}

int main()
{
    return 0;
}
