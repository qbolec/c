#include<iostream>
typedef unsigned int uint;
typedef unsigned long long ll;
uint m;//modulo
uint fib(ll n){
  uint f0=0,f1=1,f2;  
  for(int b=64;b--;){
    f2= ((ll)f1*(f1+2*f0))%m;
    f0= ((ll)f0*(f1*2+m-f0))%m;
    f1=(f2+m-f0)%m;
    if((n>>b)&1){
      f2=(f0+f1)%m;
      f0=f1;
      f1=f2;
    }
  }
  return f0;
}
using namespace std;
int main(){
  ll n;
  cin >> n >> m;
  cout << fib(n) << endl;
}
