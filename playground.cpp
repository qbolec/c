#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
  while(true){
    int k;
    scanf("%d",&k);
    if(!k)return 0;
    vector<double> f;
    for(int i=0;i<k;i++){
      double x;
      scanf("%lf",&x);
      f.push_back(x);
    }
    sort(f.begin(),f.end());
    double sum=0;
    bool ok=false;
    for(int i=0;i<k;i++){
      if(f[i]<=sum){
        puts("YES");
        ok=true;
        break;
      }
      sum+=f[i];
    }
    if(!ok)puts("NO");
  }
}
