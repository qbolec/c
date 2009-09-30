/**\
jakub lopuszanski ]|[ LO
\**/
#include <fstream.h>
#include <math.h>
ifstream qin("pro.in");
ofstream qout("pro.out");
//#define qin cin
//#define qout cout
long k;//ilosc liter w alfabecie
long n;//ilosc intervalow
long m;//dlugosc slowa
long l;//errlength
int BIN[10000];
int binadd[1024];
int binsub[1024];
struct bignum
{
   long kdo[120];
};
bignum sigma2;
bignum goodness2[102];
void add(long src,long des)
{
   for(int i=0;i<110;i++)
      goodness2[des].kdo[i]+=goodness2[src].kdo[i];
}
void funky(long src)
{
  for(int i=110;i>=0;i--)
    goodness2[src].kdo[i+1]=goodness2[src].kdo[i]-goodness2[src].kdo[i+1];
  goodness2[src].kdo[0]*=-1;
}
void shiftup(long src)
{
  for(int i=110;i>=0;i--)
     goodness2[src].kdo[i+1]=goodness2[src].kdo[i];
  goodness2[src].kdo[0]=0;
}
void b_add(int * src,int * dst)
{
   long mem=0;
   for(int i=0;i<1024;i++)
   {
     dst[i]+=src[i]+mem;
     if(dst[i]>1)
     {
       dst[i]-=2;
       mem=1;
     }
     else
       mem=0;
   }
}
void b_mult(int * src, long f, int * dst)
{
   int temp[1024];
   for(int i=0;i<1024;i++)
   {
     temp[i]=src[i];
     dst[i]=0;
   }
   while(f--)b_add(temp,dst);
}
void b_sub(int * src,int * dst)
{
  long mem=0;
  for(int i=0;i<1024;i++)
   {
     dst[i]-=src[i]+mem;
     if(dst[i]<0)
     {
       dst[i]+=2;
       mem=1;
     }
     else
       mem=0;
   }
}
void converttobin()
{
  int temp[1024];
  binadd[0]=1;
  for(int i=0;i<110;i++)
  {
    if(goodness2[0].kdo[i]>0)
    {
      b_mult(binadd, goodness2[0].kdo[i] , temp);
      b_add(temp,BIN);
      goodness2[0].kdo[i]=0;
    }
    b_mult( binadd, k ,binadd);
  }
  binsub[0]=1;
  for(int i=0;i<110;i++)
  {
    if(goodness2[0].kdo[i]<0)
     {
       b_mult(binsub, -goodness2[0].kdo[i] , temp);
       b_sub(temp,BIN);
       goodness2[0].kdo[i]=0;
     }
    b_mult( binsub, k , binsub);
  }
}
long dictsize2()
{
  goodness2[1].kdo[0]=1;
  goodness2[2].kdo[1]=1;
  goodness2[2].kdo[0]=-1;
  for(int i=3;i<=m;i++)
  {
     //wyliczmy wartosc goodness2[i]:
     //1.sumujemy wczesniejsze
     for(int e=1;e<l;e++)
        if(i-e>0)
        {
           add( i-e, i );//(skad,dokad)
        }
     //2.wymnarzamy przez k-1
     funky( i);
  }
  //ostatecznym wynikiem jest suma razy k;
  for(int e=1;e<l;e++)
     add(m-e+1,0);
  shiftup(0);
  converttobin();
}
void bigadd(int * src,int * dst)
{
   long mem=0;
   for(int i=0;i<10000;i++)
   {
     dst[i]+=src[i]+mem;
     if(dst[i]>1)
     {
       dst[i]-=2;
       mem=1;
     }
     else
       mem=0;
   }
}
int iszero(int * a)
{
  for(int i=0;i<1024;i++)
     if(a[i])return 0;

  return 1;
}
void dropdown(int * a)
{
  for(int i=0;i<1023;i++)
    a[i]=a[i+1];
  a[1023]=0;
}
void bigmult( int * a,int * b,int * r)
{
   if(b[0]==1)
   {
      b[0]=0;
      bigmult( a,b,r);
      bigadd(  a,r);

   }
   else
   {
     if(iszero(b))
     {
        for(int i=0;i<10000;i++)
           r[i]=0;
     }
     else
     {
       dropdown(b);
       bigmult(a,b,r);
       bigadd(r,r);
     }
   }
}
long powerandlog(long pow)
{
  int bigbin[10000];
  int bigtemp[10000];
  int tempBIN[10000];
  for(int i=0;i<10000;i++)
     bigbin[i]=0;
  bigbin[0]=1;
  for(int p=0;p<pow;p++)
  {
     for(int i=0;i<10000;i++)tempBIN[i]=BIN[i];
     bigmult( bigbin,tempBIN,bigtemp);
     for(int i=0;i<10000;i++)
        bigbin[i]=bigtemp[i];
  }
  for(int i=9999;i>=0;i--)
     if(bigbin[i])
       return i;

}
void solvenew()
{
  long f= n/m;
  dictsize2();
  long w= powerandlog(f);

  qout << w<< endl;
}
int main()
{
  qin>>k>>n>>m>>l;
  solvenew();
  return 0;
}

