#include<set>
#include<map>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<utility>
#include<cmath>
#include<sstream>
using namespace std;
int pc=0;
const int N=1000000;
int * s;
vector<int> p,k,tmp;
void go(int b=0,int x=1){
  if(b==p.size()){
    tmp.push_back(x);
    return;
  }
  int t=1;
  for(int i=k[b];i>=0;i--){
    go(b+1,x*t);
    t*=p[b];
  }
}
vector<int> divisors(int x){
  p.clear();
  k.clear();
  while(x>1){
    int v=s[x];
    if(!p.empty() && p.back()==v){
      k.back()++;
    }else{
      p.push_back(v);
      k.push_back(1);
    }
    x/=v;
  }
  tmp.clear();
  go();
  return tmp;
}
void sito(){
  s=new int[N];
  s[0]=0;
  s[1]=1;
  for(int i=2;i<N;i++)
    if(!s[i]){
      pc++;
      if(i<N/i)
      for(int j=i*i;j<N;j+=i)
        s[j]=i;
    }
}
const int D=30;
long long P[D][D];
bool is_sorted(char *a){
  for(int i=1;a[i];i++)
    if(a[i]<a[i-1])
      return false;
return true;
}
int cnt,sum;
int main(){
  sito();
  for(int x=10;cnt<11;x++)if(!s[x]){
    char a[10];
    sprintf(a,"%d",x);
    bool bad=false;
    int i;
    for(i=1;a[i];i++){
      int y;
      sscanf(a+i,"%d",&y);
      if(s[y]){
        bad=true;
        break;
      }
    }
    if(!bad){
      for(;i;i--){
        a[i]=0;
        int y;
        sscanf(a,"%d",&y);
        if(s[y]){
          bad=true;
          break;
        }
      }
    }
    if(!bad){
      printf("%d\n",x);
      sum+=x;
      cnt++;
    }
  }
  printf(" %d\n",sum);
  system("PAUSE");
}
//15351393371
//15372428665
//17924657155
