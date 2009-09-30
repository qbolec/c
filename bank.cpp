#include <iostream.h>
#include <stdlib.h>

struct check{ unsigned char data[9];
              unsigned long value;
            };
check checkbook[10000];
int listofchecks[10000];
int qbelectab[10000];
int checkcount=0;
int color=0;
inline void entrar()
{
        unsigned char a;
        cin.get(a);
        while(a!=10)cin.get(a);
}
int compare(const void * a,const void * b)
{
  return *(int *)a - *(int *)b;
}
inline void blit8(unsigned char * a,unsigned char * b)
{
  while(*a++=*b++);
}
void qbelec()
{
  color++;
  for(int i=0;i<checkcount;i++)
    qbelectab[listofchecks[i]]=color;
  int * p;
  p=listofchecks;
  for(int i=0;i<10000;i++)
    if(qbelectab[i]==color)
      *p++=i;
}
void outcheck(int id)
{
  int   n=listofchecks[id];
  check c=checkbook[n];

  if(n<1000)cout.put(' ');
  if(n<100)cout.put(' ');
  if(n<10)cout.put(' ');
  cout << n;

  if(id && (listofchecks[id-1]+1!=listofchecks[id]))
      cout.put('*');
  else
      cout.put(' ');


  long up  =c.value / 100;
  long down=c.value % 100;
  cout.put(' ');
  if(up<100000)cout.put(' ');
  if(up<10000)cout.put(' ');
  if(up<1000)cout.put(' ');
  if(up<100)cout.put(' ');
  if(up<10)cout.put(' ');
  cout << up << "." << (down/10) << (down % 10);
  cout.put(' ');

  cout << c.data;
}
void solve()
{
  unsigned char stringhelp[9];
  int checkidhelp;
  double valuehelp;
  checkcount=0;
  cin.get(*stringhelp);//ch or 10
  while((*stringhelp!=10) && (!cin.eof()))
  {
    cin >> (stringhelp+1);
    cin >> checkidhelp;

    blit8(checkbook[checkidhelp].data,stringhelp);

    cin >> valuehelp;
    valuehelp*=100;
    checkbook[checkidhelp].value=valuehelp;

    listofchecks[checkcount++]=checkidhelp;
    entrar();            //      '\10' or eof
    cin.get(*stringhelp);//ch or '\10' or eof
  }

  if(checkcount<500)qsort(listofchecks,checkcount,sizeof(int),compare);
  else qbelec();

  int columnA,columnB,columnC;
  columnA=(checkcount+2)/3;
  if(columnA<=(checkcount-columnA))
    columnB=columnA;
  else
    columnB=(checkcount-columnA);
  columnC=checkcount-columnA-columnB;
  for(int i=0;i<columnA;i++)
  {
    outcheck(i);
    if(i<columnB)
    {
      cout << "   ";
      outcheck(i+columnA);
      if(i<columnC)
      {
        cout << "   ";
        outcheck(i+columnA+columnB);
      }
    }
    cout << endl;
  }
}
int main()
{
int testcount;
cin >> testcount;
entrar();
entrar();
while(testcount--)
{
  solve();
  if(testcount)cout << endl;
}
}
