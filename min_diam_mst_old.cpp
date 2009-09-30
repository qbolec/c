#include<cstdio>
#define CLEAR(c) {long long * Z=(long long*) c; Z[0]=Z[1]=Z[2]=Z[3]=0; }
using namespace std;
char f[32][32];
char fc[32];
char d[32][32];
char p[32][32];
char R[32],c[32],l1[32],l2[32];
char * r;
int n,m,q;
void go(){
  int w=0;
  for(int i=n;i--;)
    if(!c[i]&&!l1[i]){
      int v=i;
      while(1){
        const int rv=r[v];
        if(rv==v){
          if(v<n)
            w>?=l1[v]+l2[v];          
          else
            w>?=l1[v]+l2[v]-1;          
          q<?=w;      
          return ;
        }
        w>?=l1[v]+l2[v]; 
        if(w>=q){
          CLEAR(c);
          return;
        }
        int l=l1[v]+1;
        if(  l > l1[ rv ]){
          l2[ rv ]=l1[ rv ];
          l1[ rv ]=l;
        }else
          l2[ rv ]>?=l;
        v=rv;                
        if(--c[ rv ])
          break;        
      }               
    }
}
void solve(){
  scanf("%d %d",&n,&m);
  CLEAR(fc);
  for(int i=n;i--;)
    for(int j=n;j--;)
      d[i][j]=n;    
  
  for(int i=m;i--;){    
    int x,y;
    scanf("%d %d",&x,&y);
    f[x][fc[x]++]=y;
    f[y][fc[y]++]=x;
  }
  q=n;
  char s[32];
  for(int v=n;v--;){
    char * w=s, *r=s;
    *w++=v;
    d[v][v]=0;
    p[v][v]=v;
    while(r<w){
      int i=*r++;
      for(int j=fc[i];j--;){
        int z=f[i][j];
        if(d[v][z]> d[v][i]+1){
          d[v][z]=d[v][i]+1;
          p[v][z]=i;
          *w++=z;
        }
      }
    }
  } 
  r=R;
  for(int a=n;a--;)
    for(int z=0;z<fc[a];z++){
      int b=f[a][z];
      if(a<b){
        r[n]=n;
        CLEAR(l1);
        CLEAR(l2);
        for(int i=n;i--;){
          r[i] =  d[i][a] < d[i][b] ? p[a][i] : p[b][i];
          c[ r[i] ]++;  
        }
        c[a]--;
        c[b]--;
        r[b]=r[a]=n;
        c[n]=2;
        go();
      }    
    }
  for(int v=n;v--;){
    r=p[v];
    CLEAR(l1);
    CLEAR(l2);
    for(int i=n;i--;)
      c[ r[i] ]++;  
    c[v]--;
    go();
  }
}
int main(){
  int d;
  scanf("%d",&d);
  for(int t=1;t<=d;t++){
    solve();
    printf("Case #%d:\n%d\n\n",t,q);
  }  
}
