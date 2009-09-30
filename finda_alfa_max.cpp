#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int main(){
  double f,t,a;
  for(double k=2;k<400;k++){
    f=1;
    t=3;
    while(t-f>0.00001){
      a=0.5*(f+t);
      if( (k/(k-a)*(a*(k-1)*(a-1)/k-1)-a)*(pow(k/(k-a),k) -k/(k-a))-k/(k-a) >=1/(a-1)){
        t=a;
      }else
        f=a;
    }
    cout << k << " -> " << f << endl ;
  }
  cin >> f;
}
