#include<cstdio>
using namespace std;
short int d[26][26];
int c,n;
int w[26];
char b[2000];
int num[20]={1};
bool dfs(int v){
  if(w[v]==c)
    return false;
  w[v]=c;
  if(v==2)return true;
  for(int i=1;i<=n;i++)
    if(d[v][i] && d[v][i]%c==0)
      if(dfs(i))
        return true;
  return false;
}
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      scanf("%d",&d[i][j]);
  for(int p=2;p<2000;p++)
    if(!b[p]){
      for(int j=p*p;j<2000;j+=p)
        b[j]=true;    
      for(c=p;dfs(1);c*=p);    
      int x=c/p;
      int r=0;
      if(x>1){
        for(int j=0;j<20;j++){
          num[j]=num[j]*x+r;
          if(num[j]>1000000){
            r=num[j]/1000000;
            num[j]%=1000000;
          }else
             r=0;
        }
      }
    }
  
  int l=20;
  while(!num[l])l--;
  printf("%d",num[l]);
  while(l--)
    printf("%06d",num[l]);
  printf("\n");
  return 0;
}
