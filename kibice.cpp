#include <fstream.h>
//#define qin cin
//#define qout cout
ifstream qin("wys.in");
ofstream qout("wys.out");
int main()
{
  int n;
  int max=0;
  long *t;
  qin>>n;
  t=new long [2*n];
  long total=0;
  for(int i=0;i<n;i++)
  {
    qin >> t[i];
    total+=t[i+n]=t[i];
  };
  total>>=1;
  int a=0;
  int b=0;
  int s=t[0];
  while(a<n)
  {
    while(s<=total)
    {
      b++;
      s+=t[b];
    }
    s-=t[b];
    b--;
    if(s>max)max=s;
    s-=t[a];
    a++;
  }
  qout << max;
  return 0;
}
