// Conversion of std to polish notation
// by qbolec2002

#include <iostream.h>

char math[256];
char output[256];
char stax[256];
char * matt;
char * stack;
char * outt;

void drop(char a)
{     *++stack=a;}

void pick()
{     stack--;}


char show()
{     return *stack;}

void foo_add_out(char a)
{     *outt++=a;}


void flush()
{
 while(*stack!='('){ foo_add_out(*stack);stack--;};
 stack--;
}


long firstcomesfirst(char a,char b)
{
 if(b=='(')return 1;
 if(b=='^')return 0;
 if(a=='^')return 1;
 if(b==':')return 0;
 if(a==':')return 1;
 if(b=='*')return 0;
 if(a=='*')return 1;
 if(b=='-')return 0;
 if(a=='-')return 1;
 if(b=='+')return 0;
 if(a=='+')return 1;
}

void convert()
{
 while(*matt)
 {
  switch(*matt)
  {
   case '-':
   case '+':
   case '*':
   case ':':
   case '^':
        if(firstcomesfirst(*matt,show()))drop(*matt);
        else
        {
         foo_add_out(show());
         pick();
         drop(*matt);
        };
        break;
   case '(':
        drop(*matt);
        break;
   case ')':
        flush();
        break;
   default :
        foo_add_out(*matt);
        break;

  };
 matt++;
 }
 while(stack!=stax-1)
  flush();
}


int main()
{
        cout << "Fast linear std function to polish syntax convertion\n" ;
        cin >> math;

        matt=math;
        outt=output;
        stack=stax;
        *stack='(';

        convert();
        cout << output << endl;

        return 0;
}


