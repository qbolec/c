#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
double px[2000];
double py[2000];
int p[2000];
double pole(int i,int j,int k){
  if(i==j || j==k || i==k)return 0.0;
  double ux=px[i]-px[j];
  double vx=px[k]-px[j];
  double uy=py[i]-py[j];
  double vy=py[k]-py[j];  
  double result= abs(ux*vy-uy*vx);
  if(result==0.0){
    printf("%d %d %d ma pole zero\n",i,j,k);
  }
  return result;
}
bool poprawy(int f,int x,int t){
  int a=p[x]-f <? t-p[x];
  int b=p[x+1]-f <? t-p[x+1];
  return b>=a;
}
void solve(){
  int d,n,c,g;
  scanf("%d %d %d %d",&d,&n,&c,&g);
  p[0]=0;
  for(int i=1;i<c;i++){
    p[i]=p[i-1]+g;
    if(p[i]>=n)p[i]-=n;    
  }
  sort(p,p+c);
  for(int i=c;i--;){
    px[i]=sin( M_PI*2.0*p[i]/n )*d;
    py[i]=cos( M_PI*2.0*p[i]/n )*d;
  }
  double f=0;
  //A B C D
  int A=0;
  int B=1;
  int C=2;
  for(int D=3;D<c;D++){
    bool popraw;
    do{
      popraw=false;
      while(C+1<D && poprawy(p[B],C,p[D])){C++;popraw=true;}
      while(B+1<C && poprawy(p[A],B,p[C])){B++;popraw=true;}
      while(A+1<B && poprawy(p[D]-n,A,p[B])){A++;popraw=true;}
    }while(popraw);
    f>?= pole(A,B,C)+pole(A,D,C);
  }
  printf("%.6lf\n\n", f /8.0);
}
int main(){
  int t;
  scanf("%d",&t);
  for(int i=1;i<=t;i++){
    printf("Scenario #%d:\n",i);
    solve();
  }
}
