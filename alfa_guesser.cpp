#include<map>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<utility>
#include<cmath>
using namespace std;
const int N=1000000;
int * s;
long long *ps;
int pc;
vector<int> tmp,p,k;
vector<bool> issq;
bool wp(int a,int b){
  if(!b)return a==1;
  return wp(b,a%b);
}
void go(int b=0,int x=1){
  if(b==(int)p.size()){
    tmp.push_back(x);
    return;
  }
  int t=1;
  for(int i=k[b];i>=0;i--){
    go(b+1,x*t);
    t*=p[b];
  }
}
void divisors(int x){
  p.clear();
  k.clear();
  while(x>1){
    int v=s[x];
    if(!p.empty() && p.back()==v){
      k.back()++;
    }else{
      p.push_back(v);
      k.push_back(1);
    }
    x/=v;
  }
  return;
//  tmp.clear();
//  go();
//  return tmp;
}
long long sum;
double in2[81];
double suf[81];
double pre[81];
double beta[1000];
double betaprim[100];
double betawzor[100];
bool check(double alfa,int k){
  beta[1]=(alfa-1.0)*2.0;
  double sm=beta[1];
  for(int r=2;r<100;r++){
/*
1 + (r*2+beta[r]*(k-1)/k)/(beta[1]+...+beta[r-1]+beta[r]/k) = alfa
1 + (r*2+beta[r]*(k-1)/k)/(sm+beta[r]/k) = alfa
(r*2k+beta[r]*(k-1))/(smk+beta[r]) = alfa-1
r*2k+beta[r]*(k-1) = (alfa-1)(smk+beta[r])
r*2k-(alfa-1)smk = beta[r](alfa-1-(k-1))
(r*2k-(alfa-1)smk)/(alfa-1-(k-1)) = beta[r]
beta[r]=(r*2k-(alfa-1)smk)/(alfa-k)
beta[r]=(r*2-(alfa-1)sm)/(alfa/k-1.0)
*/
    beta[r]=(r*2.0-(alfa-1.0)*sm)/(alfa/k-1.0);
    sm+=beta[r];
  }
  cout << "K = " << k <<  endl;
  for(int r=1;r<100;r++){
    cout << "beta_" << r << " = " << beta[r] << endl;
    if(beta[r]<=0)
      return false;

    //sprawdzenie:
    double praca=0;
    for(int i=1;i<=r;i++)
      praca+= 2+beta[i];
    double opt=0;
    for(int i=1;i<r;i++)
      opt+= beta[i];
    opt+=beta[r]/k;

    cout << "alfa_" << r << " = " << praca/opt << endl;
  }
  return true;
}
bool check2(double alfa,int k){
  double opt=beta[1]=(alfa-1)*2;
  for(int r=2;r<100;r++){
    beta[r]=(alfa-1)*opt-2*r;
    opt+=beta[r];
  }

  betaprim[1]=beta[1]-2.0/(alfa-1);
  betaprim[2]=beta[2]-2.0/(alfa-1);
  for(int r=3;r<100;r++)
    betaprim[r]=betaprim[r-1]*alfa;
  for(int r=2;r<100;r++)
    betawzor[r]=2.0*( (alfa-3+1.0/alfa)* pow(alfa,r) +1.0 )/(alfa-1.0);
  for(int r=1;r<50;r++){
    cout << "beta_" << r << " = " << beta[r] << endl;
    if(beta[r]<=0)return false;
    cout << "beta2_" << r << " = " << betaprim[r]+2.0/(alfa-1.0) << endl;
    cout << "beta3_" << r << " = " << betawzor[r]<< endl;

    //sprawdzenie:
    double praca=0;
    for(int i=1;i<=r;i++)
      praca+= 2+beta[i];
    double opt=0;
    for(int i=1;i<r;i++)
      opt+= beta[i];
    cout << "alfa_" << r << " = " << praca/opt << endl;
  }
  return true;
}
bool check3(double alfa,int k){
  cout << endl << " alfa: " << alfa << " k: " << k << endl;
  for(int i=0;i<1000;i++){
    double opt=0;
    for(int j=0;j<i;j++)
      opt+=beta[j];
    opt/=k;
    opt>?=2;

    double me=0;
    for(int j=0;j<i;j++)
      if(j%k==i%k)//miszcz lenistwa
        for(;j<i;j+=k)
          me+=beta[j]+2;

    beta[i]= alfa*opt - me - 2.0;
    if(beta[i]<0)
      return false;
    if(i<100)
    cout << "spacer " << i << " robot: " << i%k << " runda: " << i/k << " beta: " << beta[i] << " opt: " << opt << endl;
  }
  cout << endl << "to bylo alfa: " << alfa << " k: " << k << endl;

  return true;
}
int main(){
  const int k=10;
  double f=2.0;
  double t=3.0;
  while(t-f>0.0000001){
    double alfa=(f+t)*0.5;
    if(check3(alfa,k))
      t=alfa;
    else
      f=alfa;
  }
  check3(t,k);
  system("PAUSE");
//  check2(1.5+sqrt(5)*0.5,k);
//  system("PAUSE");

}
//15351393371
//15372428665
//17924657155
