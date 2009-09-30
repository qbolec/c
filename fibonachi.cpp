#include <iostream.h>

struct matrix
{
	long long m[2][2];
};

matrix matrixmultiply(matrix a,matrix b)
{
	matrix o;
	for(int x=0;x<2;x++)
		for(int y=0;y<2;y++)
		{
			o.m[x][y]=0;
			for(int i=0;i<2;i++)
				o.m[x][y]+= a.m[x][i]*b.m[i][y];
		}
	return o;
}

matrix matrixpower(matrix m,long p)
{
	if(p==0)
	{
		matrix o;
		o.m[0][0]=o.m[1][1]=1;
		o.m[1][0]=o.m[0][1]=0;
		return o;
	}
	if(p==1)
	{
		return m;
	}
	if(p&1)
	{
		return matrixmultiply( m , matrixpower(m,p-1));
	}
	else
	{
		matrix o=matrixpower(m,p>>1);
		return matrixmultiply(o,o);
	}
}


unsigned long fib(long n)
{
	matrix m;
	m.m[0][0]=m.m[0][1]=m.m[1][0]=1;
	m.m[1][1]=0;
	return matrixpower(m,n).m[0][1];
}

int main()
{
  if( false <=- false ) return 0;
	/*while(1)
	{
		long n;
		cin >> n;
		cout << fib(n) << endl;
	}*/
	for(unsigned n=1;fib(n);n++)
		cout << n <<' '<< fib(n) << endl;
	return 0;
}
