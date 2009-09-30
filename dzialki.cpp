#include <iostream.h>
long n;
long sorted[1000][1000];
long hlpsorted[1000];
long t[1000];
long l[1000];
long r[1000];
int main()
{
	cin>>n;
	long best=0;
	for(long row=0;row<n;row++)
	{
		for(long col=0;col<n;col++)
		{
			long tmp;
			cin >> tmp;
			if(tmp)t[col]=0;
			else t[col]++;
			l[col]=0;
			r[col]=0;
			sorted[t[col]][hlpsorted[t[col]]++]=col;
		}
		for(long top=999;top;top--)
		{
			while(hlpsorted[top])
			{
				long m=sorted[top][--hlpsorted[top]];
				long test=t[m]*(1+l[m]+r[m]);
				if(test>best)best=test;
				long left=m-l[m]-1;
				long right=m+r[m]+1;
				if(left>=0)
				{
					if(right<n)
					{
						if(t[left]>t[right])
							r[left]+=l[m]+1+r[m];
						else
							l[right]+=l[m]+1+r[m];
					}
					else
						r[left]+=l[m]+1+r[m];
				}
				else
					l[right]+=l[m]+1+r[m];
				}
		}
	}
	cout << best;
	return 0;
}
