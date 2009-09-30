#include<cstdio>
#include<cmath>
#include<cstdlib>
double _T[100][100];
double T(int s,int ns,int v){
  if(s<0 || ns<0)return 0;
  if(ns<=0)return 0;//same gwiazdki pasuja do wszystkiego, a my ponoc do niczego!
//  if(s<=0 && ns<=1)return 0;
  double &x=_T[s][ns];
  if(x>0)return x;
  x= 1.0+(s*v*T(s-1,ns,v)+ns*T(s,ns-1,v))/(ns+s);
  return x;
}
double M(int s,int ns,int v){
  return pow(v,s+ns)-pow(v,s);
}
int main(){
  const int block=4;
  const int space=1<<block;
  const int entrylen=32;
  for(int i=entrylen/block;i<=entrylen/block;i++){
    for(int j=0;j<=i;j+=4/block){
      printf("%d stars and %d fixed = %lf  of %lf\n",j,i-j,T(j,i-j,space),M(j,i-j,space));
    }
  }
  system("PAUSE");
}
