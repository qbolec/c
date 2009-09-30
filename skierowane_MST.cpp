#include<algorithm>
#include<vector>
using namespace std;
void solve(){
  int n,m;
  scanf("%d %d",&n,&m);
  vector<pair<int,int> > g[n];
  vector<pair<int,pair<int,int> > > edges;
  for(int i=0;i<m;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    edges.push_back(make_pair(c,make_pair(a,b)));
  }
  sort(edges.begin(),edges.end());
  for(int i=0;i<edges.size();i++)
    g[edges[i].second.first].push_back(make_pair(edges[i].first,edges[i].second.second));
  int chosen[n];
  bool reaches_zero[n];
  int visited[n];
  while(true){
    for(int i=1;i<n;i++){
      chosen[i]=g[i].front().second;
    }
    fill_n(visited,n,0);
    fill_n(reaches_zero,n,false);
    reaches_zero[0]=true;
    visited[0]=true;mp
    for(int i=1;i<n;i++)
      if(!visited[i]){
        int j;
        for(j=i;!visited[j];j=chosen[j]){
          visited[j]=i;
          if(reaches_zero[chosen[j]]){
            for(int k=i;!reaches_zero[k];k=chosen[k])
              reaches_zero[k]=true;
            break;
          }
        }
        if(!reaches_zero[i] && visited[j]==i){
          for(int k=chosen[j];;k=chosen[k]){

            if(k==j)break;
          }
        }
      }
    
  }
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
}
