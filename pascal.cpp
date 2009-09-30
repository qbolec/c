#include <iostream.h>

long nk(long n,long k)
{
  if( k>n )return 0;
  if( n==0)return 1;
  if( k==0)return 1;
  return nk( n-1,k) + nk(n-1,k-1);
}

int main()
{
  long n;
  long k;
  while(1)
  {
    cin >> n >> k;
    cout << nk(n,k);
  }
  return 0;
}
