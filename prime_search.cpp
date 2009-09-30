#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;
template<class Big,class K,class M>
M power(Big x,K k,M m){
  if(!k)return 1;
  M h=power(x,k/2,m);
  h=((Big)h*h)%m;
  return k&1? ((Big)h*x)%m : h;
}
class small_primes{
public:
  static const int range=30;// (1<<16);
  vector<int> primes;
  int divisor[range];
private:
  small_primes(){
    fill_n(divisor,range,0);
    primes.clear();
    divisor[0]=divisor[1]=-1;
    for(unsigned int i=2;i< range;i++)
      if(!divisor[i]){
        primes.push_back(i);
        for(unsigned int j=i*i;j< range;j+=i)
          divisor[j]=i;
      }
  }
public:
  static small_primes instance;
};
small_primes small_primes::instance=small_primes();

template<class Big,class X>
bool pass_RM_test(int r,X s,X x,X a){
  X a_to_s=power<Big>(a,s,x);
  if(a_to_s==1)return true;
  X a_to_s_to_2_to_j=a_to_s;
  for(int j=0;j<r;j++){
    if(a_to_s_to_2_to_j==x-1)
      return true;
    else
      a_to_s_to_2_to_j=((Big)a_to_s_to_2_to_j*a_to_s_to_2_to_j)%x;
  }
  return false;
}

template<class X>
bool is_prime(X x){
  if(x<small_primes::instance.range)
    return !small_primes::instance.divisor[x];
  X rzad=x-1;
  X s=rzad;
  int r=0;
  while(!(s%2)){
    s/=2;
    r++;
  }
  for(int i=0;i<10;i++)
    if(!pass_RM_test<long long>(r,s,x,small_primes::instance.primes[i])){
      return false;
    }
  return true;
}
template<class X>
bool is_prime_naive(X x){
  if(x<2)
    return false;
  for(int i=2;(X)i*i<=x;i++)
    if(x%i==0)
      return false;
  return true;
}

template<int F>
class bignum{
  typedef bignum<F-1> S;
  typedef bignum<F> B;
  S high,low;
  bool add(B & other){
    bool overflow=false;
    if(low.add(other.low))
      overflow=high.inc();
    return high.add(other.high)||overflow;
  }
  bool inc(){
    return low.inc()&&high.inc();
  }
};
template<>class bignum<0>{
  typedef bignum<0> B;
  unsigned int dane;
  bool add(B & other){
    unsigned int dane2=dane;
    dane+=other.dane;
    return (dane<dane2);
  }
  bool inc(){
    dane++;
    return !dane;
  }
};

int main(){
  for(int i=0;i<30;i++)
    if(is_prime(1+(1<<i)))
      cout << "dziala dla i=" << i << endl;
  for(int a=0;a<13;a++){
    int cnt=0;
    for(int b=0;b<12;b++){
      unsigned int p_1=1;
      for(int i=a;i--;)p_1*=2;
      for(int i=b;i--;)p_1*=3;
      unsigned int p=p_1+1;
      bool is_prime=false;
      for(int i=0;1<<i/3 < p;i++){//log n prob
        unsigned int g=rand()%p;
        if(power(g,p_1,p)==1 && (!a||power(g,p_1/2,p)!=1) && (!b||power(g,p_1/3,p)!=1)){
          cout << "Dla p=" << p << " zgadlem generator " << g << endl;
          is_prime=true;
          break;
        }
      }
      if(!is_prime){
   //     cout << "Nie udalo sie dowiesc, ze p=" << p << " jest pierwsza" << endl;
      }else
        cnt++;
    }
    cout << "Gdy a=" << a << " znaleziono " << cnt << " liczb pierwszych" << endl;
  }
  system("PAUSE");
  return 0;
}

