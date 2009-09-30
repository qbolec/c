#include <iostream.h>
void eu(long a, long b , long ax ,long bx, long ay,long by)
{
	long x= ax*a+bx*b;
	long y=  ay*a+by*b ;
	if((x%y==0) || (y==1))
	{
		cout << "gcd=" << y << "="<< ay << "*" << a << "+" << by << "*"<< b<<endl ;
		return;
	}
	cout << x << "=" << ax << "*" << a << "+" << bx << "*" <<b ;
	cout << "vs." ;
	cout << y<< "=" << ay << "*" << a << "+" << by << "*" <<b << endl;;
	long r=y/x;
	cout << y << "=" << x << "*" << r << "+" <<(y-x*r) << endl;
	by-=r*bx;
	ay-=r*ax;
	eu(a,b,ay,by,ax,bx);
}
int main()
{
	cout << "Podaj a,b a>b" << endl;
	long a,b;
	cin >> a >> b;
    eu(a,b,1,0,0,1);
}
