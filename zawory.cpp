#include<cstdio>
using namespace std;
int n;
int u[300][300];
int d[300][300];
int ans[300];
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    while(1){
      int x;
      scanf("%d",&x);
      if(x<0)
        break;
      u[i][x-1]=1;
    }
    d[i][i]=1;
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      if(u[i][j]){
        for(int r=0;r<n;r++)
          if(r!=i)
            if(u[r][j]){
              for(int c=0;c<n;c++){
                u[r][c]^=u[i][c];
                d[r][c]^=d[i][c];
              }              
            }
        break;
      }
  }
  for(int r=0;r<n;r++)
    for(int c=0;c<n;c++)
      ans[c]^=d[r][c];
  for(int c=0;c<n;c++)
    if(ans[c])
      printf("%d ",c);
  printf("\n");
  return 0;
}
