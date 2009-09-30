#include<cstdio>
using namespace std;
int main(){
  int r,c;
  char d;
  while(1){
    if(scanf("R%02dC%02d",&r,&c)==2){
      printf("\n R = %d C = %d \n",r,c);
    }else{
      scanf("%c",&d);
    }
  }
  return 0;
}
