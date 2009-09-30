#include<cstdio>
#include<algorithm>
using namespace std;
int n;
int h[50005];
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    h[i]=i;
  for(int i=2;i<=n;i++){
    int o=i-1;
    while(o!=1){
      swap(h[o],h[o/2]);
      o=o/2;
    }    
    swap(h[1],h[i]);
  }
  for(int i=1;i<=n;i++)
    printf(" %d",h[i]);
  printf("\n");
  return 0;
}
