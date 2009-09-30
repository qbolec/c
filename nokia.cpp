#include<cstdio>
#include<cstring>
char dupa[1000000];
int main(){
  scanf("%s",dupa);
  int len=strlen(dupa);
  printf("%d",len);
  for(int i=0;i<len;i+=8){
    char x=0;    
    for(int j=0;j<8;j++){
      x<<=1;
      x|= dupa[i+j]-'0';
    }
    putchar(x);
  }
  
  scanf("%d",&len);
}
