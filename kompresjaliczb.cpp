#include<cstdio>
using namespace std;
unsigned int a,b;
int main(){
  while(scanf("%u-%u",&a,&b)==2){
    printf("%u-",a);
    for(unsigned int mod=10,c=1;;mod*=(mod<1000000000)?10:3,c++)
      if(a== ((a%mod < b%mod )?(a-a%mod+b%mod):(a+mod-a%mod+b%mod))){
        printf("%0*u\n",c,b%mod);
        break;
      }
  }
}
