#include<iostream>
using namespace std;
  long long id;
  long long m;
struct ma{
  long long a[2][2];
  ma(int x,int y,int z,int w){
    a[0][0]=x;
    a[0][1]=y;
    a[1][0]=z;
    a[1][1]=w;
  }
};
ma mul(ma x,ma y){
  ma r(0,0,0,0);
  for(int i=0;i<2;i++)
  for(int j=0;j<2;j++){
    for(int k=0;k<2;k++){
      r.a[i][j]+=x.a[i][k]*y.a[k][j];
      r.a[i][j]%=m;
    }
  }
  return r;
}
ma pow(ma x,long long k){
  if(k==0)return ma(1,0,0,1);
  if(k==1)return x;
  if(k&1)return mul(pow(x,k-1),x);
  ma y=pow(x,k/2);
  return mul(y,y);
}
long long fib(long long i){
  ma r=pow(ma(1,1,1,0),i);
  return r.a[1][0];
}
int main(){
  cin >> id >> m;
  cout << fib(id)<<endl;
}
