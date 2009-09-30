#include<cmath>
#include<iostream>
using namespace std;
int main(){
  for(int n=3;n<=100;n++){
     cout << "n=" << n << endl;
     double s=1.0+exp(-1) ;
     double a=1.0+1.0/n;
     double e=exp(1);
     cout << 1/(1+e-a) << endl;
     double f=0;
     double t=1.0;
     while(t-f>0.0000001){
        double x=(t+f)/2;
        if(e/a+e*x<(e+1)/e *(x*e + (1-x)*e/a)){
          f=x;
        }else{
          t=x;
        }
     }
     cout << f << endl;
  }
  system("PAUSE");
}
