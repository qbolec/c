#include<cstdio>
#include<iostream>
using namespace std;
long long h[9+1][18+1][9*18+1];
long long hh[18+1][9*18+1];
long long hhh[9*18+1];
int main(){
  for(int i=0;i<=9;i++)
    hh[1][i]=h[i][1][i]=1;
  
  for(int l=2;l<=18;l++){
    for(int f=0;f<=9;f++)
      for(int w=f;w<=9*l;w++)
        h[f][l][w]=hh[l-1][w-f];
    for(int w=0;w<=9*l;w++)
      for(int f=0;f<=9;f++)
        hh[l][w]+=h[f][l][w];   
  }
  while(1){
    long long n,k,m;
    cin >> n >> k;
    if(!n && !k)return 0;
    int wb=0;
    long long d=100000000000000000LL;
    m=n;
    memset(hhh,0,sizeof(hhh));
    for(int l=18;l;l--){
      if(l>1){
        for(int i=0;i<10;i++){
          if(d*(i+1)<=m){
            for(int w=0;w<=9*l;w++)
              hhh[w+wb]+=h[i][l][w];
          }else{
            m-=d*i;
            wb+=i;
            d/=10;
            break;
          }
        }
      }else{
        for(int i=0;i<=m;i++)
          hhh[i+wb]++;
      }
    }
    long long s=-1;
    int x_w=0;
    for(int w=0;w<=9*18;w++){
      s+=hhh[w];
      if(s>=k){
        x_w=w;
        break;
      }
    }
    cout << "waga szukanego slowa to :" << x_w << endl;
    
  }
}
