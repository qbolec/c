#include<cstdio>
int main(){
  const int W=(1<<23)-1;
  for(int i=1<<12;i--;){
    int x=W;
    int y=0;
    for(int j=22;j>=11;j--)
      if(x & (1<<j)){
        x^= ( i << (j-11) );
        y^= ( 1 << (j-11) );
      }
    if(!x){
      x=W;
      printf("%d razy %d=%d\n",i,y,W);
    }
    
  }
}
