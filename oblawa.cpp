#include<cstdio>
#include<vector>
using namespace std;
vector<int> v[300000];
int k[300000];
int c,p,f,n,m;
bool flow(int i){
  if(k[i]==f)
    return false;
  if(i==2*(p-1))
    return true;
  k[i]=f;  
  for(int j=0;j<v[i].size();j++)
    if(flow(v[i][j])){
      v[v[i][j]].push_back(i);
      if(i!=1 && v[i][j]!=2*(p-1)){
        v[i][j]=v[i].back();
        v[i].pop_back();
      }
      return true;
    }
  return false;
}
int main(){
  scanf("%d",&c);
  while(c--){
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++)
      scanf("%d %d",&p,&p);
    scanf("%d",&p);
    for(int i=p*2+n+20;i--;)
      k[i]=-1;
          
    for(int i=0;i<p;i++){
      v[i*2].push_back(i*2+1);      
      int z,x;
      scanf("%d",&z);
      for(int j=0;j<z;j++){
        scanf("%d",&x);
        v[p*2+x].push_back(2*i);
        v[2*i+1].push_back(p*2+x);
      }
    }
    f=0;
    while(flow(2*0+1))f++;
    for(int i=p*2+n+20;i--;)
      v[i].clear();
    printf("%d\n",f);
  }
  return 0;
}
