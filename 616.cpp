
#include <iostream.h>

long t1[10000];
long t2[10000];
long f1=0;
long f2=0;



long test(long x, long p)
{
 for(long i=p ; i ; i--)
 {
  if( x % p == 1)
  {
   x= (x-1) - ((x-1)/p);
  }
  else
  {
   return 0;
  }
 }
 if( x % p == 0 ) return 1;
 else return 0;
}
long solve(long x)
{
 f1=f2=0;
 //if(x<3)return -1;
 for(long p=1;p*p<=x-1;p++)
 {
  if( x % p == 1 )
  {
   t1[f1++]= p ;
   if( p*p!=x-1)
   {
    t2[f2++]= (x-1)/p ;
   }
  }
 }
 for(int id=0;id<f2;id++)
 {
  if(test (x, t2[id] ) == 1 )return t2[id];
 }
 for( int id=f1-1;id>=0;id--)
 {
  if(test (x, t1[id] ) == 1 )return t1[id];
 }
 return -1;
}

int main()
{
 long x;
 while(1)
 {
  cin >>x;
  if(x<0)return 0;
  long temp=solve(x);
  if(temp == -1)
  {
   cout << x << " coconuts, no solution" << endl;
  }
  else
  {
   cout << x << " coconuts, " << temp <<" people and 1 monkey" << endl;
  }
 }

}
