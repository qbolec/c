#include <iostream.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip.h>

struct vec{
           double x;
           double y;
           };


vec axisx={1,0},axisy={0,1},orin,turtle;
double ang=0;
double scx=1;
double scy=1;

int bgbr=0;

const double DEG_TO_RAD=0.0174532925199433;

double Q_cos(double angle)
{
 return cos(angle * DEG_TO_RAD);
}
double Q_sin(double angle)
{
 return sin(angle * DEG_TO_RAD);
}


void POST_rotate(double number)
{
 ang-=number;
 while(ang<0)
 {
  ang+=360;
 };
 while(ang>=360)
 {
  ang-=360;
 };
 axisx.x= Q_cos(ang)*scx;
 axisx.y=-Q_sin(ang)*scx;

 axisy.x= Q_sin(ang)*scy;
 axisy.y= Q_cos(ang)*scy;

}

void POST_translate(double numberx,double numbery)
{
 orin.x+= axisx.x*numberx + axisy.x*numbery;
 orin.y+= axisx.y*numberx + axisy.y*numbery;
}

void POST_scale(double numberx,double numbery)
{
 scx*=numberx;
 scy*=numbery;

 axisx.x= Q_cos(ang)*scx;
 axisx.y=-Q_sin(ang)*scx;

 axisy.x= Q_sin(ang)*scy;
 axisy.y= Q_cos(ang)*scy;
}

void POST_moveto(double numberx,double numbery)
{
 turtle.x= orin.x + axisx.x*numberx + axisy.x*numbery;
 turtle.y= orin.y + axisx.y*numberx + axisy.y*numbery;

 if(bgbr) cout << endl;
 bgbr=1;
 cout << turtle.x << " " << turtle.y << " moveto";
}


void POST_rmoveto(double numberx,double numbery)
{
 vec rm;
 rm.x=axisx.x*numberx + axisy.x*numbery;
 rm.y=axisx.y*numberx + axisy.y*numbery;
 turtle.x+=  rm.x;
 turtle.y+=  rm.y;

 if(bgbr) cout << endl;
 bgbr=1;
 cout << rm.x << " " << rm.y << " rmoveto";
}

void POST_lineto(double numberx,double numbery)
{

 turtle.x= orin.x + axisx.x*numberx + axisy.x*numbery;
 turtle.y= orin.y + axisx.y*numberx + axisy.y*numbery;

 if(bgbr) cout << endl;
 bgbr=1;
 cout << turtle.x << " " << turtle.y << " lineto" ;
}

void POST_rlineto(double numberx,double numbery)
{
 vec rm;
 rm.x=axisx.x*numberx + axisy.x*numbery;
 rm.y=axisx.y*numberx + axisy.y*numbery;
 turtle.x+=  rm.x;
 turtle.y+=  rm.y;

 if(bgbr) cout << endl;
 bgbr=1;

 cout << rm.x << " " << rm.y << " rlineto" ;
}


int line(char * r)
{
 char a;
 int out=-1;
 cin.get(a);
 while((a!='\n') && (!cin.eof()))
 {
  r[++out]=a;
  cin.get(a) ;
 };
#ifdef ONLINE_JUDGE
 cin.get(a);//still there is one more char(10)
#endif
 r[++out]=0;
 return out;
}

int xcut(char * r,char tok[][100])
{
 int out=-1;
 int ins=0;

 while(*r!=0)
 {
 out++;
 ins=0;
  while(*r!=' ' && *r!=0)
  {
   tok[out][ins]=*r;
   ins++;
   r++;
  }
 if(*r==' ')r++;
 tok[out][ins]=0;
 }
 return out+1;
}

int know(char * instruction)
{
if(strcmp(instruction,"moveto")==0)return 1;
if(strcmp(instruction,"rmoveto")==0)return 2;
if(strcmp(instruction,"lineto")==0)return 3;
if(strcmp(instruction,"rlineto")==0)return 4;
if(strcmp(instruction,"scale")==0)return 5;
if(strcmp(instruction,"translate")==0)return 6;
return 0;
}

void make(double arg1,double arg2,int instruction)
{
 switch(instruction)
 {
  case(1):
  POST_moveto(arg1,arg2);
  break;
  case(2):
  POST_rmoveto(arg1,arg2);
  break;
  case(3):
  POST_lineto(arg1,arg2);
  break;
  case(4):
  POST_rlineto(arg1,arg2);
  break;
  case(5):
  POST_scale(arg1,arg2);
  break;
  case(6):
  POST_translate(arg1,arg2);
  break;


 }
}

int main()
{
cout << setiosflags(ios::fixed);
cout.precision(4);

double arg1,arg2;

int d,t,k;

char inn[100];
char tok[100][100];

 while(!cin.eof())
 {
    d=line(inn);
    t=xcut(inn,&tok[0]);

    if(*inn=='*')return 0;

    switch(t)
    {
        case(2):
             arg1=atof(tok[0]);
             if(strcmp(tok[1],"rotate")==0)POST_rotate(arg1);
        break;

        case(3):
        if(k=know(tok[2]))
        {
         arg1=atof(tok[0]);
         arg2=atof(tok[1]);
         make(arg1,arg2,k);
        };
        break;
    };

 }
}



