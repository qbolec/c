#include <fstream.h>
//#define qin cin
//#define qout cout
ifstream qin("kom.in");
ofstream qout("kom.out");

//struct
struct list
{
  int       va;
  list *    ne;
};
struct vertex
{
   int       I,L,O;
   list *       sa;
   int     sacount;//children after cr8tion
   int       elder;

};
//globs;
vertex v[30003];//v[0] unused
int korzen;
int id3;
int a;
int b;
int n;//miasta
int m;//wazne miasta
int z;//zapytania
int e;//eldrfaktor
int sq(int x)
{
  int out=0;
  int add=1;
  int quad=0;
  while(quad<x)
  {
    out++;
    quad+=add;
    add+=2;
  }
  return out;
}
int includes(int x,int y)
{
  if(v[y].I>=v[x].I && v[y].I<=v[x].O)return 1;
  else return 0;
}
void addedge(int x,int y)
{
  list * nexus;
  nexus = new list;
  nexus->ne=v[x].sa;
  nexus->va=y;
  v[x].sa=nexus;
  v[x].sacount++;
}
void lukeimyourfather(int you,int fat,int lev)
{
  v[you].L=lev;
  v[you].I=id3++;
  list * p;
  p=v[you].sa;
  if(you!=korzen)v[you].sacount--;//father is not a child
  for(int i=0;i<v[you].sacount;i++)
  {
    if(fat==p->va)
    {
      p->va=p->ne->va;
      p->ne=p->ne->ne;
    }
    lukeimyourfather(p->va,you,lev+1);
    p=p->ne;
  }
  v[you].O=id3-1;
}
void cr8graph()
{
   qin >> n;
   for(int i=1;i<n;i++)//n-1 razy
   {
     int x,y;
     qin>>x>>y;
     addedge(x,y);
     addedge(y,x);
   }
}
void cr8tree()
{
  korzen=1;//masz lepszy (szybszy) pomysl
  id3=0;
  lukeimyourfather(korzen,0,0);
}
void setelder(int you,int eld,int q)
{
  v[you].elder=eld;
  list * p;
  p=v[you].sa;

  if((q%e)==0)
  {
    if(v[you].sacount>1)
    {
      eld=you;
      q++;
    }
  }
  else
    q++;
  for(int i=0;i<v[you].sacount;i++)
  {
    setelder(p->va,eld,q);
    p=p->ne;
  }

}
void cr8elders()
{
  for(int i=1;i<=n;i++)
    if(v[i].L>e)
      e=v[i].L;

  e=sq(e);

  setelder(korzen,0,0);
}
int ycross(int id )
{
  list * p;
  p=v[id].sa;
  for(int i=0;i<v[id].sacount;i++)
  {

    if( includes( p->va , a ) )
    {
      if( includes( p->va , b))
        return ycross(p->va);
      else
        return v[a].L+v[b].L- (2*v[id].L);
    }

    p=p->ne;
  }


}
int distant()
{
   if( includes( a , b) ) return v[b].L-v[a].L;
   if( includes( b , a) ) return v[a].L-v[b].L;
   int id;
   if(v[b].L<v[a].L)
   {
     id=b;
     while( includes( id, a) == 0 )
     {
        id=v[id].elder;
     }
   }
   else
   {
     id=a;
     while( includes( id, b) == 0 )
     {
        id=v[id].elder;
     }
   }

   return ycross(id);

}
void process()
{
  int s=0;
  qin >> m;
  b=1;

  while(m--)
  {
    a=b;
    qin>> b;
    s+= distant();
  }
  qout<< s;
}
int main()
{
  cr8graph();
  cr8tree();
  cr8elders();
  process();
  return 0;
}


