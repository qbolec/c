#include<vector>
#include<utility>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef pair<int , pair<int,int> > event;
vector<event> ev;
int n;
const int M=8008;
int ss[2*M];
int * const s=ss+2;
int r[M];
vector<int> see[M];
int g;
void solve(){
  scanf("%d",&n);
  ev.resize(n);
  for(int i=n;i--;)
    scanf("%d %d %d",&ev[i].second.first,&ev[i].second.second,&ev[i].first);
  sort(ev.begin(),ev.end());
  for(int i=2*M;i--;)
    ss[i]=-1;
  for(int i=0;i<ev.size();i++){
    g++;
    see[i].clear();
    const int f=ev[i].second.first;
    const int t=ev[i].second.second;
    if( s[f-1]>s[f] && r[s[f-1]]!=g ){
      r[s[f-1]]=g;
      see[s[f-1]].push_back(i);
    }    
    if( s[t]>s[t-1] && r[s[t]]!=g ){
      r[s[t]]=g;
      see[s[t]].push_back(i);
    }    
    for(int j=f;j<t;j++){
      if(s[j]>=0 && r[s[j]]!=g){
        r[s[j]]=g;
        see[s[j]].push_back(i);        
      }
      s[j]=i;
    }
  }
  int t=0;
  for(int a=n;a--;){
    for(int bi=see[a].size();bi--;){
      int b=see[a][bi];
      for(int ci=bi;ci--;){
        int c=see[a][ci];
        if(binary_search(see[c].begin(),see[c].end(),b))
          t++;
      }
    }
  }
  printf("%d\n",t);
}
int main(){
  int d;
  scanf("%d",&d);
  while(d--)
    solve();
}
