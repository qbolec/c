#include <iostream.h>
const char poziom_m=25;
char wyp='c';
char astack[poziom_m+1];
char whichstack[poziom_m+1];
long limit;
char poziom=0;
char * a=astack;
char * w=whichstack;
int main()
{
	cin >> limit;
	switch(limit)
	{
	case(1): cout << "1\na";return 0;
	case(2): cout << "2\nab";return 0;
	case(3): cout << "2\naba";return 0;
	default:
		cout << 3 << endl;
		*a='a';
		*w=0;

		while(1)
		{
			switch(*w)
			{
			case(0)://wejscie do funkcji
				if(poziom==poziom_m)
				{
					if(*a=='a')
					{
  					//	if(wyp=='d')
   					//		wyp='c';
  					//	else
  					//	{
	   						cout.put(wyp);
							limit--;
   							if(limit==0)return 0;

   							wyp='c';
	  				//	}
                	}
					else
					{
						if(wyp=='c') wyp='b';
						else if(wyp=='b') wyp='a';
					}
					w--;
					a--;
					poziom--;
				}
				else
				{
					if(*a=='a')
					{
						*w=1;
						*++w=0;
						poziom++;
						*++a='a';
					}
					else
					{
						*w=3;
						*++w=0;
						poziom++;
						*++a='b';
					}
				}
			break;
			case(1)://a,a
				*w=2;
				*++w=0;
				poziom++;
				*++a='b';
			break;
			case(2)://a,b
				w--;
				a--;
				poziom--;
			break;
			case(3)://b,b
				*w=4;
				*++w=0;
				poziom++;
				*++a='a';
			break;
			case(4)://b,a
				w--;
				a--;
				poziom--;
			}
		}
	}
	return 0;
}

