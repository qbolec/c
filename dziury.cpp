#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
char t[406][406];
int w,h;
void go(int i,int j){
  if(i<0 || j<0 || i>=h || j>=w)return;
  if(t[i][j]){t[i][j]=2;return;}
  t[i][j]=2;
  go(i+1,j);
  go(i-1,j);
  go(i,j+1);
  go(i,j-1);
}
int x1[100],x2[100],y1[100],y2[100];
int xs[200],ys[200];
int nx[2002],ny[2002];
void solve(){
  int n;
  scanf("%d",&n);
  memset(t,0,sizeof(t));
  for(int i=0;i<n;i++){
    scanf("%d %d %d %d",x1+i,y1+i,x2+i,y2+i);
    xs[i*2]=x1[i];
    xs[i*2+1]=x2[i];
    ys[i*2]=y1[i];
    ys[i*2+1]=y2[i];
  }
  sort(xs,xs+2*n);
  int f=1;
  for(int i=0;i<2*n;i++)
    if(!i || xs[i]!=xs[i-1])
      nx[xs[i]+1000]=f++;
  w=f*2+1<?406;
  sort(ys,ys+2*n);
  f=1;
  for(int i=0;i<2*n;i++)
    if(!i || ys[i]!=ys[i-1])
      ny[ys[i]+1000]=f++;
  h=f*2+1<?406;

  for(int i=0;i<n;i++){
    x1[i]=nx[x1[i]+1000];
    x2[i]=nx[x2[i]+1000];
    y1[i]=ny[y1[i]+1000];
    y2[i]=ny[y2[i]+1000];
  }
  for(int i=0;i<n;i++){
    if(x1[i]==x2[i]){
      if(y1[i]>y2[i])swap(y1[i],y2[i]);
      for(int j=y1[i]*2;j<=y2[i]*2;j++)
        t[j][x1[i]*2]=1;
    }else{
      if(x1[i]>x2[i])swap(x1[i],x2[i]);
      for(int j=x1[i]*2;j<=x2[i]*2;j++)
        t[y1[i]*2][j]=1;
    }
  }
  go(0,0);
  int cnt=0;
  for(int i=0;i<h;i++)
  for(int j=0;j<w;j++)
  t[i][j]=(t[i][j]==2);
  
  for(int i=1;i<h;i+=2)
  for(int j=1;j<w;j+=2)
  if(!t[i][j]){
    cnt++;
    go(i,j);
  }
  printf("%d\n",cnt);
}
int main(){
  int d;
  scanf("%d",&d);
  while(d--)
    solve();
}
