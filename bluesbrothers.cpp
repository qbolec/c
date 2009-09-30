#include<cstdio>
using namespace std;
int n,m;
double x[128][128];
int main(){
  while(1){
    scanf("%d",&n);
    if(!n)
      return 0;
    scanf("%d",&m);
    for(int a=1;a<=n;a++)
      for(int b=1;b<=n;b++)
        x[a][b]=0;
     
    for(int i=0;i<m;i++){
      int a,b,p;
      scanf("%d %d %d",&a,&b,&p);
      x[a][b]=0.01*p;
      x[b][a]=0.01*p;
    }
    for(int k=1;k<=n;k++){
      for(int a=1;a<=n;a++){
        for(int b=1;b<=n;b++){
          x[a][b]>?=x[a][k]*x[k][b];
        }
      }
    }
    
    printf("%.6lf percent\n",x[1][n]*100.0);
  }
}
