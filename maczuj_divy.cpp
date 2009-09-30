#include<cstdio>
int buff[4];
int g=0;
int z=0;
int main(){
  int c;
  while((c=getchar())>=0){
    putchar(c);
    buff[g++&3]=c;
    if(buff[g&3]=='<' && buff[g+1&3]=='d' && buff[g+2&3]=='i' && buff[g+3&3]=='v')
      printf("%d",z++);
    else if(buff[g&3]=='<' && buff[g+1&3]=='/' && buff[g+2&3]=='d' && buff[g+3&3]=='i')
      printf("%d",--z);
  }
}
