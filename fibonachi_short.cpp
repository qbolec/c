#include<iostream>
using namespace std;
unsigned long long n,m,a,b=1,c;  
int main(){
  cin>>n>>m;
  for(int i=64;i--;){
    c=(b*(b+2*a))%m;
    a=(a*(b*2+m-a))%m;
    b=(c+m-a)%m;
    if((n>>i)&1){
      c=(a+b)%m;
      a=b;
      b=c;
    }
  }
  cout<<a<<endl;
}
