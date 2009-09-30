#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX_N=100000;
const int INF=1000000000;
struct kopiec{
  int tab[MAX_N];
  int where[MAX_N];
  int who[MAX_N];
  int size;
  void Swap(int idx1,int idx2){
      swap(tab[idx1],tab[idx2]);
      swap(who[idx1],who[idx2]);
      where[who[idx1]]=idx1;
      where[who[idx2]]=idx2;  
  }
  void delete_min(){
    size--;
    Swap(0,size);
    where[who[size]]=-1;
    who[size]=-1;    
    if(size){
      //printf("deleting size=%d\n",size);
      down(0);
    }
  }
  void decrement(int id,int to){
    int idx=where[id];
    if(idx<0)return;
    if(tab[idx]>to){
      tab[idx]=to;
      up(idx);
    }
  }
  void down(int idx){
    while(1){
      int c=idx*2;
      if(c<size){
        int c2=c+1;
        if(c2<size){
          if(tab[c2]<tab[c])c=c2;
        }
        if(tab[c]<tab[idx]){
          Swap(c,idx);
          idx=c;
        }else
          return;
      }else
        return;
    }
  }
  void up(int idx){
    while(idx>0){
      int f=idx/2;
      if(tab[f]>tab[idx]){
        Swap(idx,f);
        idx=f;        
      }else 
        return;
    }
  }
  kopiec(int n){
    size=n;
    for(int i=n;i--;){
      who[i]=i;
      where[i]=i;
      tab[i]=INF;      
    }
  }
};
const int MAX_K=100;
int p[MAX_K];
int pm[MAX_K];
int cache[32][MAX_N];
void solve(){  
  int k,q;
  scanf("%d %d",&k,&q);
  //printf("k=%d q=%d\n",k,q);
  for(int i=0;i<k;i++){
    scanf("%d",p+i);
    pm[i]=p[i]%p[0];
  }

  kopiec cop(p[0]);
  cop.decrement(0,0);
  for(int j=0;(1<<j) <= p[0]*2;j++)
    for(int i=0;i<p[0];i++)
      cache[j][i]=INF;
  
  while(cop.size){
    int dist=cop.tab[0];
    int who=cop.who[0];
    cache[0][who]=dist-dist%p[0];
    cop.delete_min();
    if(dist!=INF){
      for(int i=0;i<k;i++){
        int z=(who+pm[i])%p[0];
        cop.decrement(z, dist+p[i] );
      }
    }
  }
  for(int j=1,g2=1;g2 <= p[0];j++,g2*=2)
    for(int i=0;i<p[0];i++)
      cache[j][i]= cache[j-1][i]<?cache[j-1][i+g2];
  
  while(q--){
    int x;
    scanf("%d",&x);
    
    int xm=x%p[0];
    if(x>= cache[0][xm]){
      printf("%d\n",x);
    }else{
      int a=xm;
      int k=0;
      int b=a+1;
      while(b<=p[0] && x<cache[k][a] ){
        k++;
        b=xm+ (1<<k);
      }
      if(x<cache[k][a])
        printf("%d\n",x+p[0]-xm);
      else{
        while(k){
          int c=(a+b)/2;
          k--;
          if(cache[k][a]<=x){
            b=c;
          }else{
            a=c;
          }
        }
        printf("%d\n",x+a-xm);
      }
    }
  }
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
}
