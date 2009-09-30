#include<cstdio>
#include<vector>
using namespace std;
int vis[1024];
int skl[1024];
int ok[1024];
vector<int> stack;
int color=0;
int sklad=0;
vector<vector<int> > win;
vector<vector<int> > lose;
void dfs(int id){
  vis[id]=color;
  for(int i=win[id].size();i--;)
    if(vis[win[id][i]]!=color)
      dfs(win[id][i]);
  stack.push_back(id);
}
void dfs2(int id){
  vis[id]=color;
  skl[id]=sklad;
  for(int i=lose[id].size();i--;)
    if(vis[lose[id][i]]!=color)
      dfs2(lose[id][i]);
}
void solve(){
  color++;
  int n;
  scanf("%d",&n);  
  sklad=0;  
  win.clear();
  lose.clear();
  win.resize(n);
  lose.resize(n);
  for(int i=0;i<n;i++){
    int k;
    scanf("%d",&k);
    lose[i].resize(k);
    for(int j=k;j--;){
      scanf("%d",&lose[i][j]);
      lose[i][j]--;
      win[lose[i][j]].push_back(i);
    }
  }
  for(int i=0;i<n;i++)
    if(vis[i]!=color)
      dfs(i);
  color++;

  while(stack.size()){    
    int id=stack.back();
    stack.pop_back();
    if(vis[id]!=color){
      dfs2(id);
      ok[sklad++]=true;
    }
  }
  for(int i=0;i<n;i++)
    for(int j=win[i].size();j--;)
      if(skl[i] != skl[ win[i][j] ])
        ok[skl[ win[i][j] ]]=false;
  int cool=-1;
  for(int i=0;i<sklad;i++)
    if(ok[i])
      if(cool>=0){
        puts("0");
        return;
      }else
        cool=i;    
  int cnt=0;
  for(int i=0;i<n;i++)
    if(skl[i]==cool)
      cnt++;
  printf("%d\n",cnt);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
  return 0;
}
