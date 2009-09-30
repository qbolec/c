#include"gra_lib.c"
#include<algorithm>
using namespace std;
int main() {
  int n=getN(0);
  int a=1;
  int b=n+1;
  int A,B;
  if(isLess((a+b)/2)){
    B=(a+b)/2;
    while(isLess((a+B)/2)){
      printf("a=%d A=%d B=%d b=%d\n",a,A,B,b);
      b=B;
      B=(a+B)/2;
      if(a+1==b){
        answer(a);
        return 0;
      }
    }
    A=(a+B)/2;
  }else{
    A=(a+b)/2;
    while(isLess((A+b)/2)){
      printf("a=%d A=%d B=%d b=%d\n",a,A,B,b);
      a=A;
      A=(a+B)/2;
      if(a+1==b){
        answer(a);
        return 0;
      }
    }
    B=(a+B)/2;
  }
  while(a+1<b){
    printf("a=%d A=%d B=%d b=%d\n",a,A,B,b);
    if(isLess((a+b)/2)){
      int bB=(a+b)/2;
      int t[3]={b,bB,B};
      sort(t,t+3);
      B=t[0];
      b=t[1];
    }else{
      int aA=(a+b)/2;
      int t[3]={a,aA,A};
      sort(t,t+3);
      a=t[1];
      A=t[2];
    }
  }
  answer(a);
  scanf("%*d");
  return 0;
}
