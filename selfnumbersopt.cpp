#include <iostream.h>
int spawningpool[64];

inline long g(long t)
{
  long out=t;
  while(t)
  {
    out+= t % 10;
    t/=10;
  }
  return out;
}

int main()
{
  spawningpool[1]=1;

  cout<<1<<endl;
  for(long t=1;t<1000001;t++)
  {
    spawningpool[g(t) & 63]=1;

    if(spawningpool[t & 63])
      spawningpool[t & 63]=0;
    else
      cout << t << endl;

  }
  return 0;
}


