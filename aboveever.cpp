#include<cstdio>
using namespace std;
int c,n,x[1001];
int main(){
  scanf("%d",&c);
  while(c--){
    scanf("%d",&n);
    int s=0;
    for(int i=0;i<n;i++){
      scanf("%d",x+i);
      s+=x[i];
    }
    int z=0;
    for(int i=0;i<n;i++){
      if(x[i]*n>s)
        z++;
    }
    printf("%.3lf%%\n",(double)z*100.0/n);
  }
  return 0;
}
