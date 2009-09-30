#include<cstdlib>
#include<cstdio>
int main(){
  int n=50000;
  printf("%d\n",n);
  for(int i=n;i--;){
    printf("%d ",rand()%60000);
  }
}
