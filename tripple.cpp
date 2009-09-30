class tripple
{
	public :
	const long SIZE=1024;
	unsigned char sign;
	unsigned char data[SIZE];//1kb per variable
	long p;//for(i=0;i<SIZE;i++) 2^(8*i-p) *data[i];
	char operator < (tripple & t)
	{

	}
	char operator > (tripple & t)
	{

	}

	tripple & operator + (tripple & t)
	{
		tripple(
		return result;
	}
	tripple & operator - (tripple & t)
	{
		return result;
	}
	tripple & operator * (tripple & t)
	{
		return result;
	}
	tripple & operator / (tripple & t)
	{
		pompmax();
		t.unpomp();
		tripple result();
		result.p = p-t.p;
		//a teraz se poprostu dziele liczbe data[] przez liczbe t.data[]

		return result;
	}
	tripple(tripple &clone)
	{
		p=clone.p;
		for(long i=0;i<SIZE;i++)data[i]=clone.data[i];
	}
	tripple(long l)
	{
		if(l<0)
		{
			l=-l;
			sign=-1;
		}
		else
			sign=1;
		p=0;
		long i;
		for(i=0;i<4;i++)
		{
			data[i]=l&255;
			l>>=8;
		}
		for(i=4;i<SIZE;i++)data[i]=0;

	}
	tripple(long l,long d)
	{
		tripple a(l);
		tripple b(d);
		tripple c=a/b;
		tripple(c);
	}
}
