#include<cstdlib>
#include<ctime>
#include<cstdio>
int main(){
  srand(time(0));
  for(int i=0;i<20;i++){
    printf("%d\n",rand()%18);
  }
  system("PAUSE");
}
