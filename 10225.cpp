#include <iostream.h>

unsigned long b,l,n,p,q;


//(x+y)%z
unsigned long safeADD(unsigned long x ,unsigned long y ,unsigned  long z)
{
	x%=z;
	y%=z;
	unsigned long budget= z-x;
	if(y<budget)return x+y;
	return y-budget;
}
//(x*y)%z
unsigned long safeMULTIPLY(unsigned long x ,unsigned long y ,unsigned  long z)
{
	x%=z;
	y%=z;
	unsigned long budget= 4000000000/x;
	if(y<budget)return (x*y)%z;

	unsigned long o=safeMULTIPLY(x,y>>1,z);
	o=safeADD(o,o,z);
	if(y&1)o=safeADD(o,x,z);
	return o;
}
int countl()
{
	q=1;
	for(l=0;l<p;l++)
	{
		if(q==n)return 1;
		q=safeMULTIPLY(q,b,p);
	}
	return 0;
}
int main()
{
	cin >>p;
	while(!cin.eof())
	{
		cin >> b >> n;
		if(countl())
			cout << l;
		else
			cout << "no solution";
		cout << endl;
		cin >> p;
	}	
	return 0;
}
