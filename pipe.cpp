#include<cstdio>
using namespace std;
int x1,y1,x2,y2;
int L[4];
int C[4]={0,0,0,0};
int k;
int W[4];
int N[4];
#define abs(x) (x<0?-x:x)
int best=10000;
void go(int id,int x,int y,int cnt){
  if(id==k-1){
    if(!((x2-x)%L[id]) && !((y2-y)%L[id])){
      W[id]=(x2-x)/L[id];
      N[id]=(y2-y)/L[id];
      if(abs(W[id])+abs(N[id])<= C[id]){
        cnt+=abs(W[id])+abs(N[id]);
        best <?= cnt;    
      }
    }      
  }else{
    for(W[id]= -C[id];W[id]<=C[id];W[id]++){
      int f=C[id]-abs(W[id]);
      for(N[id]=-f;N[id]<=f;N[id]++)
        go(id+1,x+W[id]*L[id],y+N[id]*L[id],cnt+abs(W[id])+abs(N[id]));
    }
  }
}
int main(){
  scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2,&k);
  for(int i=0;i<k;i++)
    scanf("%d",L+i);
  for(int i=0;i<k;i++)
    scanf("%d",C+i);
  go(0,x1,y1,0);
  printf("%d\n",(best<10000)?best:-1);
  return 0;
}
