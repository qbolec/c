/*
program liczy pierwiastek z zadanej liczby z przedzialu 1..99
znajduje takie a oraz m ¿e:
a*a
--- ~= 1
 m

gdzie : m= number* 10^2n
widaæ zatem ¿e a= sqrt(number)*10^n
wynikiem bêdzie zatem a.
zmienn¹ pomocnicz¹ jest asq=a*a
*/
#include <iostream.h>

const long SIZE=64000;
const long BASE=10;
class verylong
{
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
int main()
{
	
	while(1)
	{
		long cyfry=0;
		cout << "Podaj liczbê ca³kowit¹[1..99] z której chcesz wyci¹gn¹æ pierwiastek:";
		unsigned long number;
		cin >> number;
	
		//verylong a(0);//licznik naszego u³amka dziesiêtnego którego kolejne cyfry bêdziemy odgadywac
		verylong twoa(0);// 2*a - samo a nie jest potrzebne nigdzie w programie ale zostawilem miejsca w ktorych bylo
		verylong asq(0);//=a*a
		verylong m(number);//a*a/m = 1 oznacza ze a= pierwiastek z m...zatem bedziemy sie starac aby a*a<=m
		verylong tempasq(0);//temp for asq
		while(asq.limit<SIZE-10)//ilosc iteracji zalezy od pojemnoœci naszej arytmetyki [10 to taki nasz zapas - wystarczy 3]
		{
			//teraz sprawdzam jak¹ cyfrê mogê dopisaæ na koñcu a, ¿eby a*a nie przekroczy³o m
			unsigned char c;//odgadywana cyfra
			for(c=0;c<10;c++)
			{
				/*
				tempa = a + c
				tempasq = a*a + c*c + 2*a*c
				
				w nastêpnym kroku by³oby:
	
			 	tempa'= a + (c+1)
		 		tempasq' = a*a + c*c + 1 + 2*c + 2*a*c + 2*a

			 	tempasq'-tempasq = 1+2*c+2*a <- o tyle zwiêksza siê a*a przy ka¿dym c zaczynaj¹c od c=0;
			    */
				tempasq+=1+2*c;
			    //tempasq+=a;
			    //tempasq+=a;
				tempasq+=twoa;
			    //jeœli tempsq przekroczy³o m to znaczy ¿e poprzednia cyfra by³a ok a ta ju¿ nie
				//zatem nale¿y dopisaæ na koñcu "c" bo to w³aœnie jest poprzednia cyfra
				if( m<tempasq )//porównujemy m do tempasq
				{
		    		break;//wychodzimy z fora[przedobrzylismy]
				}
			}
			tempasq-=1+2*c;
			//tempasq-=a;
			//tempasq-=a;
			tempasq-=twoa;
			asq=tempasq;
			//a[0]=c;//a+=c;
			twoa+=2*c;
			c+='0';//convert to ASCII
			cout.put(c);//wypiujemy na ekran cyferkê
			if(!cyfry++)cout.put('.');//kropka:)
			//a<<=1;//dopisujemy zero na koñcu u³amka[mno¿ymy przez 10]
			twoa<<=1;
			asq<<=2;//jesli a roœnie 10 razy to a*a roœnie 100 razy
			tempasq<<=2;//zaczynamy od liczby (a+0) mo¿na daæ tutaj tempasq=asq
			m<<=2;//jesli licznik roœnie 100 razy to mianownik te¿
		}
		cout << endl << "Wyliczono:" << cyfry << " cyfr" << endl;
	}
	return 0;
}
