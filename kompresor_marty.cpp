#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdlib>
using namespace std;
int ppb[10000000];
int main(){
  while(true){
    int n,r;
    cout << "Podaj ilosc slow, oraz zakres z jakiego maja byc losowane ich czestosci." << endl;
    cin >> n >> r;
    for(int i=0;i<n;i++)
      ppb[i]=1+(rand()%r);
    sort(ppb,ppb+n);
    long long best=1LL<<60;
    int how=0;
    long long result128;
    for(int x=1;x<256;x++){
      int y=256-x;
      int p=n;
      int level=1;
      long long len=0;
      while(p>=0){
        long long cnt=0;
        for(int t=0;t<y && p--;t++)
          cnt+=ppb[p];
        len+=cnt*level;
        level++;
        y*=x;
      }
      if(x==128){
        result128=len;
      }
      if(len<best){
        best=len;
        how=x;
      }
    }
    cout << "Najlepszy x=" << how << " daje: " << best << "b." << endl;
    cout << "Dla x=128, dostajesz : " << result128 << "b." << endl;
  }
}
