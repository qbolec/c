//brutforce
//triangles :  (p,q,r) and (a,b,b)
//b'= b/2
//L=p+q+r
//S=p*q/2
//h=sqr(a*a-b*b)
//Range=L+r
//X=a+b'=L/2
//D=a-b'

#include<math.h>
#include<iostream.h>
#include<stdlib.h>
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
int main(){
	number div[10000];
	cout << sizeof(div) << flush << endl;

	for(number b_=1000000;b_<100000000;b_++){
		number dc=0;
		for(number d=1;d*d<=b_;d++)
			if(!(b_%d)){
				div[dc++]=d;
				div[dc++]=b_/d;
			}
		for(number i=0;i<dc;i++)
			for(number j=0;j<=i;j++){
				number su=div[i]*div[j];
				number ro=(b_/div[i])*(b_/div[j]);
				number a=(su+ro)>>1;
				number h=su-a;
				if(!h)
					continue;
				number L=(b_+a)<<1;
				if(!L){
					cout << b_ << ' ' << su << ' ' << ro << ' ' << a << ' ' << h << endl << flush;
				}
				number S=h*b_;
				number r=(L-(S<<2)/L)>>1;
				if(L*(L-(r<<1))!=(S<<2))
					continue;
				number suma=L-r;//p+q
				number iloczyn=S<<1;//pq
				//p*p-(p+q)p+pq=0
				//number A=1;
				//number B=-suma;
				//number C=iloczyn;
				//number delta=B*B-(A*C<<2);
				number delta=suma*suma-(iloczyn<<2);
				if(delta<=0)
					continue;
				number roznica=root(delta);
				if(roznica*roznica!=delta)
					continue;
				number p=(roznica+suma)>>1;
				number q=suma-p;
				//cout << '.'<<flush;
				if(p*q!=iloczyn)
					continue;
				//cout << '!'<<flush;
					if(p*p+q*q!=r*r)
				continue;
				number b=b_<<1;
				if(gcd(p,q)==1){
					cout << "Found:" << endl
					<< "p:" << p << "q:" << q << "r:" << r << endl
					<< "a:" << a << "b:" << b << "h:" << h << "b/2:" << b_ << endl
					<< "L:" << L << "S:" << S << endl <<endl;
				}
			}
	}
	return 0;
}
