#include<cstdio>
#include<vector>
#include<algorithm>
char data[28500000];
char *t=data;
using namespace std;
int n,m;
int mark[100000];
int from[2000000];
int to[2000000];
int cnt[100001];
int ile[100010];
int color=2;
char gbank[5000000];//(2m/n +1)(n) = 2m + n
char * freeg=gbank;
char * g [100000];
int node[100000];
int nodes=0;
void dfs(int id){
  mark[id]=color;
  ile[color]++;
  for(int i=0;i<nodes;i++)
    if(!g[id][node[i]] && mark[node[i]]==1)
      dfs(node[i]);
}
int main(){
  scanf("%d %d ",&n,&m);
  data[fread(data,1,28500000,stdin)]=0;
  for(int i=0;i<m;i++){
    int a=0,b=0;
    while(*t<='9' && *t>='0')a=a*10+(*t++)-'0';
    t++;
    while(*t<='9' && *t>='0')b=b*10+(*t++)-'0';
    t++;
    a--;b--;
    cnt[a]++;
    cnt[b]++;
    from[i]=a;
    to[i]=b;
  }
  int d=2*m/n;
  int chosen=0;
  while(cnt[chosen]>d)chosen++;
  d=n-cnt[chosen];
  for(int i=0;i<m;i++)
    if(from[i]==chosen)
      mark[to[i]]=1;
    else if(to[i]==chosen)
      mark[from[i]]=1;
  g[chosen]=freeg;
  freeg+=n;
  node[nodes++]=chosen;
  for(int i=0;i<n;i++)
    if(mark[i]){
      g[i]=freeg;
      freeg+=n;
      node[nodes++]=i;
    }
  for(int i=0;i<m;i++)
    if(mark[from[i]] && !mark[to[i]])
      ile[from[i]]++;
    else if(!mark[from[i]] && mark[to[i]])
      ile[to[i]]++;
    else if(mark[from[i]] && mark[to[i]]){
      g[from[i]][to[i]]=1;
      g[to[i]][from[i]]=1;
    }

  for(int i=1;i<nodes;i++){
    if(ile[node[i]]==d){
      g[node[i]][chosen]=1;
      g[chosen][node[i]]=1;
    }
  }
  mark[chosen]=1;
  for(int i=0;i<n;i++)
    if(mark[i]==1){
      ile[color]=0;
      dfs(i);
      color++;
    }
  ile[mark[chosen]]+=d-1;


  printf("%d\n",color-2);
  sort(ile+2,ile+color);
  for(int i=2;i<color;i++)
    printf("%d ",ile[i]);
  puts("");
}
