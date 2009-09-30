#include<cstdio>
#include<cmath>
using namespace std;
double a[10][10];
int main(){
  a[0][0]=a[0][1]=1;
  for(int k=1;k<5;k++){
    for(int j=0;j<=k+1;j++){
      a[k][j] = a[k-1][j];
      if(j>0)
        a[k][j]+= a[k-1][j-1];
      for(int i=j-1 >? 0;i<=k-1;i++)
        a[k][j]-= a[k-1][i]*a[i][j];
      a[k][j]/=(1+a[k-1][k]);
      printf("%.3lf ",a[k][j]);

    }
    puts("");
  }
  for(int k=0;k<5;k++){
    double s=0;
    for(int i=0;i<10;i++){
      s+= pow((double)i,k);
      double f=0;
      int x=1;
      for(int j=0;j<=k+1;j++){
        f+= x*a[k][j];
        x*=i;
      }
      printf("%lf\n",s-f);
    }
  }
  scanf("%d");
}
