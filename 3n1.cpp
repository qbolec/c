#include <iostream.h>
int mo[10001];
int moc;
struct stacz
            {
             long       co;
             stacz *    ne;
             int        mo;
            };
stacz * first;
stacz * last;

void que(long what,int moves)
{
 last->ne=new stacz;
 last->co=what;
 last->mo=moves;
 last=last->ne;
}

stacz pobiez()
{
stacz out=*first;
first=first->ne;
return out;
}

int fillbroot(int w)
{
 if(w<=10000)
 {
  if(mo[w]!=0)return mo[w];
 };


  int o;

  if(w%2==0)
     o= fillbroot(w/2)+1;
  else
     o= fillbroot(w*3+1)+1;

 if(w<=10000)
 {
  mo[w]=o;
 }
     return o;

}

void main()
{
stacz a;
   first=new stacz;
   last=first;
   que(1,1);
   while((first!=last) && (moc!=10001))
   {
      a=pobiez();
      if(a.co>2000000) continue;
      if(a.co<=10000)
      {
       mo[a.co]=a.mo;
       moc++;
      };
      que(a.co*2,a.mo+1);

      if((a.co>4) && (a.co % 2==0) &&(a.co % 3== 1))
               que( (a.co-1)/3 , a.mo+1);
   }

if(moc!=10001)
{
  for(int m=1;m<=10000;m++)
  if(mo[m]==0)
  {
   fillbroot(m);
  }
}

cout << "const int helptab[10001]={"  ;
for(int i=0;i<=10000;i++)
{
 cout << mo[i] << ",";
 if(i%10==0) cout << "\n";
}
cout << "};";
}
