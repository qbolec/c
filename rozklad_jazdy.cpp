#include<cstdio>
#include<algorithm>
using namespace std;
int r[10000];
void solve(){
  int n,m,x,y,t=0;
  scanf("%d %d",&n,&m);
  r[0]=0;
  for(int i=1;i<n;i++){
    scanf("%d %d",&x,&y);    
    t+=y;
    t%=m;    
    r[i]=m-t;
  }
  sort(r,r+n);
  int best=r[n-1];
  for(int i=1;i<n;i++)
    best<?=m-r[i]+r[i-1];
  printf("%d\n",best);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
  return 0;
}
