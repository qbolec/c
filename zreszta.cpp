#include<cmath>
#include<cstdio>
int t[100];
int main(){
  for(int m=2;m<100;m++){
    for(int i=0;i<m;i++)
      t[i*i%m]=m;
    bool ok=true;
    for(int i=0;i<m;i++)
      if(t[i]!=m){
        ok=false;
        break;
      }
    if(ok)printf("%d ok\n",m);
  }
  scanf("%d",&t);
}
