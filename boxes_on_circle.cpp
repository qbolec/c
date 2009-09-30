#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
int b[1000000];
int c[2][1000000];
int h[1000000];
const int INF=0x7FFFFFFF;
int n;
int waga(int p,int t){
  return std::min(abs(t-p), std::min(abs(t-p-n),abs(t-p+n)));
}
int waga(int w,int p,int t){//O(1)
  int r=0;
  for(int i=0;i<w;++i){
    r+=waga(p,(t+i)%n);
  }
  return r;  
}

void solve(){
  scanf("%d",&n);
  for(int i=0;i<n;++i){
    scanf("%d",b+i);
    b[i+n]=b[i];
  }
  h[n]=0;
  for(int i=n;i--;){
    h[i]=h[i+1]+b[i];
  }
  int best=INF;
  for(int s=0;s<n;++s){
    int m=s;
    int now=0;
    for(int i=0;i<2;++i){
      memset(c[i],0,sizeof(int)*2*n);
    }
    for(int k=0;k<n;++k){
      if(b[k]){
        const int old=now;
        now=1-now;
        int g=INF;
        int last;
        for(int i=m;i+h[k]<=n+s;++i){
          if(i==m){
            last=waga(b[k],k,m);
          }else{
            last-=waga(k,i-1);
            last+=waga(k,i+b[k]-1);
          }
          g=std::min(g,c[old][i]+last);
          c[now][i+b[k]]=g;
        }
        m+=b[k];
      }
    }
    int minibest=INF;
    for(int i=m;i<=n+s;++i){
      minibest=std::min(minibest,c[now][i]);
    }
    best=std::min(best,minibest);
  }
  printf("%d\n",best);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
}
