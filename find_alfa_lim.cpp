#include<cmath>
#include<iostream>
#include<cstdlib>
using namespace std;
int main(){
  for(double g=0.1;g<=2.0;g+=0.1){
  double f=1;
  double t=3;
  while(t>f+0.000001){
    double a=(f+t)*0.5;
    if( (g*a-1)*(exp(a)-1)-1 >= 1.0/(a-1) ){
      t=a;
    }else
      f=a;
  }
    cout << g << " -> " << f << " => " << f*(1+4*g) <<  endl;
  }
  system("PAUSE");
}
