#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#define USE_DIV_TRICK
#define USE_FFT
//#define OLDSKUL
//#define DZIEL_NA_CZTERY
using namespace std;
template<class T>
bool operator ==(const T & a,const T & b){
  return !memcmp(&a,&b,sizeof(T));
}

template<int F>
struct bignum{
  static const unsigned int digits;
  static const unsigned int maxvalue;
  static const unsigned int myF;
  typedef bignum<F> B;
  typedef bignum<F*2> L;
  typedef bignum<F/2> S;
  unsigned int dane[F];
  bool operator < (const B & other)const{
    for(int i=F;i--;)
      if(dane[i]<other.dane[i])
        return true;
      else if(dane[i]>other.dane[i])
        return false;
    return false;
  }
  unsigned int small_mul(const unsigned int x,unsigned int r=0){
    for(int i=0;i<F;i++){
      unsigned long long m=(unsigned long long )dane[i]*x+r;
      if(m>=maxvalue){
        r=m/maxvalue;
        dane[i]=m%maxvalue;
      }else{
        r=0;
        dane[i]=(unsigned int)m;
      }
    }
    return r;
  }
  unsigned int small_div(const unsigned int x,unsigned int r=0){
    for(int i=F;i--;){
      unsigned long long m=(unsigned long long )r*maxvalue+dane[i];
      r=m%x;
      dane[i]=m/x;
    }
    return r;
  }
  unsigned int small_mod(const unsigned int x,unsigned int r=0)const{
    for(int i=F;i--;){
      unsigned long long m=(unsigned long long )r*maxvalue+dane[i];
      r=m%x;
    }
    return r;
  }
#ifndef USE_DIV_TRICK
  S operator % (const S & other)const{
    if(!other)
      4%(bool)other;
    B result=*this;
    vector<B*> shifted;
    shifted.push_back(new B(0U,other));
    while(!(result<*shifted.back())){
      shifted.push_back(new B(*shifted.back()));
      //if(shifted.back()->small_mul(2)){
      if(shifted.back()->add(*shifted[shifted.size()-2])){
        break;
      }
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
    return S(result.dane);
  }
#else
  S operator % (const S & other)const{
    if(!other)
      4%(bool)other;
    unsigned long long header;
    int divisor_head_pos=-1;
    for(int i=F/2;i--;)
      if(other.dane[i]){
        header=other.dane[i];
        header*=maxvalue;
        if(i)
          header+=other.dane[i-1];
        divisor_head_pos=i;
        break;
      }
    unsigned int offset=1;
    while(header<((unsigned long long)maxvalue/10)*maxvalue){
      header*=10;
      offset*=10;
    }
    unsigned int header_digits=(header/maxvalue);//najbardziej znaczace cyferki
    B result=*this;
    for(int i=F;i-->divisor_head_pos;){
      for(int safe=10;safe-- && result.dane[i];){
        unsigned long long B_header=result.dane[i];
        B_header*=maxvalue;
        if(i)
          B_header+=result.dane[i-1];
        unsigned int B_offset=1;
        while(B_header<((unsigned long long)maxvalue/10)*maxvalue){
          B_header*=10;
          B_offset*=10;
        }
        unsigned int B_header_digits=(B_header/maxvalue);//najbardziej znaczace cyferki
        int shift=i-divisor_head_pos;
#ifdef OLDSKUL
        long double f=B_header_digits;
        long double g=header_digits;
        long double r=f/(g+1.0);
#endif
        unsigned int my_offset=offset;
        while(my_offset>1 && B_offset>1){
          my_offset/=10;
          B_offset/=10;
        }
        if(B_offset>1){
          if(shift){
            shift--;
            my_offset=maxvalue/B_offset;
            B_offset=1;
          }else{
            break;
          }
        }
        B tmp;
        if(shift){
          if(my_offset!=maxvalue/10){
            tmp.add_shifted(other,shift-1);
            tmp.small_mul(my_offset*10);
          }else
            tmp.add_shifted(other,shift);
#ifdef OLDSKUL
          tmp.small_mul((unsigned int)(r*(maxvalue/10)));
#else
          tmp.small_mul((unsigned int)((unsigned long long)B_header_digits*(maxvalue/10)/(1+header_digits)));
#endif
        }else{
          tmp.add_shifted(other,0);
#ifdef OLDSKUL
          tmp.small_mul((unsigned int)(r*my_offset));
#else
          tmp.small_mul((unsigned int)((unsigned long long)B_header_digits*my_offset/(1+header_digits)));
#endif
        }
        if(!(result<tmp)){
          result.subtract(tmp);
          if(!result.dane[i])
            break;
        }else{
          throw 123;
        }
      }
    }
    B m(0U,other);
    while(!(result<m)){
      result.subtract(m);
    }
    return S(result.dane);
  }
#endif
  L operator * (const B & other)const;
  template<int other_size>
  bool add_shifted(const bignum<other_size> & other,const int shift){
    int overflow=false;
    if(other_size+shift>F){
      for(int i=F-shift;i<other_size;i++)
        if(other.dane[i])
          throw 13;
    }
    int limit=other_size <? F-shift;
    for(int i=0;i<limit;i++){
      if(maxvalue-1-dane[i+shift]<other.dane[i]||overflow&&(maxvalue-1-dane[i+shift]==other.dane[i])){
        dane[i+shift]-=(maxvalue-other.dane[i])-overflow;
        overflow=true;
      }else{
        dane[i+shift]+=other.dane[i]+overflow;
        overflow=false;
      }
    }
    if(overflow&&limit+shift<F)
      return inc(limit+shift);
    return overflow;
  }
  bool small_add_shifted(const int shift, unsigned int other){
    if(shift>=F)
      throw 912;
    if(maxvalue-1-dane[shift]<other){
      dane[shift]-=(maxvalue-other);
      return inc(shift+1);
    }else{
      dane[shift]+=other;
      return false;
    }
  }

  bool add(const B & other){
    int overflow=false;
    for(int i=0;i<F;i++){
      if(maxvalue-1-dane[i]<other.dane[i]||overflow&&(maxvalue-1-dane[i]==other.dane[i])){
        dane[i]-=(maxvalue-other.dane[i])-overflow;
        overflow=true;
      }else{
        dane[i]+=other.dane[i]+overflow;
        overflow=false;
      }
   //   if(dane[i]>=maxvalue)
   //     throw (int)dane[i];
    }
    return overflow;
  }
  template<int other_size>
  bool subtract_shifted(const bignum<other_size>  & other,const int shift){
    int overflow=false;
    if(other_size+shift>F){
      for(int i=F-shift;i<other_size;i++)
        if(other.dane[i])
          throw 13;
    }
    int limit=other_size <? F-shift;
    for(int i=0;i<limit;i++){
      if(dane[i+shift]<other.dane[i] || overflow&&(dane[i+shift]==other.dane[i])){
        dane[i+shift]+=maxvalue-other.dane[i]-overflow;
        overflow=true;
      }else{
        dane[i+shift]-=other.dane[i]+overflow;
        overflow=false;
      }
      if(dane[i+shift]>=maxvalue)
        throw (int)dane[i+shift];
    }
    if(overflow&&limit+shift<F)
      return dec(limit+shift);
    return overflow;
  }
  bool subtract(const B & other){
    int overflow=false;
    for(int i=0;i<F;i++){
      if(dane[i]<other.dane[i] || overflow&&(dane[i]==other.dane[i])){
        dane[i]+=maxvalue-other.dane[i]-overflow;
        overflow=true;
      }else{
        dane[i]-=other.dane[i]+overflow;
        overflow=false;
      }
      if(dane[i]>=maxvalue)
        throw (int)dane[i];
    }
    return overflow;
  }
  bool small_subtract_shifted(const int shift, unsigned int other){
    if(shift>=F)
      throw 911;
    if(dane[shift]<other){
      dane[shift]+=maxvalue-other;
      return dec(shift+1);
    }else{
      dane[shift]-=other;
      return false;
    }
  }
  
  bool inc(int at=0){
    for(int i=at;i<F;i++){
      if(dane[i]==maxvalue-1)
        dane[i]=0;
      else{
        dane[i]++;
        return false;
      }
    }
    return true;
  }
  bool dec(int at=0){
    for(int i=at;i<F;i++)
      if(dane[i]){
        dane[i]--;
        return false;
      }else
        dane[i]=maxvalue-1;
    return true;
  }
  operator bool() const{
    for(int i=0;i<F;i++)
      if(dane[i])
        return true;
    return false;
  }
  bignum<F>(const bignum<F/2> &high,const bignum<F/2> &low){
    memcpy(dane,low.dane,F/2*sizeof(unsigned int));
    memcpy(dane+F/2,high.dane,F/2*sizeof(unsigned int));
  }
  bignum<F>(const unsigned int * x){
    memcpy(dane,x,F*sizeof(unsigned int));
  }
  bignum<F>(unsigned int x=0){
    fill_n(dane,F,0);
    for(int i=0;x;i++){
      dane[i]=x%maxvalue;
      x/=maxvalue;
    }
  }
  bignum<F>(string t){
    if(t.length()>F*digits)
      throw 7;
    fill_n(dane,F,0);
    unsigned int pow10[10]={1};
    for(int i=1;i<10;i++)
      pow10[i]=pow10[i-1]*10;
    for(int i=t.length();i--;){
      int d=t[i]-'0';
      int p=(t.length()-1-i)/digits;
      dane[p]+=d*pow10[(t.length()-1-i)%digits];
    }
  }
};
template<int F> 
const unsigned int bignum<F>::digits=9;
template<int F>
const unsigned int bignum<F>::maxvalue=1000000000;
template<int F>
const unsigned int bignum<F>::myF=F;

#ifdef DZIEL_NA_CZTERY

template<int F>
class bignum_ex{
public:
  bignum<F> v;
  int x;
  void operator+= (const bignum_ex<F> & other){
    if(v.add(other.v))
      x++;
    x+=other.x;
  }

