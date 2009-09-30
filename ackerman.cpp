#include<cstdio>
#include<cstdlib>
const int Q=110;
int ack[Q][Q];
int a[Q][Q][Q];
int m[Q][Q];
int s[Q][Q];
int main(){
  for(int c=1;c<Q;c++)
    ack[1][c]=2*c;
  for(int r=2;r<Q;r++){
    ack[r][1]=2;
    for(int c=2;c<Q;c++)
      ack[r][c]=(ack[r][c-1]<Q)?ack[r-1][ack[r][c-1]]:127;
  }
  
  for(int r=1;r<Q;r++){    
    for(int c=1;c<Q;c++){      
      for(int t=1;t<Q;t++){
        if(c==1)a[r][c][t]=2%t;
        else if(r==1)a[r][c][t]=(2*c)%t;
        else{
          a[r][c][t]= 
            ack[r][c-1] < Q ? 
            a[r-1][ ack[r][c-1] ][t] : 
            a[r-1][ s[r-1][t]+ (a[r][c-1][ m[r-1][t] ]-s[r-1][t]%m[r-1][t]+m[r-1][t])%m[r-1][t]  ][t];
        }
      }
    }
    if(r==1){
      for(int t=0;t<Q/2;t++){
        m[r][t*2]=t;
        m[r][t*2+1]=t*2+1;
      }
      for(int t=0;t<Q;t++)
        s[r][t]=1;
    }else{
      for(int t=1;t<Q;t++){
        int seen[Q];
        for(int x=0;x<t;x++)seen[x]=0;
        for(int c=1;c<Q;c++){      
          if(c>10 && seen[ a[r][c][t] ] ){
            m[r][t]=c-seen[a[r][c][t]];
            s[r][t]=seen[a[r][c][t]];
            break;
          }else
            seen[a[r][c][t]]=c;
        }
    
      } 
    }
  }
 
  int T;
  scanf("%d",&T);
  while(T--){
    int t;
    scanf("%d",&t);
    for(int i=1;;i++){
      int r,c;
      scanf("%d %d",&r,&c);
      if(!r && !c)break;
      printf("Case %d: %d\n",i,a[r][c][t]);
    }
    if(T)puts("");
  }
}
