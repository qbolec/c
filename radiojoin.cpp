#include<cstdio>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
using namespace std;
typedef pair<int,int> p2;
int t,s,p;
int x[1000];
int y[1000];
int u[1000];
int find(int x){
  if(u[x]<0)
    return x;
  return u[x]=find(u[x]);
}
void join(int a,int b){
  if(u[a]<u[b]){
    u[b]=a;
  }else if(u[b]<u[a]){
    u[a]=b;
  }else{
    u[a]=b;
    u[b]--;
  }
}
int main(){
  scanf("%d",&t);
  while(t--){
    scanf("%d%d",&s,&p);
    for(int i=0;i<p;i++)
      scanf("%d%d",x+i,y+i);    
    vector<pair<int,p2> > lod;
    for(int i=0;i<p;i++)
      for(int j=0;j<i;j++)
        lod.push_back( make_pair((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]), p2(i,j) ));
    sort(lod.begin(),lod.end());
    int need=0;
    for(int i=0;i<p;i++)
      u[i]=-1;
    for(int i=0;i<lod.size() && p>s;i++){
      int a=find(lod[i].second.first);
      int b=find(lod[i].second.second);
      if(a!=b){
        p--;
        need=lod[i].first;
        join(a,b);
      }        
    }
    printf("%.2lf\n",sqrt( need ));
  }
  return 0;
}
