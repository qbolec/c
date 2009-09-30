#include <iostream.h>
long u[2][1000002];
long n,m,l;
long a,b,r;
long i,maxk,mink,k;
long s[2];
void un(long a,long b,long r)
{
	while(u[r][a]>0)a=u[r][a];
	while(u[r][b]>0)b=u[r][b];
	if(a==b)return;
	if(u[r][a]>u[r][b])
	{
 		u[r][a]=b;
 		u[r][b]=0;
	}
	else
	{
 		u[r][b]=a;
 		u[r][a]=0;
	}
	s[r]--;
}
int main()
{
	cin >> n >> m >> l;
	s[0]=s[1]=n;

	for(i=m;i;i--)
	{
 		cin >> a>>b>>r;
 		un(a,b,r);
 	}
	mink=s[0]-1;
	maxk=n-s[1];
	for(i=l;i;i--)
	{
  		cin>> k;
 		cout << (((k>=mink)&&(k<=maxk))?"tak":"nie") << endl;
	}
	return 0;
}
