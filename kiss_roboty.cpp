#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
const int k=4;
double a=2.4988;
double work[k];
double opt;
double eb_[1000000];
double eb(int t){
  if(eb_[t])
    return eb_[t];
  if(t<k)
    return eb_[t]=2*(a-1);
  if(t<2*k)
    return eb_[t]=(2*(a-1)*(a-1)-4)*pow((1+a/k),t-k);
  if(t==2*k)
    return eb_[t]=(2*(a-1)*(a-1)-4)*(pow((1+a/k),k)-1)-2;
  return eb_[t]=eb(t-1)*(1+a/k)-a/k*eb(t-1-k);
}
bool check(double af){
  memset(eb_,0,sizeof(eb_));
  a=af;
  for(int i=0;i<1000;i++)
    if(eb(i)<0)
      return false;
  return true;
}
int main(){
  double f=2;
  double t=3;
  while(t-f>0.001){
    double c=(t+f)*0.5;
    if(check(c)){
      t=c;
    }else{
      f=c;
    }
  }
  cout << f << endl;

  for(int r=0;r<10;r++){
    for(int i=0;i<k;i++){
      double opt_min=r?opt:2;
      double beta= a*opt_min - work[i] - 2;
      
      int t=r*k+i;
      double e=eb(t);
//      if(abs(e-beta)>1e-9){
        cout << "runda " << r << " robot " << i << " beta = " << beta  << endl;
        cout << "expected " << eb(t) << endl;
//      }
      
      work[i]+=beta+2;
      opt+=beta/k;
    }
  }
  system("PAUSE");
}
