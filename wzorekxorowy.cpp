#include<cstdio>
#include<cstdlib>
int main(){
  for(int r=0;r<16;r++){
    for(int c=0;c<16;c++){
      int x=c&r;
      printf("%c",x==r?'x':' ');
    }
    puts("");
  }
  system("pause");
}
