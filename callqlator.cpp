#include <iostream.h>
/*
 * PROBLEM : w pierwszym wierszu podana jest ilosc zmiennych i ilosc danych
             w drugim wierszu napisane wyrazenie na zmiennych [a..z]
             w nastepnych podane sa podstawienia
             podac wyniki
 */


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
int regcount;
int nrequest;
char * zeropointer;
double regs[30];//niech strace :)
struct graphmember{
                   graphmember * operandA;
                   graphmember * operandB;
                   char operationTYPE;//'a'-'z' is register '+' '-' ':' '*'
                  };

double getvalue(graphmember * ofwho)
{
if( ofwho->operationTYPE<='z' && ofwho->operationTYPE>='a' )
    return regs[ofwho->operationTYPE-'a'];
 switch(ofwho->operationTYPE)
 {
  case '+':return getvalue(ofwho->operandA)+getvalue(ofwho->operandB);
  case '-':return getvalue(ofwho->operandA)-getvalue(ofwho->operandB);
  case ':':return getvalue(ofwho->operandA)/getvalue(ofwho->operandB);
  case '*':return getvalue(ofwho->operandA)*getvalue(ofwho->operandB);
 }
 return 0;
}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
char priority(char a)
{
 if(a=='^')return 4 ;
 if(a=='*' || a==':')return 3;
 if(a=='+' || a=='-')return 2;
 return 0;
}

int firstismoreimportand(char a,char b)
{
 a=priority(a);
 b=priority(b);
 if(a>b)return 1;
 if(a==b)return 0;
 if(b<a)return -1;
}

graphmember * graphfromstring(char * math,graphmember * uplink,graphmember * korzen)
{

if(math>=zeropointer)
{
 uplink->operationTYPE='+';
 uplink->operandB=new graphmember;
 uplink->operandB->operationTYPE=0;
 return korzen;
}
 /*
   idea :
   you've got an uplink with set left branch
   nothing more is importand
   you also get a pointer to txt pointing the operator '*' '+' .etc
   you have to return uplink or lower
 */


 graphmember * newuplink;
 graphmember * newkorzen;
 uplink->operationTYPE=*math;
 uplink->operandB=new graphmember;

 //posibility no 1: pointed operation is more importand then another

 if((
 *(math+1)!='(' && firstismoreimportand(*math ,*(math+2)))
 || *(math+2)==')')
                   {

                   uplink->operandB->operationTYPE=*math+1;
                   newuplink=new graphmember;
                   newuplink->operandA=korzen;
                   if(*(math+2)==')')math++;
                   newkorzen=newuplink;
                   return graphfromstring(math+2,newuplink,newkorzen);
                   }
 //posibility no 2: we must w8 with operation until right is done

 if(*(math+1)=='(' || firstismoreimportand(*(math+2),*math))
 {
                if(*(math+1)=='(')math++;
                newkorzen=korzen;
                newuplink=uplink->operandB;
                newuplink->operandA=new graphmember;
                newuplink->operandA->operationTYPE=*(math+1);
                if(*(math+2)==')')math++;
                return graphfromstring(math+2,newuplink,newkorzen);
 }

 //posibility no 3: we must pomp a:b up becouse a:b*c = (a:b) * c
 uplink->operandA->operandA=new graphmember;
 uplink->operandA->operandA->operationTYPE=uplink->operandA->operationTYPE;
 uplink->operandA->operationTYPE=uplink->operationTYPE;
 uplink->operationTYPE=0;//it was unvalid
 uplink->operandA->operandB=new graphmember;
 uplink->operandA->operandB->operationTYPE=*(math+1);
 newuplink=uplink;
 newkorzen=korzen;
 if(*(math+2)==')')math++;
 return graphfromstring(math+2,newuplink,newkorzen);

}
void op2op(char * op2,char * op)
{
 if(*op2!='-')*op++='+';
 while(*op2)
 {
        if(*op2!=' ')*op++=*op2;
        op2++;
 }
 *op=0;
 zeropointer=op;
}
int main()
{
 cin >> regcount;
 cin >> nrequest;
 char opis[1000];
 char opis2[1000];
 cin >> opis2;
 op2op(opis2,opis);

graphmember * initial;
initial=new graphmember;
initial->operandA=new graphmember;
initial->operandA->operationTYPE=0;//null, just null nothing more or less

graphmember * basis;
basis=graphfromstring(opis,initial,initial);

for(int tim=0;tim<nrequest;tim++)
{
        for(int i=0;i<regcount;i++)
                cin >> regs[i];

   cout << "Vynick : " <<   getvalue(basis);
}

}
