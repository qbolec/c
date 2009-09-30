#include <fstream.h>
//#define qin cin
//#define qout cout
ifstream qin("kol.in");
ofstream qout("kol.out");
unsigned long n,m,z,A,B,I,mmx;
unsigned long cox[131073];
unsigned long fox[131073];
unsigned long speedup[44];
unsigned long * spwrite;
void validate(unsigned long id)
{
  if(!id)return;
  unsigned long c1,c2,ii=id<<1;
  c1=fox[ ii   ]+cox[ ii   ];
  c2=fox[ ii +1]+cox[ ii +1];

  if((c1>=c2) && (c1>fox[id]))
  {
    fox[id]=c1;
    validate(id>>1);
    return;
  }
  if((c2>=c1) && (c2>fox[id]))
  {
    fox[id]=c2;
    validate(id>>1);
    return;
  }

}
int posible(unsigned long id,unsigned long st,unsigned long ed,unsigned long up)
{

  if((ed<A)||(st>B) )return 1;

  up+=cox[id];

  if((A<=st)&&(ed<=B))
  {

    if(fox[id] + up > mmx)return 0;
    else
    {

      *spwrite++=id;
      return 1;
    }
  }
  else
  {
    unsigned long hp=(st+ed)>>1;
    if( posible(id<<1,st,hp,up) && posible((id<<1)+1,hp+1,ed,up))
      return 1;
    else
      return 0;
  }


}
inline void oneline()
{
  qin>> A >> B >> I;
  if(I>m)
  {
    qout.put('N');
    qout << endl;
    return;
  }
  B--;
  spwrite=speedup;
  mmx=m-I;
  unsigned long * sp;
  if(posible(1,1,n-1,0))
  {
    qout.put('T');
    qout << endl;
    for(sp=spwrite-1;sp>=speedup;sp--)
      cox[*sp]+=I;

    for(sp=spwrite-1;sp>=speedup;sp--)
      validate(*sp>>1);
  }
  else
  {
    qout.put('N');
    qout<< endl;
  }
}



int main()
{
  qin >> n >> m >> z;
  while(z--)
    oneline();
  return 0;

}
/*
unsigned int pow2(unsigned int x)
{
  unsigned int o=1;
  while(o<x)o=o<<1;
  return o;
}

void inittable()
{
//lisci bedzie n-1
//nie zmienia to faktu ze wysokosc
//drzewa bedzie taka jak potegi 2
//nie mniejszej niz n-2
//stad lisci bedzie pow2(n-1)
//potrzba im jednak jeszcze korzeni
//to kolejne pow2(n-1) -1
//oraz pomijanego przez nas cox[0]
//w sumie dokladnie:
  l=pow2(n-1)*2;

  cox=new unsigned int[l];
  fox=new unsigned int[l];
  for(unsigned int x=0;x<l;x++)
    fox[x]=cox[x]=0;

}
*/

