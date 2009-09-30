#include <iostream.h>
int n;
int kto;
int * stoskto;
int stos[17]={0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
int isprime[33]={0,0,1,1,0,1,0,1,0,0,0,1,0,
1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0};
int hlp[17]={1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int main()
{

 cin>>n;
 int li=1;
 while(!cin.eof())
 {
  cout<<"Case "<<li++<<":"<<endl;

  kto=2;
  stoskto=stos+2;
  labor:

    *stoskto+=2;
    if(*stoskto>n)
    {
      *stoskto=kto&1;
      kto--;
      hlp[*(--stoskto)]=1;
      if(kto==1)goto harbor;

    }
    else
    {
      if(*(hlp+*stoskto)&& *(isprime+(*stoskto+*(stoskto-1))))
      {
        if(kto==n)
        {
          if(*(isprime+(*stoskto)+1))
          {
            for(int * k=stos+1;k<stoskto;k++)
            {
              cout<<*k<< " ";
            }
            cout<< stos[n] << endl;
          }
        }
        else
        {
          kto++;
          hlp[*(stoskto++)]=0;
        }
      }
    }
  goto labor;

  harbor:
  cin>>n;
  if(!cin.eof())cout<<endl;

 }
 return 0;
}
 

