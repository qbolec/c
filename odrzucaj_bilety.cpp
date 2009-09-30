#include<cstdio>
#include<cstring>
int a[22];
int b[22];
int c[22];
int f[22];
int v[16];
void solve(){
  int n,m,k;
  scanf("%d %d %d",&n,&m,&k);
  for(int i=0;i<k;i++){
    scanf("%d %d %d",a+i,b+i,c+i);
    f[i]=c[i]*(b[i]-a[i]);
  }
  int best=0;
  for(int i=1;i<(1<<k);i++){
    memset(v,0,sizeof(v));
    int g=0;
    for(int j=0;j<k;j++)
      if(i&(1<<j)){
        v[a[j]]+=c[j];
        v[b[j]]-=c[j];
        g+=f[j];
      }
    int w=0;
    for(int j=0;j<=m+1;j++){
      w+=v[j];
      if(w>n)
        break;
    }
    if(w<=n)
      best>?=g;
  }
  printf("%d\n",best);
}
int main(){
  int d;
  scanf("%d",&d);
  while(d--)solve();
}
