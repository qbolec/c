#include <iostream.h>
long c;
long n;

struct comand
{
	char begin;//0 end!, 1 yes its  begin
	long pos;
	long time;
	char kiled;
};
comand comands[80001];
struct copiec
{
	long cox[80008];
	long incox;
	long * comp(long sm, long bi);
};
copiec cmd;
copiec seen;
char placseen[40000];


long comparecomands(long sm,long bi)
{
	if(comands[sm].pos<comands[bi].pos)return 1;
	if(comands[sm].pos>comands[bi].pos)return 0;
}
long compareplax(long sm,long bi)
{
	if(sm>bi)return 1;
	return 0;
}
addtocox(long id, copiec & c)
{
	c.incox++;
	c.cox[c.incox]=id;
	repair(c, c.incox);
}
int main()
{
	cin >> c;
	cmd.comp= comparecomands;
	seen.comp= compareplax;
	while(c--)
	{
		cin >> n;
		long time=0;
		while(n--)
		{
			comands[time].time=time;
			comands[time].begin=1;
			comands[time].kiled=0;
			cin >> comands[time].pos;
			addtocox( time , cmd);
			time++;
			comands[time].time=time;
			comands[time].begin=0;
			comands[time].kiled=0;
			cin >> comands[time].pos;
			comands[time].pos++;//chyba
			addtocox( time , cmd);
			time++;
		}
		long lastpos=0;
		while( cmd.incox )
		{

			c=coxget( cmd );
			if(lastpos==0)lastpos=comands[c].pos;
			if(comands[c].pos>lastpos)
			{//skonczono segment
				lastpos=comands[c].pos;
				//patrzymy kto wygral
				s=coxpeek(seen);
				seenplax[s>>1]=1;
			}
			if( comands[c].begin)
			{
				addtocox( c , seen);
			}
			else
			{
				comands[c].kiled=1;
			}
		}
		long tot=0;
		for(long i=0;i<n;i++)
			if(seenplax[i])tot++;
		cout << tot << endl;
		clearmem();
	}
	return 0;
}

