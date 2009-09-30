#include<cstdio>
#include<iostream>
using namespace std;
unsigned long long sum(unsigned long long x,unsigned long long y){
  unsigned long long r=x+y;    
  if(r<x || r<y) return ~0LL;
  return r;
}
int main(){
  unsigned long long limit[101][65];//limit[k][r]  = maxymalne n ze majac k zarowek da sie w r ruchach
  limit[0][0]=1;
  for(int i=1;i<=64;i++)
    limit[0][i]=1;
  limit[1][0]=1;
  for(int i=1;i<=64;i++)
    limit[1][i]=i+1;
  for(int k=2;k<=100;k++){
    limit[k][0]=1;
    for(int r=1;r<=64;r++){
      limit[k][r]=limit[k-1][r];
      limit[k][r]>?=sum(limit[k-1][r-1],limit[k][r-1]);
    }
  }
  while(1){
    int k;
    unsigned long long n;
    cin >> k >> n;
    if(!k)return 0;
    int i;
    for(i=0;i<64;i++)
      if(limit[k][i]>n){
        cout << i << endl;
        break;
      }
    if(i==64)  cout <<"More than 63 trials needed." << endl;
  }
}
