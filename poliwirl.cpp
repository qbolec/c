#include <iostream.h>
#include <math.h>
double a,b,c,delta;
void main()
{
	cin >> a >> b >> c;	a*=2;c*=2;
	if( (delta=b*b-a*c)<0 ) cout << "œpae" ;
	else	{
		delta=sqrt(delta);
		cout << (-b+delta)/a << " " << (-b-delta)/a;
	}
}
