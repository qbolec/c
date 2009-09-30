#include<vector>
#include<cstdio>
#include<iostream>
using namespace std;
template<class C>
bool kmp(vector<C> needle, vector<C> haystack){
  vector<int> b;
  b.resize(needle.size()+1);
  b[0]=b[1]=0;
  for(int i=2;i<b.size();i++){
    int k=i;
    while( k && (needle[ b[k-1] ]!=needle[ i-1 ] || needle[b[k-1]+1]==needle[i]  ) )
      k=b[k-1];
    b[i]=k?b[k-1]+1:0;    
  }
  int fit=0;
  for(int p=0;p<haystack.size();p++){
    while(fit && haystack[p]!=needle[fit])
      fit=b[fit];
    if(haystack[p]== needle[fit])
      fit++;
    if(fit==needle.size())
      return true;
  }
  return false;
}
int main(){
  vector<int> A;
  vector<int> B;
  int a,b;
  scanf("%d %d",&a,&b);
  while(a--){
    int x;
    scanf("%d",&x);
    A.push_back(x);
  }
  while(b--){
    int x;
    scanf("%d",&x);
    B.push_back(x);
  }
  if(kmp(A,B))
    cout << "YES" << endl;
  else
   cout << "NO" << endl;
  return 0;
}
