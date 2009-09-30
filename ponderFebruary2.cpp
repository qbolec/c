//brutforce
//triangles :  (p,q,r) and (a,b,b)
//b'= b/2
//L=p+q+r
//S=p*q/2
//h=sqr(a*a-b*b)
//Range=L+r
//X=a+b'=L/2
//D=a-b'

//#include<math.h>
#include<iostream.h>
//#include<stdlib.h>
#include<conio.h>
#include "primes_7cyfr.h"
typedef long long number;
number gcd(number a,number b){
	if(!b)return a;
	return gcd(b,a%b);
}
number root(number n){
	number x=n;
	while(1){
		number poprawka=(n/x-x)/2;
		if(!poprawka)
			return x;
		x+=poprawka;
	}
}
char pow[bigCNT];
number div[bigCNT];
number b_;
void check(number a,number h){
	if(!h)
		return;
	number L=(b_+a)<<1;
	if(!L)
		return;
	number S=h*b_;
	number r=(L-(S<<2)/L)>>1;
	if(L*(L-(r<<1))!=(S<<2))
		return;
	number suma=L-r;//p+q
	number iloczyn=S<<1;//pq
	number delta=suma*suma-(iloczyn<<2);
	if(delta<=0)
		return;
	number roznica=root(delta);
	if(roznica*roznica!=delta)
		return;
	number p=(roznica+suma)>>1;
	number q=suma-p;
	if(p*q!=iloczyn)
		return;
	if(p*p+q*q!=r*r)
		return;
	number b=b_<<1;
	if(gcd(p,q)==1){
		cout << "Found:" << endl
		<< "p:" << p << "q:" << q << "r:" << r << endl
		<< "a:" << a << "b:" << b << "h:" << h << "b/2:" << b_ << endl
		<< "L:" << L << "S:" << S << endl <<endl;
	}
}
void enumerate(number val,int dc){
	if(!dc){
		number su=val;
		number ro=b_*b_/val;
		if((su^ro)&1)
			return;
		number a=(su+ro)>>1;
		number h=su-a;
		if(!a || !h)
			return;
		check(a,h);
		check(h,a);
	}else{
		for(int i=0;i<=pow[dc-1];i++){
			enumerate(val,dc-1);
			val*=div[dc-1];
		}
	}
}
int main(int ac,char * args[]){
	if(ac==2){
		b_=0;
		for(int i=0;args[1][i];i++)
			b_=b_*10+args[1][i]-'0';
	}else
		b_=1;
	for(;;b_++){
		if(kbhit()){
			cout << b_ << endl;
			return 0;
		}
		int dc=0;
		number n=b_;
		for(int i=0;(i<bigCNT) && (big[i]*big[i]<=n);i++){
			if(!(n%big[i])){
				number d=div[dc]=big[i];
				int cnt=0;
				do{
					n/=d;
					cnt++;
				}while(!(n%d));
				pow[dc++]=cnt;
			}
		}
		if(n!=1){
			div[dc]=n;
			pow[dc]=1;
			dc++;
		}
		for(int i=0;i<dc;i++)
			pow[i]<<=1;
		enumerate(1,dc);
	}
	return 0;
}
a=6;s=6;t=5;p=16;q=11
{
	L=pp-qq +pp+qq + 2pq = 2pp + 2pq=2p(p+q)
	L=2(2sta+ssa+tta)
	S=2pq(pp-qq)/2=pq(pp-qq)
	S=2sta(ssa-tta)
	//jest to wariant w ktorym podstawa to 2sta

}
{
	2p(p+q)=2(2sta+ssa+tta)

	pq(pp-qq)=2sta(ssa-tta)
}
{
	p(p+q)=a(s+t)(s+t)
	pq(p+q)(p-q)=2staa(s+t)(s-t)
}
{
	p(p+q)=a(s+t)(s+t)
	(s+t)q(p-q)=2ast(s-t)
	//zaden dzielnik s+t nie moze byc dzielnikiem s, bo bylby wtedy dzielnikiem t i viceversa
	//zatem :
	  (s+t) \ 2a(s-t)
	//jesli jednak
	d\(s+t)  && d\s-t  =>  d\ 2s ,
	//ale s+t jest nieparzyste wiec d jest nieparzyste wiec
	d\s =>  d\t d=gcd(s+t)
	//zatem musi byc:
	(s+t)\ 2a  => (s+t) \ a
	//niech zatem:
	a=(s+t)c
}
{
	p(p+q)=c(s+t)(s+t)(s+t)
	(s+t)q(p-q)=2cst(s-t)(s+t)
}
{
	p(p+q)=c(s+t)(s+t)(s+t)
	q(p-q)=2cst(s-t)
	//gcd(p,p+q)=gcd(p,q)=gcd(p,p-q)=1
	//wiec:
	d\p && d\c =>  d\q(p-q) => d\gcd(p,q(p-q))=1
	//zatem:
	d\p => d \ (s+t)(s+t)(s+t)
	//zauwazmy tez ze gcd(p+q,p-q)=gcd(p+q,2q)=gcd(p+q,q)=1 zatem
	d\(p+q) && d\c =>  d\q(p-q) => d\ gcd(p+q,q(p-q))=1
	//zatem
	d\p => d \ (s+t)(s+t)(s+t)
	//a dokladniej pokazalem ze:
	c=1
}
{
	p(p+q)=(s+t)(s+t)(s+t)
	q(p-q)=2st(s-t)
	//gcd obu rownan = 1
}



