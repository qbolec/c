#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
long double x[1024][1024];
long double y[1024][1024];
int main(){
  const int M=1000;
  x[0][0]=1;
  for(int h=0;h<M;h++)
    y[0][h]=1;
  for(int n=1;n<M;n++){
    double ex=0;
    for(int h=1;h<=n;h++){
      for(int l=0;l<n;l++){
        x[n][h]+=x[l][h-1]*y[n-l-1][h-1]*2;
        x[n][h]-=x[l][h-1]*x[n-l-1][h-1];
      }
      ex+=h*x[n][h];
      y[n][h]=y[n][h-1]+x[n][h];
    }
    for(int h=n+1;h<M;h++)
      y[n][h]=y[n][h-1];
    ex/=y[n][n];
    printf("%d : %llf %llf\n",n,ex,ex/log(n));
  }
  system("pause");
}
