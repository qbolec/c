#include <iostream.h>
int n;
int kto;
int *stack;
int *last;
int hlp[17]={1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int isprime1plus[17]={0,1,1,0,1,0,1,
0,0,0,1,0,1,0,0,0,1};
int stos[16];
int nx[17][7]=
{
{17},
{2,4,6,10,12,16,17},//1
{3,5,9,11,15,17},//2
{2,4,8,10,14,16,17},//3
{3,7,9,13,15,17},//4
{2,6,8,12,14,17},//5
{5,7,11,13,17},//6
{4,6,10,12,16,17},//7
{3,5,9,11,15,17},//8
{2,4,8,10,14,17},//9
{3,7,9,13,17},//10
{2,6,8,12,17},//11
{5,7,11,17},//12
{4,6,10,16,17},//13
{3,5,9,15,17},//14
{2,4,8,14,16,17},//15
{3,7,13,15,17},//16
};

void it()
{
  if(stack==last)
  {
    if(isprime1plus[*stack])
    {
      for(stack=stos;stack<last;stack++)
        {cout << *stack ;cout.put(' ');}
      cout << *stack << endl;
    }
    return;
  }
  int * p;
  int * help;
  p=*(nx+*stack);
  while(*p<=n)
  {
    help=hlp+*p;
    if(*help)
    {
      *++stack=*p;
      *help=0;
        it();
      *help=1;
      stack--;
    }
    p++;
  }
}




int main()
{
 cin>>n;
 int li=1;
 while(!cin.eof())
 {
  cout<<"Case "<<li++<<":"<<endl;
  stack=stos;
  last=stos+n-1;
  *stack=1;
  it();
  cin>>n;
  if(!cin.eof())cout<<endl;

 }
 return 0;
}
 

