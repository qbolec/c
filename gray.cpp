#include<cstdio>
int main(){
  int g[64]={0,1};
  for(int i=2;i<64;i++){
    printf("kodem dla %d jest %d\n",i,g[i]=i^(i/2));
  }
}
