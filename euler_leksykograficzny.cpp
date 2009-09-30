#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
vector<vector<pair<int,int> > >g;
vector<int> eaten;
vector<bool> killed;
vector<int> r;
void go(int id){
  while( eaten[id]<g[id].size() && killed[g[id][eaten[id]].first])eaten[id]++;
  if(eaten[id]==g[id].size())return;
  int c=g[id][eaten[id]].first;
  killed[c]=true;
  go(g[id][eaten[id]++].second);
  r.push_back(c);
  go(id);
}
void solve(){
  int n,m;
  scanf("%d %d",&n,&m);
  g.clear();
  g.resize(n);
  eaten.clear();
  eaten.resize(n,0);
  killed.clear();
  killed.resize(m+2,false);
  int start=-1;
  for(int i=0;i<m;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    a--;
    b--;
    if(start<0)start=a<?b;
    g[a].push_back(make_pair(c,b));
    g[b].push_back(make_pair(c,a));
  }
  for(int i=0;i<n;i++){
    if(g[i].size()%2){
      puts("NIE");
      return;
    }
    sort(g[i].begin(),g[i].end());
  }
  r.clear();
  go(start);
  for(int i=1;i<=m;i++)
    if(!killed[i]){
      puts("NIE");
      return;
    }
  for(int i=r.size();i--;)
    printf("%d ",r[i]);
  puts("");
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
}
