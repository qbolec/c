#include<cstdio>
using namespace std;
int sum[10][80],n;
int main(){
  scanf("%d",&n);
  n/=2;
  sum[0][0]=1;
  for(int i=0;i<n;i++){
    for(int j=0;j<10;j++){
      for(int s=0;s<51;s++){
        sum[i+1][s+j]+=sum[i][s];
      }
    }
  }
  int res=0;
  for(int s=0;s<51;s++){
    res+=sum[n][s]*sum[n][s];
  }
  printf("%d\n",res);
}
