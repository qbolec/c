#include <iostream.h>
struct queue
{
long  v;
queue*n;
int spawned;
};
int spid=0;
queue spawningpool[100];

inline queue * nev()
{
 spid++;
 if(spid==100)spid=0;
 return spawningpool+spid;
}
inline void add(queue * q,long v)
{
 while(1)
 {
  if(q->v==v)return;
  if(q->v<v)
  {
   if(q->n)q=q->n;
   else
   {
    q->n=nev();
    q->n->v=v;
    q->n->n=0;
    return;
   }
  }
  else
  {
   queue * i;
   i=nev();
   *i=*q;
   q->n=i;
   q->v=v;
   return;
  }
 }
}

long g(long t)
{
  long out=t;
  while(t)
  {
    out+= t % 10;
    t/=10;
  }
  return out;
}
int main()
{
  queue*que;
  que=nev();
  que->n=0;
  que->v=1;
  cout<<1<<endl;

  for(long t=1;t<1000001;t++)
  {
    add(que,g(t));
    if(que->v==t)
    {
      que->spawned=0;
      que=que->n;
    }
    else
      cout << t << endl;
  }
  return 0;
}


