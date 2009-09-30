#include<vector>
#include<utility>
#include<cstdio>
int n,m;
int deg[100001];
int visit[100001];
int color=666;
int dek;
vector<int> graf[100001];
vector< pair<int,int> > input;
vector< pair<int,int> > output;
bool dfs(int id){
  if(visit[id]==color)
    return false;
  if(deg[id]<=dek){    
    return true;
  }
  visit[id]=color;
  
  for(int i=0;i<graf[id].size();i++){
    int c= input[graf[id][i]].first+input[graf[id][i]].second- id;
    if(dfs(c)){
      graf[c].push_back(graf[id][i]);
      for(int j=i+1;j<graf[id].size();j++)
        graf[id][j-1]=graf[id][j];
      graf[id].pop_back();
      deg[c]++;
      deg[id]--;
      return true;
    }
  }
  return false;
}
bool minimize(int id){
  color++;
  dek=deg[id]-2;
  return dfs( id);
}
int main(){

  scanf("%d %d",&n,&m);
  for(int i=0;i<=n;i++)
    deg[i]=visit[i]=0;
  for(int i=0;i<m;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    deg[a]++;
    input.push_back(make_pair(a,b));
    output.push_back(make_pair(a,b));
  }

  for(int t=0;t<100;t++)
    for(int i=output.size();i--;)
      if(deg[output[i].first]>deg[output[i].second]+1){
        deg[output[i].first]--;
        deg[output[i].second]++;
        swap(output[i].first,output[i].second);
      }
  for(int i=output.size();i--;)
    graf[ output[i].first] .push_back( i );
  for(int i=1;i<=n;i++)
    while(minimize(i)){}
  for(int i=1;i<=n;i++)
    for(int j=0;j<graf[i].size();j++)
      if(output[graf[i][j]].first!=i)
        swap(output[graf[i][j]].first,output[graf[i][j]].second);
  int k=0;
  for(int i=1;i<=n;i++)
    k>?=deg[i];  
  printf("%d\n",k);
  for(int i=0;i<input.size();i++){
    if(input[i].first==output[i].first)
      printf("1\n");
    else
      printf("0\n");
  }
  return 0;
}
