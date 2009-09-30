#include <iostream.h>
#include <fstream.h>
//#define qin cin
//#define qout cout
ifstream qin("kol.in");
ofstream qout("kol.out");
unsigned long n,m,z,A,B,I,mmx;
unsigned long cox[131073];
unsigned long fox[131073];
unsigned long data[256];
unsigned long * w;
unsigned long * r;
unsigned long speedup[64];
unsigned long * spwrite;

void validate(unsigned long id)
{
unsigned long c1,c2,ii;
tab:if(!id)return;
  ii=id<<1;
  c1=fox[ ii   ]+cox[ ii   ];
  c2=fox[ ii +1]+cox[ ii +1];

  if((c1>=c2) && (c1>fox[id]))
  {
    fox[id]=c1;
    id>>=1;
    goto tab;
  }
  if((c2>=c1) && (c2>fox[id]))
  {
    fox[id]=c2;
    id>>=1;
    goto tab;
  }

}
int posible()
{
spwrite=speedup;
mmx=m-I;
r=data;
w=&data[4];
unsigned long int ed;
unsigned long int st;
unsigned long int up;
unsigned long int id;
while(r!=w)
{
  id=*r++;
  st=*r++;
  ed=*r++;
  up=*r++;
  if((ed>=A)&&(st<=B))
  {
    up+=cox[id];

    if((A<=st)&&(ed<=B))
    {

      if(fox[id] + up > mmx)
        return 0;
      else
        *spwrite++=id;
    }
    else
    {
      unsigned long hp=(st+ed)>>1;
      *w++=(id<<1);
      *w++=st;
      *w++=hp;
      *w++=up;
      *w++=(id<<1)+1;
      *w++=hp+1;
      *w++=ed;
      *w++=up;
    }
  }
}
return 1;
}
inline void oneline()
{
  qin>> A >> B >> I;
  if(I>m)
  {
    qout.put('N');
    qout.put('\n');
    return;
  }
  B--;
  unsigned long * sp;
  if(posible())
  {
    qout.put('T');
    qout.put('\n');
    for(sp=spwrite-1;sp>=speedup;sp--)
      cox[*sp]+=I;

    for(sp=spwrite-1;sp>=speedup;sp--)
      validate(*sp>>1);
  }
  else
  {
    qout.put('N');
    qout.put('\n');
  }
}



int main()
{
  qin >>  n ;
  qin >>  m ;
  qin >>  z ;
data[0]=1;
data[1]=1;
data[2]=n-1;
data[3]=0;
  while(z--)
    oneline();
  return 0;
}

