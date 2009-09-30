#include<cstdio>
#include<vector>
using namespace std;
int f,t,n,m,best,cnt;
const int MAX_N=1000010;
vector<int> gt[MAX_N];
int degout[MAX_N];
unsigned short int ways[MAX_N];
vector<int> stack;
int main(){
  scanf("%d %d",&n,&m);
  for(int i=0;i<m;i++){
    scanf("%d %d",&f,&t);
    degout[f]++;
    gt[t].push_back(f);
  }
  stack.push_back(n+1);
  while(stack.size()){
    int id=stack.back();
    stack.pop_back();
    ways[id]=1;
    for(int i=gt[id].size();i--;)
      if(ways[ gt[id][i] ] < 1)
        stack.push_back( gt[id][i] );
  }
  ways[n+1]=2;  
  for(int i=n+1;i;i--)
    if(!degout[i])
      stack.push_back(i);
  while(stack.size()){
    int id=stack.back();
    stack.pop_back();
    int w= !ways[id]?0:ways[id]-1;
    for(int i=gt[id].size();i--;){
      if(!--degout[gt[id][i]])
        stack.push_back(gt[id][i]);
      int z=ways[gt[id][i]]+w;
      ways[gt[id][i]]= z <? 36502;
    }
  }
  for(int i=0;i<=n;i++){    
    if(ways[i]>0 && degout[i])
      ways[i]=36502;
    best >?= ways[i];
  }
  if(best>36501)
    puts("zawsze");
  else
    printf("%d\n",best-1);
  for(int i=0;i<=n;i++)
    if(ways[i]==best)
      cnt++;
  printf("%d\n",cnt);
  for(int i=0;i<=n;i++)
    if(ways[i]==best)      
      printf("%d ",i);  
  puts("");
  return 0;
}
