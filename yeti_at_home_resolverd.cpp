#include<cmath>
#include<cstdio>
#include<iostream>
using namespace std;
const int T=1000000;
long double beta[T];
int main(){
  double x=1.3;
  double y=1.6;
  while(x+0.00001<y){
    const long double a=(x+y)/2;
    for(int k=4;k<1000;k++){
      const long double f=k/(k-a);
      for(int t=0;t<k;t++){
        beta[t]=(a-1)*pow(f,t+1);
//        cout << "beta[" << t << "]=" << beta[t]<<endl;
      }
      beta[k]=  f*  ( (a-1) *(pow(f,k)-f ) -1 );
//      cout << "beta[" << k << "]=" << beta[k]<<endl;
      for(int t=k+1;t<T;t++){
        beta[t]=beta[t-1]+ a*(beta[t-1]-beta[t-k])/(k-a);
//        cout << "beta[" << t << "]=" << beta[t]<<endl;
        if(beta[t]<0.0001){
          cout << "bad " << a << " for k=" <<k << " t=" << t << " beta=" << beta[t] << endl;
          goto bad_alfa;
        }else if(beta[t]>1000000){
          cout << "seems good" << a << " for k=" <<k << " t=" << t << " beta=" << beta[t] << endl;
//          system("PAUSE");
          break;
        }
      }
    }
    y=a;
    cout << "good " << a << endl;
    continue;
bad_alfa:
    x=a;
  }
  cout << "x=" << x << endl;
  system("PAUSE");
}
