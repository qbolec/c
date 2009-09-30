#include <iostream.h>
#include <stdlib.h>
struct litera{char a;char hlp;};
int difrent       ;
char stos[11]     ;
char * stack      ;
char * zero       ;
litera info[11]   ;
char st[11]       ;
int compare(const void * a,const void * b)
{
  if(*(char *)a <*(char *)b)
     return -1;
  else
     return 1;
}
void gopermute()
{
  if(stack==zero)
  {
    *zero=0;
    cout << stos << endl;
  }

  else
    for(char p=0;p<difrent;p++)
    {
      if(info[p].hlp)
      {
       info[p].hlp--;
       *stack++=info[p].a;
       gopermute();
       info[p].hlp++;
      }
    }

  stack--;
}

void one()
{
 register int i;
 //-clear-//
  difrent=0;
  for(int i=0;i<11;i++)
    info[i].a=0;
  zero=stack=stos;
 //-wczytaj-//
 cin >> st;
 char * pt;
 //-analizuj-//
 pt=st;
 while(*pt)
 {
   zero++;
   for(i=0;i<difrent;i++)
     if(info[i].a==*pt)
       {info[i].hlp++;break;};
   if(i==difrent)
     {info[difrent].hlp=1;info[difrent++].a=*pt;};
   pt++;
 }
  qsort(info,difrent,2,compare);
  gopermute();
}

int main()
{
  long n;
  cin>> n;
  while(n--)
  {
  one();
  cout << endl;
  }

}

