#include <iostream.h>
/*
total[n][k]= ilosc poprawnych wyrazów o d³ugoœci dok³adnie n, przy limicie k
total[n][k]=
*/
class verylong
{
	public:
	unsigned char byte[128];
	unsigned char limit;
	addtome( verylong & other)
	{
		long rest=0;
		unsigned char i;
        for(i=0;i<other.limit;i++)
        {
        	rest+=byte[i]+other.byte[i];
        	byte[i]=rest&255;
        	rest>>=8;
        }
        while(rest)
        {
            rest+=byte[i];
            byte[i++]=rest&255;
            rest>>=8;
        }
        if(i>limit)limit=i;
	}
	cmptome( verylong & other)
	{
		if(other.limit>limit)return 1;
		if(other.limit<limit)return -1;
		for(unsigned char i=limit-1;i>=0;i--)
		{
			if(other.byte[i]>byte[i])return 1;
			if(other.byte[i]<byte[i])return -1;
		}
		return 0;
	}
	verylong(unsigned long x)
	{
		limit=0;
		for(unsigned char i=0;i<128;i++)
			byte[i]=0;
		while(x>0)
		{
			byte[limit++]=x&255;
			x>>=8;
		}

	}
	verylong()
	{
		limit=0;
		for(unsigned char i=0;i<128;i++)
			byte[i]=0;
	}
};
long total[10000][114];
long totalbig[10000][114];
inline long gettotal(long n,long k)
{
	if(n<0)return 0;
	if(k<0)return 0;
	return total[n][k];
}
inline long valid(long i,long n,long k)
{
	i++;
	if(i>=n)return 1;
	return gettotal(n-i,k);
}
void init()
{
	//n=1 zostawiamy 0 bo i tak nie wiadomo co to znaczy n=0,ale chyba jest dokladnie jeden ciag o dlugosci 0
	//n=1 niezaleznie od k jest + oraz - czyli 2
	for(long k=0;k<114;k++)total[0][k]=0;
	for(long k=0;k<114;k++)total[1][k]=totalbig[1][k]=2;
	for(long n=2;n<10000;n++)
	for(long k=0;k<114;k++)
	{
		//total[n][k]= total[n-1][k]+total[n-2][k]+...total[n-k][k]
		long maxk= (k<n)?k:n;
		for(long i=0;i<=maxk;i++)
			total[n][k]+=valid(i,n,k);
		totalbig[n][k]=totalbig[n-1][k]+total[n][k];
	}
}

inline long getprefixminusescount(char * number)
{
	long out;
	for(out=0;*number=='-';number++)out++;
	return out;
}
inline long len(char * s)
{
	long l=0;
	while(*s++)l++;
	return l;
}
long tolong(char * number,long n,long k)
{
	if(n<=0)return 0;
	long out=0;
	out=totalbig[n-1][k];
	while(n>0)
	{
		long minuses= getprefixminusescount( number );
		//nasz ci¹g to ------+coœ
		//out to :     -----------+coœ
        long maxk= (k<n)?k:n;
		for(long i=maxk;i>minuses;i--)
		{
			out+= valid(i,n,k);//ilosc ciagow zaczynajacych sie od i minusow, o dlugosci n, gdzie k to limit:)
		}
		//nasz ci¹g to ------+coœ
		//out to :     ------+------
		//ró¿ni¹ sie koñcówk¹:coœ
		number+=minuses+1;
		n-=minuses+1;
	}

	return out;
}
void construct(long number,long k,char * out,long &n)
{

	for(n=1;totalbig[n][k]<=number;n++);
	long rest=number-totalbig[n-1][k];
	long minuscount;
	long restn=n;
	while(restn>0)
	{
    	long maxk= (k<restn)?k:restn;
    	for(minuscount=maxk;valid(minuscount,restn,k)<=rest;minuscount--)
    	{
    		rest-=valid(minuscount,restn,k);
    	}
    	for(long i=minuscount;i;i--)
    		*out++='-';
    	*out++='+';
    	restn-=minuscount+1;
    }
}
int main()
{
    init();
    long n,k1,k2,t,x;
    char buffer[1024];
    cin >>  k1 >> k2 >> t ;
    while(t--)
    {
    	cin >> buffer;
    	n=len(buffer);
    	x=tolong(buffer,n,k1);
    	construct(x,k2,buffer,n);
    	for(long i=0;i<n;i++)
    		cout << buffer[i];
    	cout << endl;
    }
    return 0;
}
