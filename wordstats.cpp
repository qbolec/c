#include <fstream.h>
#include <stdlib.h>
const int alfabetcount=77;
int alfabetcast[256];
int asciicast[alfabetcount];
long lencount[32];


ifstream fin("input.txt");
ofstream fout("output.txt");
//#define fin cin
//#define fout cout


struct q3
{
	q3 * q[alfabetcount];
	long count;
};
struct stat
{
	char * text;
	long count;
};
stat stats[256000];
long stat3=0;
q3 * root;

void add( unsigned char * text, q3 * & drzewo)
{
	if(drzewo==0)
	{
		drzewo = new q3;
		drzewo->count=0;
		for(int i=0;i<alfabetcount;i++)
			drzewo->q[i]=0;
	}
	if(*text==0)
	{
		drzewo->count++;
	}
	else
	{
		add( text+1, drzewo->q[ alfabetcast[*text] ]);
	}
}


void fileadd( char * filename)
{
	ifstream qin( filename, ios::bin );
	unsigned char wordbuff[64];
	char itsaword=1;
	char newword;
	int ix=0;

	while(!qin.eof())
	{

	        qin.get(wordbuff[ix]);

	        if(alfabetcast[wordbuff[ix]]!=-1)
	        {
	        	ix++;
	        	if(ix>30)
	        	{
	        		ix=0;
	        		itsaword=0;
	        	}
	        }
	        else
	        {
	        	if( (wordbuff[ix]==' ') || (wordbuff[ix]==10) || (wordbuff[ix]==13))
	        	{
                                newword=1;
	        	}
	        	else
	        	{
	        		newword=0;
	        		itsaword=0;
	        	}
	        	if((ix>0) && (ix<30) && (itsaword==1))
	        	{

	        		wordbuff[ix]=0;
	        		for(int i=0;i<ix;i++)
	        		{
	        			if(alfabetcast[wordbuff[i]]<alfabetcast['a'])
	        			{
	        				wordbuff[i]=asciicast[ alfabetcast[wordbuff[i]]+alfabetcast['a'] ];
	        			}

	        		}
	        		lencount[ix]++;
	        		add( wordbuff , root );
	        	}
	        	itsaword=newword;
	        	ix=0;
	        }

	}
}
void flush3( ofstream &qout, q3 * drzewo ,unsigned char * text , int ix)
{
	if(drzewo==0)return;
	if(drzewo->count)
	{
		text[ix]=0;
		qout << text << " " <<drzewo->count << endl;
                stats[stat3].text=new char[ix+1];
                for(int i=0;i<=ix;i++)
                	stats[stat3].text[i]=text[i];
                stats[stat3].count=drzewo->count;
                stat3++;

	}
	for(int i=0;i<alfabetcount;i++)
	{
		if( drzewo->q[i] )
		{
                       text[ix]=asciicast[i];
                       flush3( qout , drzewo->q[i] , text , ix+1);
		}
	}
}
void flushtofile(char * filename)
{
	ofstream qout(filename);
	unsigned char wordbuff[32];
	flush3( qout , root , wordbuff , 0);
}
void preparedict()
{
	ifstream alfa("alfabet.txt");

	for(int a=0;a<256;a++)
		alfabetcast[a]=-1;
	int slot3=0;

	for(int i=0;i<64;i++)
	{
		alfabetcast[alfa.get()]=i;
	}

	for(int a=0;a<256;a++)
	{
		if(alfabetcast[a]!=-1)
			asciicast[alfabetcast[a]]=a;
	}
}
int cmp(const void * a,const void * b)
{
	return ((stat *)a)->count - ((stat *)b)->count;
}
void flushsorted( char * filename )
{
	ofstream qout( filename);
	qsort( stats, stat3 , sizeof(stat) , cmp );
	for( int i=0;i<stat3;i++)
		qout << stats[i].text << "\t" << stats[i].count << endl;
	for( int i=0;i<32;i++)
		qout << "Naliczono\t" << lencount[i] << "\twyrazow\t" << i << "\tliterowych" << endl;
}
int main()
{
	preparedict();
	char filename[256];
	/*int more=1;
	while(more)
	{
		fout << endl << "Podaj Nazwe Pliku:" << endl ;
		fin >> filename;
		fout << "...przetwarzam " << filename << endl << flush;
		fileadd( filename );
		fout << endl <<  "Czy Chcesz dodac jeszcze jakis plik 0-nie 1-tak :";
		fin >> more;
	}
	fout << endl << "Gdzie zapisac statsy?" << endl;
	fin >> filename;
	flushtofile( filename );
	fout << endl << "A Gdzie dane posortowane wg statsow?" << endl;
	fin >> filename;
	flushsorted( filename );*/
	fileadd( "msgarch.dat" );
	flushtofile( "stats.txt" );
	flushsorted( "sotred.txt" );
	return 0;
}
