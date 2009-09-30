#include <iostream.h>
#include <stdlib.h>
char st[11]       ;
char * last;
int compare(const void * a,const void * b)
{
  return (*(char *)a-*(char *)b);
}

void one()
{

  cin >> st;
  last=st;
  while(*last++);
  last-=2;
  qsort (st,last-st+1,1, compare);

  while(1)
  {
    cout << st << endl;
    char * maly;
    char * duzy;
    char biggest=0;
    maly=last;

    label:
    if(*maly>=biggest)
    {
      biggest=*maly;
      maly--;
      if(maly<st)break;
      else goto label;
    }
    else
    {
      //duzy to najmniejszy z wiekszych od maly
      //i najbardziej na prawo z takich
      duzy=last;
      while(*duzy<=*maly)duzy--;
      //teraz duzy wskazuje na dobra wartosc ale...
      while(*(duzy-1)==*duzy)duzy--;
      //swap
      biggest=*duzy;
      *duzy=*maly;
      *maly=biggest;
      qsort(maly+1,last-maly,1,compare);
    }

  }


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

