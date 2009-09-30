#include <fstream.h>
//#include <iostream.h>
//#define qin cin
//#define qout cout
ifstream qin("sup.in");
ofstream qout("sup.out");
char t[101];
int n;
int rx[100];
int ry[100];
int b[201][201];
int maxx;
int minx;
int maxy;
int miny;
int headshots;
int queX[40404];
int queY[40404];
int queW;
int inque;
int color=0;
void datain()
{
  qin >> n;
  maxx=-101;
  maxy=-101;
  minx=101;
  miny=101;

  for(int i=0;i<n;i++)
  {
    qin >> rx[i] >> ry[i];
    if(rx[i]>maxx)maxx=rx[i];
    if(rx[i]<minx)minx=rx[i];
    if(ry[i]>maxy)maxy=ry[i];
    if(ry[i]<miny)miny=ry[i];
  }

}
inline void clear()
{
  headshots=0;
  b[minx+1][miny]=1000;
  b[minx-1][miny]=1000;
  b[minx][miny+1]=1000;
  b[minx][miny-1]=1000;
  queW=0;
}
inline void gocr8(int x,int y)
{
  if((b[x][y]==color)||(x<0) || (y<0) || (x>maxx) || (y>maxy))return;
  if(b[x][y]==1000)headshots++;
  b[x][y]=color;
  queX[queW]=x;
  queY[queW++]=y;
  int ox=2*minx-x;
  int oy=2*miny-y;
  if( (ox>0) && (oy>0) && (ox<maxx) && (oy<maxy))
  {
    int assshots=0;
    if(b[ox+1][oy]==color)assshots++;
    if(b[ox-1][oy]==color)assshots++;
    if(b[ox][oy+1]==color)assshots++;
    if(b[ox][oy-1]==color)assshots++;
    if(assshots>2)headshots=666;
  }
  inque++;
}
char testadvanced()
{
  minx=-minx;
  miny=-miny;
  maxx+=minx;
  maxy+=miny;
  clear();
  gocr8(minx,miny);
  int * x=queX;
  int * y=queY;
  inque=1;
  while((headshots<3) && (inque))
  {
    int *xx=rx;
    int *yy=ry;
    for(int i=0;i<n;i++)
      gocr8(*x+*xx++,*y+*yy++);
    x++;
    y++;
    inque--;
  }
  if(headshots>2)return 1;
  return 0;
}
char dzieli(int m,int x,int y,int rx,int ry)
{
  long int f=rx*x+ry*y;
  long int g= rx*y - ry*x;
  if(f<0)f=-f;
  if(g<0)g=-g;
  if((f%m) || (g%m))  return 0;
  return 1;
}
char rozklada(int x,int y)
{
  long int m=x*x+y*y;
  for(int i=0;i<n;i++)
    if(dzieli(m,x,y,rx[i],ry[i])==0)return 0;
  return 1;
}
char test2k()
{
  for(int ux=1;ux<101;ux++)
    for(int uy=1;uy<101;uy++)
      if(rozklada(ux,uy)==1)return 0;
  return 1;
}

char testtrivial()
{
  if((minx<0) &&  (miny<0) && (maxx>0) && (maxy>0))return 1;
  else return 0;
}
/*
char test()
{
 for(int i=0;i<n;i++)
    if( (rx[i]+ry[i])&1) return 1;
 return 0;
}
*/
char testnwdy()
{
  for(int i=0;i<101;i++)
    t[i]=0;
  for(int i=0;i<n;i++)
    if(ry[i]>0)t[ry[i]]=1;
    else t[-ry[i]]=1;

  if(t[1])return 1;

  for(char a=100;a>1;a--)
  {
    char b;
    if(t[a])
    {
      for( b=a-1;b>1;a--)
        if(t[b])break;
      if(t[b])
      {
        t[a%b]=1;
        if(t[1])return 1;
      }
    }
    a=b+1;
  }
  if(t[1])return 1;
  else return 0;
}
char testnwdx()
{
  for(int i=0;i<101;i++)
    t[i]=0;

  for(int i=0;i<n;i++)
    if(rx[i]>0)t[rx[i]]=1;
    else t[-rx[i]]=1;

  if(t[1])return 1;

  for(char a=100;a>1;a--)
  {
    char b;
    if(t[a])
    {
      for( b=a-1;b>1;a--)
        if(t[b])break;
      if(t[b])
      {
        t[a%b]=1;
        if(t[1])return 1;
      }
    }
    a=b+1;
  }
  if(t[1])return 1;
  else return 0;
}
char sims(int nx,int ny,int x,int y)
{
  if( (x * ny) !=  (y * nx) ) return 0;
  if( (x * nx) < 0 ) return 0;
  if( (x*x)+(y*y) > (nx*nx) + (ny*ny) ) return 0;
  return 1;
}
void optimizedata()
{
  int newn=0;
  int newrx[100];
  int newry[100];
  for(int i=0;i<n;i++)
  {
    int gupi=0;
    if(rx[i] || ry[i])
    {
      for(int j=0;j<newn;j++)
        if(sims(rx[i],ry[i],newrx[j],newry[j]))
        {
          gupi=1;
          break;
        }
      if(gupi)continue;
      for(int j=i+1;j<n;j++)
        if(sims(rx[i],ry[i],rx[j],ry[j]))
        {
          gupi=1;
          break;
        }
      if(gupi)continue;
      newrx[newn]=rx[i];
      newry[newn]=ry[i];
      newn++;
    }
  }
  n=newn;
  for(int i=0;i<n;i++)
  {
    rx[i]=newrx[i];
    ry[i]=newry[i];
  }
}
void solveone()
{
  color++;
  datain();
//  optimizedata();

  if(testtrivial()==0)
    cout<< "testtrivial";
  if(testnwdx()==0)
    cout<< "testnwdx";
  if(testnwdy()==0)
    cout<< "testnwdy";
  if(test2k()==0)
    cout<< "test2k";
  if(testadvanced())
    qout << "TAK";
  else
    qout << "NIE";

  qout << endl;
}

int main()
{
   int k;
   qin >> k;
   while(k--)
    solveone();
   return 0;
}
