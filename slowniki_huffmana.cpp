#include<cstdio>
using namespace std;
long long T[20][20],p[20][20];
int n;

int main(){
  scanf("%d",&n);
  for(int i=0;i<=n;i++){
    p[i][0]=p[i][i]=1;
    for(int j=1;j<i;j++)
      p[i][j]=p[i-1][j]+p[i-1][j-1];
  }
  for(int j=0;j<=n;j++)
    T[0][j]=!(j&(j-1));
  T[1][0]=1;
  for(int i=1;i<=n;i++){
    for(int j=0;j<=n;j++){
      if(i!=1 || j!=0){
        int r=j&1;
        for(int k=0;2*k+r<=i;k++)
          T[i][j]+= p[i][2*k+r]* T[i- 2*k-r ][k+ (j+1)/2 ];      
      }
    }
  }
  printf("%lld\n",T[n][0]);
}
