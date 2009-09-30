#include<cstdio>
int main(){
  long long x=24386094146700LL;
  for(int i='_';i<='z';i++){
    while(x%i==0){
      printf("%c",(char)i);
      x/=i;
    }
  }
  printf("\n%d left\n",(int)x);  
}
