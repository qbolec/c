#include<cstdio>
using namespace std;
int x,n,s,b,m;
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    scanf("%d",&x);
    s+= x*2-n+1;
    if(s>b){
      m=i+1;
      b=s;
    }     
  }
  printf("Best move: %d\n",m);
}
