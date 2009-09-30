#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
int wp[505][505];
int ml[505][505];
int p[505];
int maz[505];
int zona[505];
int n;
void solve(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    int x;
    scanf("%d",&x);
    for(int j=0;j<n;j++)
      scanf("%d",&wp[x][j]);
  }
  for(int i=0;i<n;i++){
    int x;
    scanf("%d",&x);
    for(int j=1;j<=n;j++){
      int y;
      scanf("%d",&y);
      ml[x][y]=j;
    }
  }
  for(int i=1;i<=n;i++){
    p[i]=i;
    maz[i]=0;
    zona[i]=0;
  }
  random_shuffle(p+1,p+n+1);
  reverse(p+1,p+n+1);
  random_shuffle(p+1,p+n+1);
  for(int i=1;i<=n;i++){
    int w=p[i];
    while(w){
      int s=maz[w];
      for(int i=s;i<n;i++){
        int m=wp[w][i];
        if(!zona[m]){
          zona[m]=w;
          maz[w]=i;
          w=0;
          break;
        }else if(ml[m][zona[m]]>ml[m][w]){
          int k=zona[m];
          zona[m]=w;
          maz[w]=i;
          w=k;
          break;
        }
      }
    }
  }
  for(int i=1;i<=n;i++){
    printf("%d %d\n",i,zona[i]);
  }
}
  
int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
}
