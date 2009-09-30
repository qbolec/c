#include<cstdio>
using namespace std;
int n,t;
unsigned char cnt[1024*1024/8];
void point(int x,int y){
  for(int xx=x;xx<n;xx|=xx+1){
    unsigned char * cntxxn8=cnt+xx*n/8;
    for(int yy=y;yy<n;yy|=yy+1)
      cntxxn8[yy/8]^=1<<(yy&7);  
  }
}
int query(int x,int y){
  unsigned char c=0;
  for(int xx=x;xx>=0;xx=(xx&(xx+1))-1){
    unsigned char * cntxxn8=cnt+xx*n/8;
    for(int yy=y;yy>=0;yy=(yy&(yy+1))-1)
      c^=cntxxn8[yy/8]>>(yy&7);
  }
  return c&1;
}
void solve(){
  scanf("%d %d",&n,&t);
  n++;
  while(n&7)n++;
  for(int x=n*n/8;x--;)
    cnt[x]=0;
  while(t--){
    char c;
    int x1,x2,y1,y2;
    scanf(" %c",&c);
    if(c=='C'){
      scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
      point(x1,y1);
      point(x2+1,y2+1);
      point(x1,y2+1);
      point(x2+1,y1);
    }else{
      scanf("%d %d",&x1,&y1);      
      printf("%d\n",query(x1,y1));
    }
  }
  puts("");
}
int main(){
  int x;
  scanf("%d",&x);
  while(x--)
    solve();
  return 0;
}
