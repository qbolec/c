#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char t[3000];
char s[3000];
vector<int> mul(vector<int>& a,vector<int>& b){
  vector<int> r(a.size());
  for(int i=0;i<a.size();i++)
    r[i]=b[a[i]];
  return r;
}
vector<int> pow(vector<int> a,int k){
  vector<int> r(a.size());
  for(int i=0;i<r.size();i++)r[i]=i;
  while(k){
    if(k&1){
      r=mul(r,a);
    }
    a=mul(a,a);
    k>>=1;
  }
  return r;
}
void solve(){
  int n,m,k;
  scanf("%d %d",&n,&m);
  vector<int> a(n+1);
  a[0]=0;
  for(int i=0;i<n;i++)
    scanf("%d",&a[1+i]);
  for(int i=0;i<m;i++){
    scanf("%d",&k);
    memset(t,' ',n+4);
    gets(t);
    memset(s,' ',n+4);
    vector<int> h=pow(a,k);
    for(int i=0;t[i];i++){
      s[h[i]]=t[i];
    }
    s[1+n]=0;
    puts(s+1);
  }
}
int main(){
  int d;
  scanf("%d",&d);
  while(d--)solve();
}
