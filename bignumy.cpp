#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<vector>
using namespace std;
template<class T>
bool operator ==(const T & a,const T & b){
  return !memcmp(&a,&b,sizeof(T));
}

template<int F>
struct bignum{
  typedef bignum<F-1> S;
  typedef bignum<F> B;
  typedef bignum<F+1> L;
  static const unsigned int digits;
  S high,low;
/*
  S mul(const S & other){
    S rest=low.mul(other);
    S rest2=high.mul(other);
    if(high.add(rest))
      if(rest2.inc())
        throw 1;
    return rest2;
  }
  B mul(const B & other){
    B my_copy=*this;
    S rest=mul(other.low);
    S rest2=my_copy.mul(other.high);
    if(high.add(my_copy.low))
      if(my_copy.high.inc())
        if(rest2.inc())
          throw 2;
    B rest3(rest2,my_copy.high);   1:42 7 znakow
    if(rest3.add(rest))
      throw 3;
    return rest3;
  }
*/
  bool operator < (const B & other)const{
    return high==other.high&&low<other.low|| high<other.high;
  }
  unsigned int small_mul(unsigned int x,unsigned int r=0){
    return high.small_mul(x,low.small_mul(x,r));
  }
  unsigned int small_div(unsigned int x,unsigned int r=0){
    return low.small_div(x,high.small_div(x,r));
  }
  unsigned int small_mod(unsigned int x,unsigned int r=0)const{
    return low.small_mod(x,high.small_mod(x,r));
  }
/*
  S operator % (const S & other){
    if(!other)
      4%(bool)other;
    B result=*this;
    vector<B*> shifted;
    shifted.push_back(new B(0,other));
    while(!(result<*shifted.back())){
      shifted.push_back(new B(*shifted.back()));
      if(shifted.back()->add(*shifted[shifted.size()-2]))
        break;
    }
    delete shifted.back();
    shifted.pop_back();
    while(!shifted.empty()){
      if(!(result<*shifted.back())){
        result.subtract(*shifted.back());
      }
      delete shifted.back();
      shifted.pop_back();
    }
    if(result.high)
      throw 8;
    return result.low;
  }
*/

  S operator % (const S & other){
    if(!other)
      4%(bool)other;
    B result=*this;
    vector<B*> shifted;
    shifted.push_back(new B(0,other));
    while(!(result<*shifted.back())){
      shifted.push_back(new B(*shifted.back()));
      if(shifted.back()->add(*shifted[shifted.size()-2]))
        break;
    }
    delete shifted.back();
    shifted.pop_back();
    while(!shifted.empty()){
      if(!(result<*shifted.back())){
        result.subtract(*shifted.back());
      }
      delete shifted.back();
      shifted.pop_back();
    }
    if(result.high)
      throw 8;
    return result.low;
  }

  L operator * (const B & other){
    if(!other || !*this)
      return L(0);
    S a_plus_b(low);
    bool a_plus_b_rest=a_plus_b.add(high);
    S c_plus_d(other.low);
    bool c_plus_d_rest=c_plus_d.add(other.high);
    L result(high*other.high,low*other.low);

    B ad_plus_bc=a_plus_b*c_plus_d;
    int ad_plus_bc_rest=a_plus_b_rest&&c_plus_d_rest;
    if(a_plus_b_rest)
      if(ad_plus_bc.high.add(c_plus_d))
        ad_plus_bc_rest++;
    if(c_plus_d_rest)
      if(ad_plus_bc.high.add(a_plus_b))
        ad_plus_bc_rest++;
    if(ad_plus_bc.subtract(result.low))
      ad_plus_bc_rest--;
    if(ad_plus_bc.subtract(result.high))
      ad_plus_bc_rest--;
    if(ad_plus_bc_rest<0)
      throw 4;
    
    if(result.low.high.add(ad_plus_bc.low))
      result.high.inc();
    if(result.high.low.add(ad_plus_bc.high))
      result.high.high.inc();
    while(ad_plus_bc_rest--)
      result.high.high.inc();
    return result;
  }
  bool add(const S & other){
    return low.add(other)&&high.inc();
  }
  bool add(const B & other){
    bool overflow=false;
    if(low.add(other.low))
      overflow=high.inc();//dodawanie w n^2 ? pogratulowac.
    return high.add(other.high)||overflow;
  }
  bool subtract(const B & other){
    bool overflow=false;
    if(low.subtract(other.low))
      overflow=high.dec();
    return high.subtract(other.high)||overflow;
  }
  bool inc(){
    return low.inc()&&high.inc();
  }
  bool dec(){
    return low.dec()&&high.dec();
  }
  operator bool() const{
    return low||high;
  }
  bignum<F>(unsigned int x=0):high(0),low(x){}
  bignum<F>(const S & high,const S & low):high(high),low(low){}
  bignum<F>(string t){
    if(t.length()>digits)
      throw 7;
    if(t.length()>S::digits){
      high=t.substr(0,t.length()-S::digits);
      low=t.substr(t.length()-S::digits);
    }else{
      high=0;
      low=t;
    }
  }
};
template<> struct bignum<0>{
  typedef bignum<0> B;
  typedef bignum<1> L;
  unsigned int dane;
  static const unsigned int digits;
  static const unsigned int maxvalue;
  /*
  B mul(const B & other){
    unsigned long long m=(unsigned long long)dane*other.dane;
    dane=m%maxvalue;
    return B(m/maxvalue);
  }
  */
  bool operator < (const B & other)const{
    return dane<other.dane;
  }
  unsigned int small_mul(unsigned int x,unsigned int r=0){
    unsigned long long m=(unsigned long long)dane*x+r;
    dane=m%maxvalue;
    return m/maxvalue;
  }
  unsigned int small_div(unsigned int x,unsigned int r=0){
    unsigned long long m=(unsigned long long)r*maxvalue + dane;
    dane=m/x;
    return m%x;
  }
  unsigned int small_mod(unsigned int x,unsigned int r=0)const{
    unsigned long long m=(unsigned long long)r*maxvalue + dane;
    return m%x;
  }

  B & operator %= (const B & other){
    dane%=other.dane;
    return *this;
  }
  L operator * (const B & other){
    unsigned long long m=(unsigned long long)dane*other.dane;
    return L(B(m/maxvalue),B(m%maxvalue));
  }
  bool add(const B & other){
    if(other.dane>=maxvalue-dane){
      dane=other.dane-(maxvalue-dane);
      return true;
    }else{
      dane+=other.dane;
      return false;
    }
  }
  bool subtract(const B & other){
    if(other.dane>dane){
      dane+=maxvalue-other.dane;
      return true;
    }else{
      dane-=other.dane;
      return false;
    }
  }
  bool inc(){
    dane++;
    if(dane==maxvalue){
      dane=0;
      return true;
    }else
      return false;
  }
  bool dec(){
    if(!dane){
      dane=maxvalue-1;
      return true;
    }else{
      --dane;
      return false;
    }
  }
  operator bool()const{
    return dane;
  }
  bignum<0>(unsigned int x=0):dane(x){}
  bignum<0>(string t){
    if(t.length()>digits)
      throw 6;
    dane=0;
    for(int i=0;i<t.length();i++)
      dane=dane*10+t[i]-'0';
  }
};
template<int F> const unsigned int bignum<F>::digits=bignum<F-1>::digits*2;
const unsigned int bignum<0>::digits=9;
const unsigned int bignum<0>::maxvalue=1000000000;

