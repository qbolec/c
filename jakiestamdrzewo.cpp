#include<cstdio>
#include<cstdlib>
int main(){
  int n =100;
  printf("%d\n",n);
  puts("0");
  int id=2;
  for(int i=0;i<10;i++){
    for(int j=0;j<9;j++){
      printf("%d ",id-1);
      id++;
    }
    printf("%d ",id-10);
    id++;
  }
  int k=4;
  printf("%d\n",k);
  scanf("%d",&k);
}