//wariant drugi:
{
	L=pp-qq +pp+qq + 2pq = 2pp + 2pq=2p(p+q)
	L=2(ssa-tta+ssa+tta)=4ass
	S=2pq(pp-qq)/2=pq(pp-qq)
	S=2sta(ssa-tta)
	//jest to wariant w ktorym wysokosc to 2sta
}
{
	p(p+q)=2ass
	pq(p+q)(p-q)=2sta(ssa-tta)
}
{
	p(p+q)=2ass
	q(p-q)2ass=2sta(ssa-tta)
}
{
	p(p+q)=2ass
	q(p-q)s=at(s+t)(s-t)
	//gcd(s,s+t)=gcd(s,s-t)=gcd(s,t)=1 ergo:
	s \ a   => a=cs
}
{
	p(p+q)=2csss
	q(p-q)=ct(s+t)(s-t)
	//gcd(p(p+q),q(p-q))=gcd(p+q,p-q)=gcd(p+q,2q)=gcd(p+q,q)=1
	//1=gcd(2css,ct(s+t)(s-t))= ergo:
	c=1

}
{
	p(p+q)=2sss
	q(p-q)=t(s+t)(s-t)
	//sprawdzenie:
	//16*27=2*6*6*6
	//11*5=5(11)(1)
	p=2xxx
	p+q=yyy
	q=yyy-2xxx
	s=xy
	gcd(x,y)=1
}
{
	(yyy-2xxx)(4xxx-yyy)=t(xy+t)(xy-t)
	//wiemy ze:x=2 y=3 t=5 jest rozwiazaniem
	//pytanie: czy to przypadek ze xy-t=1; x+y=t ; x,y,t sa liczbami pierwszymi?
	//y jest nieparzyste wiec lewa strona jest nieparzysta
	//gdyby x bylo nieparzyste to t(xy+t) byloby parzyste co daje sprzecznosc
	/*       %5 %6 %3
	0 0  0    0  0  0
	1 1  1    1  1  1
	2 4  8    3  2  2
	3 9  27   2  3  0
	4 16 64   4  4  1
	5 25 125  0  5  2
	*/
	//nasze rownanie modulo 6:
	(y-2x)(4x-y)=t(xy+t)(xy-t)

	y jest nieparzyste
	x jest parzyste
	t jest nieparzyste
}

