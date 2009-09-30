#include <fstream.h>
ifstream qin("zam.in");
ofstream qout("zam.out");
struct lista
{
  lista * ne;
  int    va;
};
struct vertex
{
  lista * sa;
  int  cena;
};
vertex dane[100];
char tab[101][1001];
int n,m,w,k,s;
int stack[1001];
int *smtp=stack;
int dfs()
{
   if(s==0)
   {
     if(*smtp==k)return 1;
     else return 0;
   }
   if(s<0) return 0;
   if(tab[*smtp][s]) return 0;
   tab[*smtp][s]=1;
   lista * ptr=dane[*smtp].sa;
   while(ptr)
   {
     *++smtp = ptr->va;
     s-=dane[*smtp].cena;
     if(dfs()) return 1;
     s+=dane[*smtp].cena;
     --smtp;
     ptr=ptr->ne;
   }
   return 0;
}
void addnode(int a,int b)
{
  lista * ptr =dane[a].sa;
  dane[a].sa=new lista;
  dane[a].sa->ne=ptr;
  dane[a].sa->va=b;
}
void loaddata()
{
  qin>>n>>m>>w>>k>>s;
  for(int i=1;i<=n;i++)
    qin>> dane[i].cena;
  for(int i=0;i<m;i++)
  {
     int a,b;
     qin >> a >> b;
     addnode(a,b);
     addnode(b,a);
  }
  
}
int main()
{
  loaddata();
  *smtp=w;
  s-= dane[w].cena;
  dfs();
  for(int * st=stack;st<=smtp;st++)
    qout << *st << " ";
}