  void operator-= (const bignum_ex<F> & other){
    if(v.subtract(other.v))
      x--;
    x-=other.x;
  }
  void operator*=(const unsigned int n){
    if(n==1)return;
    if(n==0){
      v=0U;
      x=0;
      return;
    }
    unsigned int r=v.small_mul(n);
    if(((1<<30)-r)/n<abs(x))
      throw 88;
    x=x*(int)n+(int)r;
  }
  void operator/=(const unsigned int n){
    if(x>=0){
      if(v.small_div(n,x%n))
        throw 887;
      x/=(int)n;
    }else{
      if(x%(int)n){
        if(v.small_div(n,(int)n+(x%(int)n)))
          throw 888;
        x/=(int)n;
        x--;
      }else{
        if(v.small_div(n))
          throw 889;
        x/=(int)n;
      }
    }
  }
  bignum_ex<F*2> operator * (const bignum_ex<F> & other)const{
    bignum_ex<F*2> ab(v*other.v,x*other.x);
    
    if(x){
      bignum_ex<F> b=other.v;
      b*=(unsigned int)abs(x);
      if(x>0){
        if(ab.v.add_shifted(b.v,F))
          ab.x++;
        ab.x+=b.x;
      }else{
        if(ab.v.subtract_shifted(b.v,F))
          ab.x--;
        ab.x-=b.x;
      }
    }
    if(other.x){
      bignum_ex<F> a=this->v;
      a*=(unsigned int)abs(other.x);
      if(other.x>0){
        if(ab.v.add_shifted(a.v,F))
          ab.x++;
        ab.x+=a.x;
      }else{
        if(ab.v.subtract_shifted(a.v,F))
          ab.x--;
        ab.x-=a.x;
      }
    }

    return ab;
  }
  bignum_ex<F>(const bignum<F> & other, int x=0):v(other),x(x){  }
};
template<int F>
ostream & operator << (ostream & sout,const bignum_ex<F> &b){
  return sout << "x=" << b.x << " v=" << b.v ;
}

template<int F>
void add_shifted(bignum<F*4> & result,const bignum_ex<F> & n,unsigned int shift){
  if(result.add_shifted(n.v,shift))
    throw 4545;
  if(n.x>0){
    if(result.small_add_shifted(shift+F,n.x))
      throw 4546;
  }else if(n.x<0){
    if(result.small_subtract_shifted(shift+F,-n.x))
      throw 4547;
  }
}
//podzial na cztery:
template<int F>
bignum<F*2> bignum<F>::operator * (const bignum<F> & other)const{
  if(!other || !*this)
    return 0U;
  typedef bignum<F/4> Q;
  typedef bignum_ex<F/4> Q_ex;
  typedef bignum_ex<F/2> S_ex;
  Q a(dane);
  Q b(dane+F/4);
  Q c(dane+F/2);
  Q d(dane+F*3/4);

  Q A(other.dane);
  Q B(other.dane+F/4);
  Q C(other.dane+F/2);
  Q D(other.dane+F*3/4);

#include "szm.h"


  L result(0U);
  ::add_shifted(result,col0,0);
  ::add_shifted(result,col1,F/4);
  ::add_shifted(result,col2,F/2);
  ::add_shifted(result,col3,F*3/4);
  ::add_shifted(result,col4,F);
  ::add_shifted(result,col5,F*5/4);
  ::add_shifted(result,col6,F*3/2);
  
  return result;
}


template<>
bignum<2> bignum<1>::operator * (const bignum<1> & other)const{
  unsigned long long m=(unsigned long long)dane[0]*other.dane[0];
  unsigned int m2[2]={m%maxvalue,m/maxvalue};
  return L(m2);
}


//podzial na pol:
template<>
bignum<2*2> bignum<2>::operator * (const bignum<2> & other)const{
  if(!other || !*this)
    return 0U;
  S my_low(dane);
  S my_high(dane+2/2);
  S other_low(other.dane);
  S other_high(other.dane+2/2);

  S a_plus_b(my_low);
  bool a_plus_b_rest=a_plus_b.add(my_high);
  S c_plus_d(other_low);
  bool c_plus_d_rest=c_plus_d.add(other_high);
  B ac=my_high*other_high;
  B bd=my_low*other_low;
  L result(ac,bd);

  B ad_plus_bc=a_plus_b*c_plus_d;
  int ad_plus_bc_rest=a_plus_b_rest&&c_plus_d_rest;
  if(a_plus_b_rest)
    if(ad_plus_bc.add_shifted(c_plus_d,2/2))
      ad_plus_bc_rest++;
  if(c_plus_d_rest)
    if(ad_plus_bc.add_shifted(a_plus_b,2/2))
      ad_plus_bc_rest++;
  if(ad_plus_bc.subtract(bd))
    ad_plus_bc_rest--;
  if(ad_plus_bc.subtract(ac))
    ad_plus_bc_rest--;
  if(ad_plus_bc_rest<0){
    cout << "ehm:" <<a_plus_b_rest << " und " << c_plus_d_rest << endl;
    throw 4;
  }
  result.add_shifted(ad_plus_bc,2/2);
  while(ad_plus_bc_rest--)
    result.inc(2+2/2);
  return result;
}
#else
#ifdef USE_FFT
namespace FFT{//FFT{begin}
const unsigned int BASE_PRIME=1811939329U;// 2^25 * 27 +1
const unsigned int GENERATOR=25547U;
const unsigned int GROUP_SIZE=BASE_PRIME-1;

struct Element{
  unsigned int x;
  static int gcd_ex(int x,int p,int a,int b){
    if(!x) return b;
    int r=p/x;
    return gcd_ex(p%x,x,b-a*r,a);
  }
  static Element inv( int x){
     if(x&(x-1))
       throw 1024;
     if(x>=BASE_PRIME)
       throw 7292;
     int z= gcd_ex(x,BASE_PRIME,1,0)%(int)BASE_PRIME;
     return Element(z>=0?z:(z+BASE_PRIME));
  }
	Element(unsigned int re=0):x(re){
    if(re>=BASE_PRIME){
      cout << "jakis=" << re << endl;
      throw 7293;
    }
  }
	Element operator *(const Element & b)const{
		return Element((unsigned long long)b.x*x%BASE_PRIME);
	}
	Element operator +(const Element &b)const{
    unsigned int f=x+b.x;
    if(f>=BASE_PRIME)f-=BASE_PRIME;
		return Element(f);
	}
	void operator +=(const Element &b){
    x+=b.x;
    if(x>=BASE_PRIME)
      x-=BASE_PRIME;
  }
	Element operator -(const Element &b)const{
    if(x<b.x){
      return Element(x+(BASE_PRIME-b.x));
    }else{
      return Element(x-b.x);
    }
	}
	static unsigned int powerup(int k,unsigned int x){
    unsigned int result=1;
    while(k){
//      cout << "x=" << x << "k=" << k << endl;
      if(k%2)
        result=((unsigned long long)result*x)%BASE_PRIME;
      k/=2;
      x=((unsigned long long)x*x)%BASE_PRIME;
    }
    return result;
  }
	static Element n_th_root(const unsigned int n){
    if(n>=GROUP_SIZE)
      throw (int)GROUP_SIZE;
    if(GROUP_SIZE%n)
      throw 10000001;
    int k=GROUP_SIZE/n;
    unsigned int x=powerup(k,GENERATOR);
    if(1!=powerup(n,x)){
      cout << "do dupy ten pierwiastek " << x << " dal " << powerup(n,x) << endl;
      throw 63;
    }
    if(GROUP_SIZE!=powerup(n/2,x)){
      cout << "do dupy ten pierwiastek" << endl;
      throw 31;
    }
    return Element(x);
	}
};
int rev(int x,int k){
	int y=0;
	for(int i=0;i<k;i++)
		if(x&(1<<i))
			y|=1<<(k-i-1);
	return y;
}

void fft(const Element *a,const Element * w,const int n,const int k,Element * A,const int * reversed){
	for(int i=0;i<n;i++)
		A[reversed[i]].x=a[i].x;
  int mnc=0;
	for(int s=1;s<=k;s++){//as uncle cormen says
		const int m=1<<s;
		const int d=n/m;
		const int half_m=m/2;
		for(int j=0;j<half_m;j++){
			const Element& omega=w[d*j];
			for(int k=j;k<n;k+=m){
        mnc++;
				const Element t=omega*A[k+half_m];
				const Element u=A[k];
				A[k]+=t;
				A[k+half_m]=u-t;
			}
		}
	}
//	cout << mnc << "mnozen" << endl;
}
void multiply(const Element * a,const Element * b, Element * ab,int n,int k){
  //wyznacz pierwiastki z jedynki
	Element omega[n];
  omega[0]=1;
  omega[1]=Element::n_th_root(n);
  for(int i=2;i<n;i++)
    omega[i]=omega[i-1]*omega[1];
  //przygotuj permutacje
	int reversed[n];
	for(int i=0;i<n;i++)
		reversed[i]=rev(i,k);
  Element A[n];
  Element B[n];
  fft(a,omega,n,k,A,reversed);
  fft(b,omega,n,k,B,reversed);
  for(int i=0;i<n;i++)
		A[i]=A[i]*B[i];
	//Implementacja DFT
	//3.odwracamy pierwiastki
	reverse(omega+1,omega+n);
	//4.obliczamy FFT
	fft(A,omega,n,k,ab,reversed);
  //musimy jeszcze podzielic przez n
 	Element odwrotnosc_n=Element::inv(n);
	if(1!=(unsigned long long)odwrotnosc_n.x*n%BASE_PRIME){
    cout << "n=" << n << " inv=" << odwrotnosc_n.x << endl;
    throw 101;
  }
  for(int i=0;i<n;i++)
    ab[i]=ab[i]*odwrotnosc_n;
}
}//FFT{end}
template<int F>
bignum<F*2> bignum<F>::operator * (const bignum<F> & other)const{
  if(!other || !*this)
    return 0U;
  if(F>FFT::GROUP_SIZE/(1000*1000))
    throw 2048;
  //znajdz odpowiednia potege dwojki
  int minimal=F*3*2+1;
  int k=1;
	int n=2;
	while(n<minimal){//n=2^k >= m
		n<<=1;
		k++;
	}
	
  FFT::Element a[n];
  FFT::Element b[n];
  for(int i=0;i<F;i++){
    unsigned int d=dane[i];
    a[i*3]=d%1000;
    d/=1000;
    a[i*3+1]=d%1000;
    d/=1000;
    a[i*3+2]=d%1000;
  }
  for(int i=0;i<F;i++){
    unsigned int d=other.dane[i];
    b[i*3]=d%1000;
    d/=1000;
    b[i*3+1]=d%1000;
    d/=1000;
    b[i*3+2]=d%1000;
  }
  for(int i=F*3;i<n;i++)
    a[i]=b[i]=0;

  FFT::Element AB[n];
  multiply(a,b,AB,n,k);
  L result(0U);
  unsigned int parts[F*2*3];
  unsigned int rest=0;
  for(int i=0;i<F*2*3;i++){
//    cout << "," <<AB[i];
    rest+=AB[i].x;
    parts[i]=rest%1000;
    rest/=1000;
  }
//  cout << endl;
  for(int i=0;i<F*2;i++)
    result.dane[i]=parts[i*3]+parts[i*3+1]*1000+parts[i*3+2]*1000000;
  return result;
}
#else
template<int F>
bignum<F*2> bignum<F>::operator * (const bignum<F> & other)const{
  if(!other || !*this)
    return 0U;
  S my_low(dane);
  S my_high(dane+F/2);
  S other_low(other.dane);
  S other_high(other.dane+F/2);

  S a_plus_b(my_low);
  bool a_plus_b_rest=a_plus_b.add(my_high);
  S c_plus_d(other_low);
  bool c_plus_d_rest=c_plus_d.add(other_high);
  B ac=my_high*other_high;
  B bd=my_low*other_low;
  L result(ac,bd);

  B ad_plus_bc=a_plus_b*c_plus_d;
  int ad_plus_bc_rest=a_plus_b_rest&&c_plus_d_rest;
  if(a_plus_b_rest)
    if(ad_plus_bc.add_shifted(c_plus_d,F/2))
      ad_plus_bc_rest++;
  if(c_plus_d_rest)
    if(ad_plus_bc.add_shifted(a_plus_b,F/2))
      ad_plus_bc_rest++;
  if(ad_plus_bc.subtract(bd))
    ad_plus_bc_rest--;
  if(ad_plus_bc.subtract(ac))
    ad_plus_bc_rest--;
  if(ad_plus_bc_rest<0){
    cout << "ehm:" <<a_plus_b_rest << " und " << c_plus_d_rest << endl;
    throw 4;
  }
  result.add_shifted(ad_plus_bc,F/2);
  while(ad_plus_bc_rest--)
    result.inc(F+F/2);
  return result;
}
#endif

template<>
bignum<2> bignum<1>::operator * (const bignum<1> & other)const{
  unsigned long long m=(unsigned long long)dane[0]*other.dane[0];
  unsigned int m2[2]={m%maxvalue,m/maxvalue};
  return L(m2);
}


#endif







template<int F>
ostream& operator << (ostream& sout, const bignum<F> & b ){
  int start=0;
  for(int i=F;i--;)
    if(b.dane[i]){
      start=i;
      break;
    }
  sout << b.dane[start] ;
  for(int i=start;i--;)
    sout <<setfill('0') << setw(b.digits) << b.dane[i];
  return sout;
}



template<int F>
istream& operator >> (istream& sin, bignum<F> & b ){
  string text;
  sin >> text;
  b=text;
  return sin;
}
// ???? w 42 sek

template<class B,class C>
B power_mod_classic(B x, C k,const B & m){
  B result=1;
  while(k){
    if(k.small_div(2))
      result=(result*x)%m;
    x=(x*x)%m;
  }
  return result;
}


template<class B,class C>
B power_mod(B x, C k,const B & m){
//  B should_be=power_mod_classic(x,k,m);
  B result=1;
  unsigned int minimal_multiplications=C::myF*30;
  unsigned int best_bits_at_once=1;
//  cout << "regular number of multiplications: " << minimal_multiplications << endl;
  for(int i=2;i<16;i++){
    unsigned int multiplications=(1<<i)-2+(C::myF*30)/i;
    if(multiplications<minimal_multiplications){
      minimal_multiplications=multiplications;
      best_bits_at_once=i;
    }
  }
//  cout << "best number of multiplications: " << minimal_multiplications << " for "<<best_bits_at_once<<" bits" << endl;
  const int bits_at_once=best_bits_at_once;
  B small_powers[1<<bits_at_once];//={1,x};
  small_powers[0]=1;
  small_powers[1]=x;
  for(int i=2;i<(1<<bits_at_once);i++)
    small_powers[i]=(small_powers[i-1]*x)%m;
  vector<unsigned int > rs;
  while(k){
    unsigned int r=k.small_div(1<<bits_at_once);
    rs.push_back(r);
  }
  while(!rs.empty()){
    unsigned int r=rs.back();
    rs.pop_back();
    for(int i=0;i<bits_at_once;i++)
      result=(result*result)%m;
    result= (result*small_powers[r])%m;
  }
/*
  if(!(result==should_be)){
    cout << "result=" << result << endl << "should be=" << should_be << endl;
    throw 42;
  }
*/
  return result;
}


typedef bignum<128> Bignum;

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

