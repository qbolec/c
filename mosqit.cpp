#include <iostream.h>

long solve(long x,long t)
{
 cin >> x >> t;
 x*=(x+1);
 x>>1;

 for(long int i=2;i<=t;i++)
 {
  x=sqrt(x);
  x*=(x+1);
  x>>1;
 }
 return x;
}

int main()
{

 return 0;
}