ostream& withzeros (ostream& sout, const bignum<0> & b ){
  return sout<< setfill('0') << setw(b.digits) << b.dane;
}
template<int F>
ostream& withzeros (ostream& sout, const bignum<F> & b ){
  return withzeros(withzeros(sout,b.high),b.low);
}


ostream& operator << (ostream& sout, const bignum<0> & b ){
  return sout<< b.dane;
}
template<int F>
ostream& operator << (ostream& sout, const bignum<F> & b ){
  if(b.high)
    return withzeros(sout << b.high,b.low);
  return sout<< b.low;
}

template<int F>
istream& operator >> (istream& sin, bignum<F> & b ){
  string text;
  sin >> text;
  b=text;
  return sin;
}

template<class B,class C>
B power_mod(B x, C k,const B & m){
  B result=1;
  while(k){
    if(k.small_div(2))
      result=(result*x)%m;
    x=(x*x)%m;
  }
  return result;
}
typedef bignum<6> Bignum;

class small_primes{
public:
  static const int range= (1<<22);
  vector<unsigned int> primes;
  int divisor[range];
private:
  small_primes(){
    fill_n(divisor,range,0);
    primes.clear();
    divisor[0]=divisor[1]=-1;
    for(unsigned int i=2;i< range;i++)
      if(!divisor[i]){
        primes.push_back(i);
        if(i<range/i)
        for(unsigned int j=i*i;j< range;j+=i)
          divisor[j]=i;
      }
  }
public:
  static small_primes instance;
};
small_primes small_primes::instance=small_primes();

bool sprawdz(int a,int b){
  Bignum dwa_do_a=1;
  for(int i=0;i<a;i++)
    dwa_do_a.small_mul(2);
  Bignum trzy_do_b=1;
  for(int i=0;i<b;i++)
    trzy_do_b.small_mul(3);

  Bignum p=(trzy_do_b*dwa_do_a).low;

  Bignum log_minus_1=p;
  log_minus_1.small_div(2);

  Bignum minus_1=p;
  

  p.inc();
  for(int i=0;i<small_primes::instance.primes.size();i++){
    unsigned int d=small_primes::instance.primes[i];
    if(p.small_mod(d)==0){
      cout << "dzieli sie przez " << d << endl;
      return false;
    }
  }
  cout << p<<"przez nic malego sie nie dzieli, szukam generatora" << endl;
  for(int i=0;i<20;i++){//2*3 prob
    cout << '?' << flush;
    Bignum g=rand();
    if(power_mod(g,log_minus_1,p)==minus_1){
      Bignum k=p;
      k.dec();
      k.small_div(3);
      if(!b||!(power_mod(g,k,p)==Bignum(1))){
        cout << "Dla p=" << p <<  " zgadlem generator " << g << endl;
        return true;;
      }
    }
  }
  return false;
}

int main(){
  if(sprawdz(103,72))
    system("PAUSE");
  try{
    while(true){
      int a,b;
      a=500+rand()%60;
      b=500+rand()%60;
      //cin >> a >> b;
      if(sprawdz(a,b)){
        cout << "2^" << a << "*3^" << b << "+1 jest liczba pierwsza!:D" << endl;
      }else
        cout << '.';
    }
  }catch(int x){
    cout << "Error:" << x << endl;
  }
  system("PAUSE");
}
