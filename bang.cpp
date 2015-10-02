#include <iostream>

using namespace std;
int bang(int x)
{
    int y, z;
    y=~x;
    z=y+1;
    z=~z;
    y=y&z;
    y=y>>31;
    y=y&1;
    return(y);
}
int main()
{
    return 0;
}
