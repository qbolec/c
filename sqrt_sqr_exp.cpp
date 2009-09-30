#include<cstdio>
#include<cmath>
const int N=5000;
double ab[N+1][N+1];
int main(){
  for(int a=0;a<=N;++a){
    for(int b=0;b<=N;++b){
      ab[a][b]=sqrt(a*a+b*b);
    }
  }

  for(int n=1;n<=N;++n){
    double result=0;
    for(int a=0;a<n;++a){
      for(int b=0;b<n;++b){
        int ile= (n-a)*(n-b)*(!!a+1)*(!!b+1);
        result+= ile*ab[a][b];
      }
    }
    printf("%.2lf\n",result/n/n/n/n);
  }
}
