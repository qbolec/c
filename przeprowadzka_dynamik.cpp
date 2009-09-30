#include<iostream>
using namespace std;
int n,k,i,j,l,x,s[1001],L[101],M[1001][101];
int main(){
  cin>>n>>k;
  for(i=0;i<n;i++){
    cin>>x;
    x=s[i+1]=s[i]+x;
    for(j=k;j>1;j--){
      l=L[j];
      while(l<i&&M[l+1][j-1]<x-s[l])
        l++;
      M[i+1][j]=M[l][j-1]>?x-s[l];
      L[j]=l;
    }
    M[i+1][1]=x;
    L[1]=i;
  }
  cout<<M[n][k];
}
