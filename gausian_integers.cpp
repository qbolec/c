#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<utility>
#include<cmath>
using namespace std;
const int N=100000001;
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
  if(b==p.size()){
    tmp.push_back(x);
    return;
  }
  int t=1;
  for(int i=k[b];i>=0;i--){
    go(b+1,x*t);
    t*=p[b];
  }
}
vector<int> divisors(int x){
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
  tmp.clear();
  go();
  return tmp;
}
int main(){
  s=new int[N];
  s[0]=0;
  s[1]=1;
  issq.resize(N,false);
  for(int i=1;i*i<N;i++)
    issq[i*i]=true;
  puts("sqdone");
  for(int i=2;i<N;i++){
    if(!s[i]){
//      s[i]=i;
//      printf("%d\n",i);
      pc++;
      for(int j=i;j<N;j+=i){
        s[j]=i;
      }
    }
  }
  puts("field done");
  long long sum=0;
  for(int i=1;i<N;i++)
    sum+= (N-1)/i*i;
  ps=new long long[N];
  ps[0]=0;
  cout << sum << endl;
  for(int m=1;m<N;m++){
    vector<int> md=divisors(m);
    int pss=0;
    for(int k=0;k<md.size();k++)
      pss+=2*md[k];
    ps[m]=ps[m-1]+pss;
  }
  for(int a=1;a*a<N;a++)
  for(int b=1;a*a+b*b<N;b++)if(wp(a,b)){
    int mmin=1;
    int mmax=(N-1)/(a*a+b*b);
    sum+=(long long)(ps[mmax]-ps[mmin-1])*a;
//    for(int m=1;(a*a+b*b)*m<N;m++)
//      sum+=ps[m]*a;
  }

  /*
  for(int x=1;x<N;x++){
    vector<int> divs=divisors(x);
    printf("\r%d: ",x);
    for(int j=0;j<divs.size();j++){
      int i=divs[j];
      sum+=divs[j];
//      printf("%d,",divs[j]);
      int m=x/i;
      vector<int> md=divisors(m);
      int ps=0;
      for(int k=0;k<md.size();k++){
        ps+=2*md[k];
      }
      for(int a=1;a*a<i;a++){
        int a2=a*a;
        int b2=i-a2;
        if(issq[b2]&&wp(b2,a)){
//          for(int k=0;k<md.size();k++){
//            printf("%d + %di , %d - %di,",md[k]*a,md[k]*(int)sqrt(b2),m/md[k]*a,m/md[k]*(int)sqrt(b2));
//            sum += md[k]*a;
//            sum += m/md[k]*a;
            sum+=(long long)ps*a;
//          }
        }
      }
    }
  }
*/
  cout << endl << sum << endl;
  system("PAUSE");
}
//15351393371
//15372428665
//17924657155