  Bignum p((trzy_do_b*dwa_do_a).dane);

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
  unsigned int gens[]={7,5,10,19,11,rand()};
  for(int i=0;i<6;i++){//2*3 prob
    cout << '?' << flush;
    Bignum g=gens[i];
    if(power_mod(g,log_minus_1,p)==minus_1){
      Bignum k=p;
      k.dec();
      k.small_div(3);
      if(!b||!(power_mod(g,k,p)==Bignum(1))){
//        if(p<Bignum(3000000000U))
        cout << "Dla p=" << p <<  " zgadlem generator " << g << endl;
        return true;;
      }
    }
  }
  return false;
}
#define DAWAJ
#ifdef DAWAJ
int main(){
  try{
 
  sprawdz(103,72);
   system("PAUSE");
    while(true){
      int a,b;
      a=1400+rand()%60;
      b=1400+rand()%60;
      //cin >> a >> b;
      if(sprawdz(a,b)){
        cout << "2^" << a << "*3^" << b << "+1 jest liczba pierwsza!:D" << endl;
        system("PAUSE");
      }else
        cout << '.';
    }
  }catch(int x){
    cout << "Error:" << x << endl;
  }
  system("PAUSE");
}
#else
int main(){
  try{
  /*
  for(int a=10;a<32;a++)
    for(int b=0;b<32;b++)
      if(sprawdz(a,b)){
        cout << "2^" << a << "*3^" << b << "+1 jest liczba pierwsza!:D" << endl;
      }
  system("PAUSE");
  */
  int t;
  cin >> t;
  while(t--){
    bignum<1200> a,b;
    cin >> a >> b ;
    cout << a * b << endl;
  }
  return 0;
    }catch(int x){
    cout << "Error:" << x << endl;
  }
  system("PAUSE");
}
#endif
