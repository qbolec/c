#include<cstdio>
#include<algorithm>
using namespace std;
int n,cas;
int t[10];
int tl[10];
int tr[10];
int s[10];
bool go(int id){
  for(int j=0;j<n;j++)
    if(tl[j]==id){
        if(s[tr[j] ]>=0 && (s[ tr[j] ] != s[id]+ t[j]))
          return false;        
        if(s[tr[j]]<0){
          s[ tr[j] ] = s[id]+ t[j];
          if(s[tr[j]]<0)
            return false;
          if(!go(tr[j]))
            return false;
        }
      }        
  for(int j=0;j<n;j++)
    if(tr[j]==id){
        if(s[tl[j]]>=0 && (s[ tl[j] ] != s[id]- t[j]))
          return false;        
        if(s[tl[j]]<0){
          s[ tl[j] ] = s[id]- t[j];
          if(s[tl[j]]<0)
            return false;
          if(!go(tl[j]))
            return false;
        }
      }        
  return true;
}
bool test(int rails){
  bool used[10];
  for(int i=0;i<rails;i++)
    used[i]=false;
  for(int i=0;i<n;i++){
    used[tr[i]]=true;
    used[tl[i]]=true;
  }
  for(int i=0;i<rails;i++)
    if(!used[i])
      return false;  
  s[0]=0;
  for(int i=1;i<rails;i++)
    s[i]=-1;
  if(go(0)){
    for(int i=0;i<rails;i++)
      if(s[i]<0)
        return false;
    printf("Scenario #%d\n%d:",cas,rails);
    sort(s,s+rails);
    for(int i=0;i<rails;i++)
      printf("%d ",s[i]);
    printf("\n\n");
    return true;
  }else
    return false;
}
bool doall(int rails,int pos){
  if(pos==n)
    return test(rails);
  for(int i=0;i<rails;i++)
    for(int j=0;j<i;j++){
      tl[pos]=j;
      tr[pos]=i;
      if(doall(rails,pos+1))
        return true;      
    }
  return false;
}
bool can(int rails){
  return doall(rails,0);
}
void solve(){
  scanf("%d",&n);
  for(int i=0;i<n;i++)
    scanf("%d",t+i);
  for(int r=2;r<8;r++)
    if(can(r))
      return;  
  
}
int main(){
  int c;
  scanf("%d",&c);
  for(cas=1;cas<=c;cas++)
    solve();
  return 0;
}
