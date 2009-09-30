#include<cstdio>
#include<vector>
using namespace std;
int g[20]={
  1 ,
2 ,
7 ,
5 ,
30 ,
169 ,
441 ,
1872 ,
7632 ,
1740 ,
93313 ,
459901 ,
1358657 ,
2504881
};
vector<int> p;
bool check(int m,int l,int w){
  while(w--){
    if(p[(l+m)%p.size()]>0)
      return false;
    l=(l+m)%p.size();
    p.erase(p.begin()+l);
    if(l==p.size())l=0;
  }
  return true;
}
bool check(int k,int m){
  p.resize(2*k);
  for(int i=0;i<k;i++)p[i]=1;
  for(int i=k;i<2*k;i++)p[i]=-1;
  return check(m,0,k);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    int k;
    scanf("%d",&k);
    printf("%d\n",g[k]);
  }
}
