//#include <fstream.h>
#include <iostream.h>
#define qin cin
#define qout cout
//ifstream qin("sup.in");
//ofstream qout("sup.out");
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
int queR;
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
  queR=0;
  queW=0;
}
inline void gocr8(int x,int y)
{
  if(b[x][y]==color)return;
  if(x<0 || y<0)return;
  if(x>maxx || y>maxy)return;
  if(b[x][y]==1000)headshots++;
  b[x][y]=color;
  queX[queW]=x;
  queY[queW++]=y;
}
char testadvanced()
{
  minx=-minx;
  miny=-miny;
  maxx+=minx;
  maxy+=miny;
  clear();
  gocr8(minx,miny);
  while(headshots<3)
  {
    if(queR==queW)
      return 0;

    int x=queX[queR];
    int y=queY[queR];
    int *xx=rx;
    int *yy=ry;
    for(int i=0;i<n;i++)
      gocr8(x+*xx++,y+*yy++);

    queR++;
  }
  return 1;
}
char test()
{
 for(int i=0;i<n;i++)
    if( (rx[i]+ry[i])&1) return 1;
 return 0;
}
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

char testtrivial()
{
  if((minx<0) &&  (miny<0) && (maxx>0) && (maxy>0))return 1;
  else return 0;
}
void solveone()
{
  color++;
  datain();

  if(testtrivial() && test() && testnwdx() && testnwdy())
    testadvanced();
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
