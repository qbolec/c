#include<cstdio>
#include<cstdlib>
int s[64];
int main(){
  s[0]=1;
  s[1]=2;
  for(int i=3;i<64;i+=2){
    for(int a=1;a+1<i;a+=2)
      s[i]>?=1+s[a]*s[i-1-a];
    printf("%d %d\n",i,s[i]);
  }
  system("PAUSE");
}
