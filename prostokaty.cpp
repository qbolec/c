// prostokaty.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct prost{
   int w, h;
	};

typedef struct point{
   int x1, y1, x2, y2;
	};

typedef struct obrot{
   unsigned char p[4];
	};

const obrot obroty[16]={{0,0,0,0}, {0,0,0,1}, {0,0,1,1}, {0,0,1,0}, {0,1,1,0}, {0,1,1,1}, {0,1,0,1}, {0,1,0,0}, 
						{1,1,0,0}, {1,1,0,1}, {1,1,1,1}, {1,1,1,0}, {1,0,1,0}, {1,0,1,1}, {1,0,0,1}, {1,0,0,0}};

prost dane[4], dane2[4];
point punkty[4];

void putbox(int x, int y, int i)
{
  int j=i;	 
  while(--j>0)
  {
	  if((punkty[j].x1>x)&&(punkty[j].x1<x+dane[i].w)&&(punkty[j].y2>y))
		  //&&(punkty[j].y2<y+dane[i].h
		y=punkty[j].y2;
	  //j--;
  }
  punkty[i].x1=x;
  punkty[i].y1=y;
  punkty[i].x2=x+dane[i].w;
  punkty[i].y2=y+dane[i].h;
}

prost countsize()
{
  int i, maxy=punkty[0].y2, maxx=punkty[0].x2;
  prost biggest;

  for(i=1;i<4;i++)
  {
	  maxy=(maxy<punkty[i].y2?punkty[i].y2:maxy);
      maxx=(maxx<punkty[i].x2?punkty[i].x2:maxx);
  }

  biggest.h=maxy;
  biggest.w=maxx;
  return biggest;
}

void clearpoint()
{
	int i;
	for(i=0;i<4;i++)
	{
		punkty[i].x1=0;
		punkty[i].y1=0;
		punkty[i].x2=0;
		punkty[i].y2=0;
	}
}

void makeNstep(int step)
{
  int i, t;
  for(i=0;i<4;i++)
  {
    if(obroty[step].p[i]!=obroty[step-1].p[i])
	{
		t=dane[i].h;
		dane[i].h=dane[i].w;
		dane[i].w=t;
		return;
	}
  }
}

int type0()
{
   prost square;
   clearpoint();
   putbox(0,0,0);
   putbox(punkty[0].x2, 0, 1);
   putbox(punkty[1].x2, 0, 2);
   putbox(punkty[2].x2, 0, 3);
   square=countsize();
   return square.h*square.w;
}

int type1()
{
   prost square;
   clearpoint();
   putbox(0,0,0);
   putbox(punkty[0].x2, 0, 1);
   putbox(punkty[1].x2, 0, 2);
   putbox(0, punkty[0].y2, 3);
   square=countsize();
   return square.h*square.w;
}

int type2()
{
   prost square;
   clearpoint();
   putbox(0,0,0);
   putbox(punkty[0].x2, 0, 1);
   putbox(0, punkty[0].y2, 2);
   putbox(punkty[2].x2, (punkty[0].y2<punkty[1].y2?punkty[0].y2:punkty[1].y2), 3);
   square=countsize();
   return square.h*square.w;
}

int type3()
{
   prost square;
   clearpoint();
   putbox(0,0,0);
   putbox(punkty[0].x2, 0, 1);
   putbox(punkty[1].x2, 0, 2);
   putbox(punkty[1].x1, punkty[1].y2, 3);
   square=countsize();
   return square.h*square.w;
}

int type4()
{
   prost square;
   clearpoint();
   putbox(0,0,0);
   putbox(punkty[0].x2, 0, 1);
   putbox(punkty[1].x2, 0, 2);
   putbox(punkty[2].x1, punkty[2].y2, 3);
   square=countsize();
   return square.h*square.w;
}

int area(int type)
{
  int maxh, maxw;
  
  switch(type){
  /*case 0 : maxw=dane[0].w+dane[1].w+dane[2].w+dane[3].w;
           maxh=max(dane[0].h,dane[1].h,dane[2].h,dane[3].h);
		   return maxw*maxh;*/
  case 0 : return type0();
  case 1 : return type1();
  case 2 : return type2();
  case 3 : return type3();
  case 4 : return type4(); 
  }
}

int main(int argc, char* argv[])
{
	int i,j, min,x, a,b,c, d;
	min = 100000000;
	dane2[0].h=8;
	dane2[0].w=3;
	dane2[1].h=5;
	dane2[1].w=7;
	dane2[2].h=3;
	dane2[2].w=7;
	dane2[3].h=5;
	dane2[3].w=4;

/*	dane2[0].h=10;
	dane2[0].w=5;
	dane2[1].h=10;
	dane2[1].w=6;
	dane2[2].h=8;
	dane2[2].w=4;
	dane2[3].h=9;
	dane2[3].w=5;*/

    for(a=0;a<4;a++)
	{
     dane[a]=dane2[0];
     for(b=0;b<4;b++)
	 {
		 if (b!=a)
		 {
			 dane[b]=dane2[1];
			 for(c=0;c<4;c++)
			 {
				if((c!=a)&&(c!=b))
				{
					dane[c]=dane2[2];
					for(d=0;d<4;d++)
					if((d!=a)&&(d!=c)&&(d!=b))
					{   
						dane[d]=dane2[3];

						for(j=0;j<16;j++)
						{
						 if(j!=0)makeNstep(j);
							for(i=0;i<4;i++)
						 {
								if (area(i)<min) {
									min=area(i);
									printf("typ: %d, wynik %d", i, min);
									printf("dane: %d %d \n %d %d \n %d %d \n %d %d \n", dane[0].h, dane[0].w,
																					 dane[1].h, dane[1].w,
																					 dane[2].h, dane[2].w,
																					 dane[3].h, dane[3].w);
									printf("obroty: %d %d %d %d \n", obroty[j].p[0], obroty[j].p[1], obroty[j].p[2], obroty[j].p[3]);

								}
							}
						}

					}
				}
			 }
			}
	 }
	}

	printf("Hello World!\n %d", min);
	return 0;
}

