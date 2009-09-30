#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    int x;
    scanf("%d",&x);
    int z[x];
    for(int i=0;i<x;i++){
      scanf("%d",z+i);
    }
    sort(z,z+x);
    int cnt=0;
    for(int i=0;i<x;i++)
      if(z[i]<=i)
        cnt++;
      else
        break;
    printf("%d\n",cnt);
  }
}
