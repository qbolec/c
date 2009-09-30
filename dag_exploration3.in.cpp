#include<cstdio>
int main(){
  printf("X X\n");
  for(int i=0;i<10;i++){
    printf("0 %d\t",i*10+1);
    for(int j=1;j<10;j++)
      printf("%d %d\t",j+10*i,j+1+10*i);
    puts("");
  }
  int f=101;
  for(int i=1;i<=10;i++){
    printf("%d %d\n",i*10,f++);
  }
  for(int i=10;i<100;i+=10){
    printf("%d %d\n",i,i+10);
  }
}

