/*Better Sooner Then Later    *\

        written by

         *Q*B*A*

\*Rockets (Lasers, Fasts,ect.)*/


//--------------------------includes[_][#][x]
#include <stdlib.h>
#include <iostream.h>
//----------------------------------------=[|

//---------------------------structs[_][#][x]
struct point {
	      double x;
	      double y;
	      short int c;
             };
//----------------------------------------=[|

//---------------------------globals[_][#][x]
point	* BiW;
int BiWCount;
int * BIGINDEXBUFFER;
//----------------------------------------=[|


//-------------------------functions[_][#][x]
void Swap(int * a,int * b)
{
        int w=*a;
        *a=*b;
        *b=w;
}

void RightScroll(int * st,int * en)
{
	int w=*en;
	while(en!=st)
	{
	 *en=*(en-1);
	 en--;
	}
	*st=w;
}

void Minus(int * start,int iblen)
{
        int * ne;
        ne=start+1;
	for(int i=1;i<iblen;i++,ne++)
        {
	 BiW[*ne].x-=BiW[*start].x;
	 BiW[*ne].y-=BiW[*start].y;
        };

}
int findleft(int * indexbuffer,int iblen)
{
        int out=0;
        double best=BiW[indexbuffer[0]].x;
        for(int i=1;i<iblen;i++)
        {
         if(BiW[indexbuffer[i]].x<best)
         {
          best=BiW[indexbuffer[i]].x;
          out=i;
         }
        }
        return out;
}


int compangels(const void * a,const void * b)
{
        int whata=*((int *)a);
        int whatb=*((int *)b);
        if( BiW[whata].x*BiW[whatb].y>BiW[whatb].x*BiW[whata].y)return 1;
        else return -1;
}

void Solve(int * indexbuffer, int iblen)
{
        if(iblen<4)return ;
        Swap( indexbuffer,indexbuffer + findleft(indexbuffer,iblen));
        Minus(indexbuffer,iblen);
        qsort(indexbuffer+1,iblen-1,sizeof(int),compangels);

        if(iblen==4)
        {
         if(BiW[indexbuffer[1]].c+BiW[indexbuffer[0]].c) Swap(indexbuffer+1,indexbuffer+3);
          return;
          };

        int smartcounter=0;
        int j=0;
        lab:    smartcounter+=BiW[indexbuffer[j]].c;
                j++;
        if(smartcounter) goto lab;
        if(BiW[indexbuffer[j]].c==BiW[indexbuffer[0]].c)goto lab;

        RightScroll(indexbuffer+1,indexbuffer+j);

        Solve(indexbuffer+2,              j-2);
        Solve(indexbuffer+j+1,        iblen-j);

}



void wczytajinformacjeopunktach()
{
        cout << "Podaj mi liczbe punktow czyli 2n:\n";
        cin >> BiWCount;

        BiW=new point[BiWCount];

        cout << "\nProsze podac wspolrzedne wszystkich bialych punktow:\n";
        for(int i=0;i<BiWCount/2;i++)
        {
         cout << "\nx <spacja> y dla punktu #"<< i <<":";
         cin >> BiW[i].x >> BiW[i].y ;
         BiW[i].c=1;
        };

        cout << "\nProsze podac wspolrzedne wszystkich czarnych punktow:\n";
        for(int i=BiWCount/2;i<BiWCount;i++)
        {
         cout << "\nx <spacja> y dla punktu #"<< i-(BiWCount/2) <<":";
         cin >> BiW[i].x >> BiW[i].y ;
         BiW[i].c=-1;
        }

        cout << "\nTnx - now proccieding\n";
}
void wypiszdane()
{
        cout << "\n\nOto pary punktow (Bialy + Czarny)\n";
        for (int i=0;i<BiWCount;i+=2)
        {
         cout << "\nPara #"<<i/2 ;
         if( BIGINDEXBUFFER[i]<BiWCount/2)cout <<BIGINDEXBUFFER[i] << " + " << BIGINDEXBUFFER[i+1]-(BiWCount/2) ;
         else cout <<BIGINDEXBUFFER[i+1] << " + " << BIGINDEXBUFFER[i]-(BiWCount/2) ;
        }
}

void initindexbuffer()
{
        BIGINDEXBUFFER= new int[BiWCount];
        for(int i=0;i<BiWCount;i++)
        BIGINDEXBUFFER[i]=i;
}

int main()
{

	wczytajinformacjeopunktach();//wymaga zaimplementowania!!!
        initindexbuffer();


	Solve(BIGINDEXBUFFER,BiWCount);

	wypiszdane();//wymaga implementacji!!! 

return 0;
}







