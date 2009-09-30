#include<cstdio>
#include<vector>
using namespace std;
int parent[7000];
vector<int> children[7000];
int with[7000];
int without[7000];
int val[7000];
int n;
void go(int id){
  with[id]=val[id];
  for(int i=0;i<children[id].size();i++){
    go(children[id][i]);
    without[id]+= (with[children[id][i]] >? without[children[id][i]]);
    with[id]+=without[children[id][i]];
  }
}
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    scanf("%d",val+i);
  while(1){
    int k,l;
    scanf("%d %d",&k,&l);
    parent[k]=l;
    if(!k && !l)
      break;
  }
  int root=0;
  for(int i=1;i<=n;i++){
    if(!parent[i])
      root=i;
    children[parent[i]].push_back(i);
  }
  go(root);
  printf("%d",with[root]>?without[root]);
}
