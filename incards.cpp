#include<cstdio>
#include<vector>
using namespace std;
void solve(){
  int n,m;
	scanf("%d %d",&n,&m);
  vector< vector<pair<int,int> > > graf(n+1);
  vector<int> indeg(n+1,0);
	for(int i=0;i<m;i++){
		int f,t,c;
		scanf("%d %d %d",&f,&t,&c);
		t--;
		f--;
		if(t==0)t=n;
		graf[f].push_back( make_pair( t, c) );
    indeg[t]++;
	}
	vector<int> td;
  for(int i=0;i<=n;i++)
    if(!indeg[i])
      td.push_back(i);
  vector<int> sorted;
  int r=0;
  while(r<td.size()){
    int id=td[r++];
    sorted.push_back(id);
    for(int i=graf[id].size();i--;)
      if( !--indeg[ graf[id][i].first ])
        td.push_back( graf[id][i].first );
  }
  const int INF=2000000000;
  vector<int> there(n+1,INF);
  vector<int> from(n+1,INF);
  there[0]=0;
  from[n]=0;
  int cnt=0;
  for(int i=0;i<=n;i++){
    int id=sorted[i];
    if(id!=n)
      cnt+= there[id];
    for(int j=graf[id].size();j--;)
      there[graf[id][j].first] <?= there[id]+ graf[id][j].second ;
  }
  for(int i=n;i>=0;i--){
    int id=sorted[i];
    for(int j=graf[id].size();j--;)
      from[ id] <?= from[ graf[id][j].first ] + graf[id][j].second;
    if(id!=0)
      cnt+= from[id];
  }
  
  printf("%d\n",cnt);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
  return 0;
}
	
