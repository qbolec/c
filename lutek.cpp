#include<cstdio>
using namespace std;
int c,n,k;
int main(){
  scanf("%d",&c);
  while(c--){
    scanf("%d %d",&n,&k);
    puts((n|k|n-k)^n?"P":"N");
  }
}
