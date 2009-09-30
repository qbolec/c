#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int t[51];
vector<int> todo;
vector<int> kid[51];
int c[51];
int kids[51];
char hash[51][1000];
int main(){
  int n;
  while(1){
    long long res=1;
    scanf("%d",&n);
    if(!n)return 0;
    for(int i=1;i<=n;i++)
      c[i]=0;
    for(int i=1;i<=n;i++){
      scanf("%d",t+i);
      kid[t[i]].push_back(i);
    }
    int tdc=0;
    for(int i=1;i<=n;i++){
      if(!(c[i]=kid[i].size()))
        todo.push_back(i);    
    }    
    long long fixedpoints=1;
    while(todo.size()){
      int v=todo.back();
      todo.pop_back();
      hash[v][0]=kids[v]+1;
      hash[v][1]=0;
      vector<char *> hashes;
      for(int i=0;i<kids[v];i++){
        int c=kid[v][i];
        hashes.push_back( hash[c] );
      }
      sort(hashes.begin(),hashes.end());
      char * w=&hash[v][1];
      for(int i=hashes.size();i--;)
        for(int j=0;hashes[i][j];j++)
          *w++= hashes[i][j];
      int cnt=0;
      for(int i=hashes.size()-1;i--;)
        if(!strcmp(hashes[i],hashes[i+1])){
          cnt++;
        }else{
          fixedpoints*=cnt;
          cnt=1;
        }
      if(!--c[ t[v] ])
        todo.push_back(t[v]);
      fixedpoints*=cnt;
    }
    for(int i=1;i<=n;i++)
      if(c[i]==1){
        vector<int> cycle;
        for(int j=i;c[j]==1;j=t[j]){
          cycle.push_back(j);
          c[j]=0;
        }
        cnt=1;
        for(int j=cycle.size();--j;){
          bool failed=false;
          for(int k=cycle.size();k--;)
            if(!strcmp(hash[k],hash[(k+j)%cycle.size()])){
              failed=true;
              break;
            }
          if(!failed)
            cnt++;
        }
        fixedpoints*=cnt;
        
      }
    printf("%lld\n",res);    
  }
}
