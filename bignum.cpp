//modular china long
const unsigned char primescount=29;
const unsigned char primes[primescount]={101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251};
#include <iostream.h>
const long SIZE=64000;
const long BASE=10;
class verylong
{//oldsql
	public:

	unsigned char byte[SIZE];
	long limit;
	inline void operator +=(unsigned long other)
	{
		long rest=0;
		long i=0;
		while(other)
		{
			rest+=byte[i]+(other%BASE);
			byte[i++]=rest%BASE;
			rest/=BASE;
			other/=BASE;
		}
		while(rest)
		{
			rest+=byte[i];
			byte[i++]=rest%BASE;
			rest/=BASE;
		}
		if(i>limit)limit=i;
	}
	inline void operator -=(verylong & other)
	{
		long help=0;//zaporzyczenie od nastêpnej kolumny-zaporzyczenie dla poprzedniej:)
		long i=0;
		for(i=0;i<other.limit;i++)
		{
			help+=BASE+byte[i]-other.byte[i];
			byte[i]=help%BASE;
			help/=BASE;
			help--;
		}
		while(help<0)
		{
			help+=BASE+byte[i];
			byte[i++]=help%BASE;
			help/=BASE;
			help--;
		}
		while(limit--)
		{
			if(byte[limit])break;
		}
		limit++;

	}
	inline void operator -=(unsigned long other)
	{
		long help=0;//zaporzyczenie od nastêpnej kolumny-zaporzyczenie dla poprzedniej:)
		long i=0;
		while(other)
		{
			help+=BASE+byte[i]-(other%BASE);
			byte[i++]=help%BASE;
			other/=BASE;
			help/=BASE;
			help--;
		}
		while(help<0)
		{
			help+=BASE+byte[i];
			byte[i++]=help%BASE;
			help/=BASE;
			help--;
		}
		while(limit--)
		{
			if(byte[limit])break;
		}
		limit++;
	}
	inline void operator +=(verylong & other)
	{
		long rest=0;
		long i;
        for(i=0;i<other.limit;i++)
        {
        	rest+=byte[i]+other.byte[i];
        	byte[i]=rest%BASE;
        	rest/=BASE;
        }
        while(rest)
        {
            rest+=byte[i];
            byte[i++]=rest%BASE;
            rest/=BASE;
        }
        if(i>limit)limit=i;
	}
	inline void operator =(verylong & other)
	{
		//we copy only the importand bytes
		long i;
		for(i=other.limit-1;i>=0;i--)byte[i]=other.byte[i];
		//we clear unused bytes
		for(i=other.limit;i<limit;i++)byte[i]=0;
		limit=other.limit;
	}
	inline void operator <<=(unsigned long pos)
	{
		limit+=pos;
		long i;
        for(i=limit-1;i>=pos;i--)
        	byte[i]=byte[i-pos];
        for(i=0;i<pos;i++)byte[i]=0;
	}
	inline unsigned char & operator [](unsigned long pos)
	{
		if(pos>=limit)limit=pos+1;
		return byte[pos];
	}
	inline char operator <( verylong & other)
	{
		if(other.limit>limit)return 1;
		if(other.limit<limit)return 0;
		for(long i=limit-1;i>=0;i--)
		{
			if(other.byte[i]>byte[i])return 1;
			if(other.byte[i]<byte[i])return 0;
		}
		return 0;
	}
	unsigned long tolong()//for debug purpouses only:)
	{
		long i=0;
		long out=0;
		long ratio=1;
		while(0x7FFFFFFF-9*ratio>out)
		{
			out+=ratio*byte[i++];
			ratio*=BASE;
			if(i==limit)break;
		}
		return out;
	}
	verylong(unsigned long x)//konstruktor konwertuj¹cy long->verylong
	{
		limit=0;
		while(x>0)
		{
			byte[limit++]=x%BASE;
			x/=BASE;
		}
        for(long i=limit;i<SIZE;i++)
			byte[i]=0;

	}
	verylong()//konstruktor tworzacy pust¹ liczbê
	{
		limit=0;
		for(long i=0;i<SIZE;i++)
			byte[i]=0;
	}
};

class chinalong
{

public:
	unsigned char phantom[primescount];
	void operator +=(chinalong &o)
	{
		for(unsigned char i=0;i<primescount;i++)
		{
			long temp=o.phantom[i]+phantom[i];
			phantom[i]=temp%primes[i];
		}
	}
	void operator -=(chinalong &o)
	{
		for(unsigned char i=0;i<primescount;i++)
		{
			long temp=o.phantom[i]-phantom[i];
			phantom[i]=temp%primes[i];
		}
	}
	void operator *=(chinalong &o)
	{
		for(unsigned char i=0;i<primescount;i++)
		{
			long temp=o.phantom[i]*phantom[i];
			phantom[i]=temp%primes[i];
		}
	}
	void operator =(chinalong &o)
	{
		for(unsigned char i=0;i<primescount;i++)
			phantom[i]=o.phantom[i];
	}
	char operator ==(chinalong &o)
	{
		for(unsigned char i=0;i<primescount;i++)
			if(o.phantom[i]!=phantom[i])return 0;
		return 1;
	}
    toverylong(verylong & v)
    {
    	v=phantom[0];//initialize
    	verylong m=primes[0];//initialize safe multiplier
    	for(long i=1;i<primescount;i++)
    	{
    		verylong one=inv( v , m );
    		one
    	}
    }
	chinalong(long x)
	{
		for(unsigned char i=0;i<primescount;i++)
			phantom[i]=x%primes[i];
	}
};

char er[256];
int main()
{

    return 0;
}
