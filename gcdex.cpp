long gcdex(long k, long * m, long **x, long i,long o,long n)
{
	if(i==o)
		return i;
	long r= m[i]/m[o];
	m[i]-=r*m[o];
	if(m[i])
	{
		for(long j=0;j<k;j++)
			x[i][j]-=r*x[o][j];
		o=i;
	}
	else
		n--;
	if(++i==k)i=0;
	while(!m[i])if(++i==k)i=0;
		return gcdex( k , m , x , i , o , n );
}
long gcd(long k, long * m , long * w)
{//ci¹g m ma byc malej¹cy
	long **x= new long *[k];
	for(long i=0;i<k;i++)
	{
		x[i]=new long[k];
		for(long j=0;j<k;j++)
			x[i][j]=0;
		x[i][i]=1;
	}
	long id=gcdex(k,m,x,0,k-1,k);
	for(long i=0;i<k;i++)
		w[i]=x[id][i];
	return m[id];
}

/*--sample of use--*/
#include <iostream.h>
int main()
{
	long k;
	cout << "Podaj : # liczb dla ktorych chcesz policzyc gcd" << endl;
	cin >> k;
	long * m=new long[k];
	long * w=new long[k];
	cout << "Podaj : liczby w kolejnosci od najwiekszej do najmniejszej" << endl;
	for(long i=0;i<k;i++)
		cin>> m[i];
	long g=gcd(k,m,w);
	cout << "Wynik to :" << endl << g << '=' << w[0] << "*m0"  ;
	for(long i=1;i<k;i++)
	{
		cout << '+' << w[i] << "*m" << i ;
	}
	return 0;
}

