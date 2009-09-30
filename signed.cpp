#include <iostream.h>
int main()
{
	unsigned char a=0;
	signed char b=a;
	for(long t=0;t<256;t++)
	{
		cout <<(int) a << "is signed : " <<(int) b << endl;
		a++;
		b=a;
	}
	return 0;
}

