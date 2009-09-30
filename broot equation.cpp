// Conversion of std to polish notation
// by qbolec2002

#include <iostream.h>

char math[256];
char output[256];
char stax[256];
double regs[256];
double lrange[256];
double hrange[256];
double srange[256];
char * matt;
char * stack;
char * outt;

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

void convert(char * math,char * output)
{
        matt=math;
        outt=output;
        stack=stax;
        *stack='(';

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
         *outt++=show();
         *stack = *matt;
        };
        break;
   case '(':
        *++stack=*matt;
        break;
   case ')':

        while(*stack!='(')
        {*outt++= *stack;stack--;};
        stack--;

        break;
   default :
        *outt++=*matt;
        regs[*matt]=-1;
        break;


  };
 matt++;
 }
 while(stack!=stax-1)
 {
  if(*stack!='(') *outt++=*stack;
  stack--;
 };

}

void setranges()
{
        for(char i=0;i<256;i++)
        {
         if(regs[i]==-1)
         {
          cout << "\nsetranges for variable " << i << " lowest,step,highest :";
          cin >> lrange[i] >> srange[i] >> hrange[i];
         }
        }
}
void brootwar()
{

}
int main()
{
        cout << "Fast linear std function to polish syntax convertion\n" ;
        cin >> math;
        convert(math,output);
        setranges();
        brootwar();
        cout << output << endl;

        return 0;
}


