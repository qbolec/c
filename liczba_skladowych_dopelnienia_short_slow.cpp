#include<cstdio>
//#include<vector>
#include<algorithm>
char data[28500000];
char *t=data;
using namespace std;
int n,m;
int ev[100000];
int c[100000];
int ile[100000];
vector<int> g[100000];
int cnt[100001];
int *s =stack;
int find(int x){
  if(c[x]<0)return x;
  return c[x]=find(c[x]);
}
void unite(int a,int b){
  if(a!=b){
    if(c[a]<c[b]){
      c[b]=a;
    }else if(c[b]<c[a]){
      c[a]=b;
    }else{
      c[a]=b;
      c[b]--;
    }
  }
}
#define zlep(id,f,t) if(f<t-1)unite(id,find(f+1));

int main(){
  scanf("%d %d ",&n,&m);
  memset(ev,127,sizeof(int)*n);
  for(int i=0;i<m;i++){
    int a,b;
    scanf("%d%d",&a,&b);
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  for(int i=0;i<n;i++)
    sort(g[i].begin(),g[i].end());
  for(int i=0;i<n;i++){
    if(g[i].empty()){
      printf("1\n%d\n",n);
      return 0;
    }
    if(g[i].front())
    if(edges[cnt[i]])ev[edges[cnt[i]]-1]=0;
    ev[n-1]<?=edges[cnt[i+1]-1]+1;
    for(int j=cnt[i];j<cnt[i+1]-1;j++)
      ev[edges[j+1]-1]<?=edges[j]+1;
  }

  for(int i=0;i<n;i++){
    if(ev[i]<i)
      while(s!=stack && ev[i]<=s[-1])
        --s;
    *s++=i;
  }
  int p=0;
  for(int * z=stack;z<s;z++){
    while(p<*z)
      c[p++]=*z;
    c[p++]=-1;
  }
  for(int i=0;i<n;i++){
    int id=find(i);
    zlep(id,-1,edges[cnt[i]]);
    zlep(id,edges[cnt[i+1]-1],n);
    for(int j=cnt[i];j<cnt[i+1]-1;j++)
      zlep(id,edges[j],edges[j+1]);
  }
  s=stack;
  int wynik=0;
  for(int i=0;i<n;i++){
    if(0>c[i]){
      wynik++;
      *s++=i;
    }
    ile[find(i)]++;
  }
  printf("%d\n",wynik);
  for(int *i=stack;i<s;i++)
    *i=ile[*i];
  sort(stack,s);
  for(int *i=stack;i<s;i++)
    printf("%d ",*i);
  puts("");
}
