#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
bool exec(const double a,const int k){
  double w[k];
  for(int i=0;i<k;i++)w[i]=0;
  double pref=0;
  for(int t=0;t<100000;t++){
    int i=t%k;
    double b=(a*pref-k*w[i]+(a-1)*k)/(k-a);
    if(b>1e60)return true;
    if(b<=0)
      return false;

    w[i]+=b+1;
    pref+=b;
  }
  return true;
  
}
int main(){
  double f,t,a;
  for(double k=2;k<40;k++){
    f=1;
    t=2;
    while(t-f>0.00001){
      a=0.5*(f+t);
      if( (a-1)*(pow(k/(k-a),k+1)-pow(k/(k-a),2))-k/(k-a) >=1/(a-1)){
        t=a;
      }else
        f=a;
    }
    cout << k << " -> " << f << endl ;
    a=f;
    cout << pow(k/(k-a),k) << " <> " << exp(a) << " <> " << (a-1/3)*exp(4/3) << endl;
    cout << k << " -> " << (a-1)*(pow(k/(k-a),k+1)-pow(k/(k-a),2))-k/(k-a) << " vs. " << 1/(a-1) << endl;
    cout << k << " => " << k/(k-a)*((a-1)*(  pow(k/(k-a),k) -k/(k-a)  )-1) << " vs. " << 1/(a-1) << endl;
    cout << k << " ~> " << k/(k-a)*((a-1)*(  pow(exp(1)+ a/(k-a) ,a)  -k/(k-a)  )-1) << " vs. " << 1/(a-1) << endl;
    cout << k << " :> " << k/(k-a)*((a-1)*(  pow(exp(1)+ a/(k-a)+ a*a/(k*k) ,a)  -k/(k-a)  )-1) << " vs. " << 1/(a-1) << endl;
    f=1;
    t=2;
    while(t-f>0.0001){
      a=0.5*(f+t);
      if( exec(a,k)){
        t=a;
      }else
        f=a;
    }
    cout << k << " = " << f << endl;
  }
  cin >> f;
}
