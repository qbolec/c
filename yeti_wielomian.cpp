#include<cmath>
#include<cstdio>
#include<iostream>
//#define SUM
using namespace std;
const int T=1000000;
long double beta[T];
const int K=6000;
long double done[K];
bool check(const long double a,const int k){
  for(int t=0;t<k;t++)
    done[t]=0;
  long double progress=0;
  int u=0;
  for(int t=0;t<T;t++){
#ifdef SUM
    //sum
    beta[t]=(progress*a-k*(1.0+done[u]-a))/(k-a);
//      cout << "k=" << k << " t="  << t << " u=" << u << " b="  << beta[t] << " p=" << progress << endl;
/*
    double b;
    if(t>=k){
      b=0;
      for(int i=t-k+1;i<t;i++)
        b+=beta[i];
      b=(b*a-k)/(k-a);
    }else{
      b=(a-1)*pow(k/(k-a),t+1);
    }
    if(fabs(beta[t]-b)>0.000001){
      cout << b << " vs. " << beta[t] << endl;
    }
*/
#else
    //max
    beta[t]=((progress*a-k*(1+done[u]))/(k-a))>?(a-(1+done[u]));
#endif
    if(beta[t]<0.00001){
//          cout << "bad " << a << " for k="<<k << " t=" << t << " beta=" << beta[t]<<   endl;
//          system("PAUSE");
      return false;
    }else if(beta[t]>1000000){//          cout << "seems good " << a << " for k="<<k << " t=" << t <<   endl;
      return true;
    }
    done[u]+=beta[t]+1;
    progress+=beta[t];
    const long double opt= 1+progress/k;
//        assert(fabs(opt*a-done[u])<0.0000001);
    if(k==++u)u=0;
  }
  return true;
}
bool rok(int k,double a, double r){
  return (r-k/(k-a))*pow(r,k-1)+a/(k-a)>0;
}
double guessr(int k,double a){
  //zgadujemy r
  double f=(k-1.0)/(k-a);
  double t=k/(k-a);
  while(f+0.0000001<t){
    double r=(f+t)*0.5;
    if(rok(k,a,r)){
      t=r;
    }else
      f=r;
  }
  return (f+t)*0.5;
}
bool alfaok(int k, double a){
  double r=guessr(k,a);
  int s= (int)ceil(k/(a-1));
  double b= ((s-1)*(a-1)*a/(k-a) - k/(k-a))*pow(k/(k-a),k-s);
  if(b<a)
    return false;
  return 0<=r*((s-1)*(a-1)-k+a-1)-(s-1)*(a-1)+k - a*pow(r,s-k);
}
double guess(int k){
  //zgadujemy a
  double f=2;
  double t=3;
  while(f+0.0000001<t){
    double a=(f+t)*0.5;
    if(alfaok(k,a)){
      t=a;
    }else
      f=a;
  }
  return (f+t)*0.5;
}
int main(){
#ifdef SUM
  puts("SUM");
#else
  puts("MAX");
#endif
  for(int k=2;k<K;k++){
#ifdef SYMULATE
    double x=1;
    double y=3;
    while(x+0.000001<y){
      const long double a=(x+y)/2;
      if(check(a,k)){
        y=a;
//      cout << "good " << a << endl;
      }else{
        x=a;
      }
    }
    cout << "for k= " << k <<" alpha= " << x << endl;
#endif
    cout << "for k= " << k << " should be " << guess(k) << endl;
//    cout << "beta_k= " << beta[k] << " while 1/(alpha-1)=" << 1.0/(x-1) << endl;
/*
    check(x,k);

    for(int r=0;r<2*k;r++){
      for(int i=r*k;i<r*k+k;i++)
        cout << "beta[" << i <<"]=" << beta[i] << endl;
      cout << endl;
    }
*/
  }
  system("PAUSE");
}
