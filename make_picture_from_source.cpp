#include<cstdio>
using namespace std;
int main(){
  int cnt=0;
  while(1){
    char c;
    if(scanf(" %c",&c)!=1)
      return 0;
    printf("%c",c);
    if(!(++cnt%50))
      printf("\n");
  }  
}
