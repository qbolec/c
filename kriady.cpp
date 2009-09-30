#include <iostream.h>
long tab[10002]={0,1};
long k,n;
int main()
{
	cin >> n >> k;
// tab[n][k]=tab[n-1][k-1]*(n-k)+tab[n-1][k]*k;
	for(long i=1;i<=n;i++)
	for(long j=k;j>1;j--)
	{
 		tab[j]=tab[j]*j+tab[j-1]*(i-j+1);
 		tab[j]%=(7*13*66);
	}
	tab[k]+=7*13*66-1;
	cout << (tab[k]%7)+1 << ' ' << (tab[k]%13)+1 << ' ' << (tab[k]%66)+1 << endl;
    return 0;
}
