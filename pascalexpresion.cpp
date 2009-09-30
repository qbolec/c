//----------------------[some strinx.h fooz]
#define DIE(a) {cout << a << endl;return 0;}
#include <iostream.h>
#include <ctype.h>
void lowercase(char *c){
	while(*c)
		*c++=tolower(*c);	
}
//================[for evaluation]
//----------------[Value is basic class for NumValue, BoolValue, and is used to stack them together]
class Value{
public:
	virtual int  isNum(){return 1;}
	virtual int  getValue()=0;
};
//----------------[NumValue is a result of arithmetic operations stored onto stack]
class NumValue: public Value{
	int num;
public:
	int getValue(){return num;}
	NumValue(int n){num=n;}
};
//----------------[BoolValue is a result of logical operations stored inside tha stack]
class BoolValue: public Value{
	int istrue;
public:
	int isNum(){return 0;}
	int getValue(){return istrue;}
	BoolValue(int t){istrue=t;}
};
//================[for lexer]
//----------------[Token is basic class for all other gramar parts of language]
class Token{
public:
	Value virtual * getValue(Value * args[])=0;
	int virtual getArity(){return 2;}
	int virtual inPriority()=0;
	int virtual outPriority(){return inPriority()^1;}
};
class Atomic:public Token{
public:
	int getArity(){return 0;}
	int inPriority(){return 10;}
	int outPriority(){return 10;}
};
class LeftBracket:public Token{
public:
	Value * getValue(Value * args[]){return args[0];}
	int getArity(){return 1;}//trick by qbolec2003
	int inPriority(){return 0;}
	int outPriority(){return 10;}
};
class RightBracket:public Token{
public:
	Value * getValue(Value * args[]){return args[0];}
	int getArity(){return 1;}//trick by qbolec2003
	int inPriority(){return 10;}
	int outPriority(){return 0;}
};
class LowPriorityUnary:public Token{
public:
	int getArity(){return 1;}
	int inPriority(){return 5;}
	int outPriority(){return 10;}
};
class HyperPriorityUnary:public Token{
public:
  	int getArity(){return 1;}
  	int inPriority(){return 8;}
};
class HighPriority:public Token{
public:
	int inPriority(){return 7;}
};
class MiddlePriority:public Token{
public:
  	int inPriority(){return 5;}
};
class LowPriority:public Token{
public:
  	int inPriority(){return 3;}
};

//----------------[ATOMIC:Number represents literals such as 123 or 0]
class Number: public Atomic{
	int num;
public:
	Value * getValue(Value * args[]){return new NumValue(num);}
	Number(int n){num=n;}
};
//----------------[ATOMIC:Bool represents 'true' or 'false' literal]
class Bool: public Atomic{
	int istrue;
public:
	Value * getValue(Value * args[]){return new BoolValue(istrue);}
	Bool(int t){istrue=t;}
};
//----------------[OTHER TOKENS:]
class Multiply: public HighPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new NumValue(args[0]->getValue()*args[1]->getValue());
		else
			return 0;
	}
};
class Divide: public HighPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum()&&args[1]->getValue())
			return new NumValue(args[0]->getValue()/args[1]->getValue());
		else
			return 0;
	}
};
class Modulo: public HighPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum()&&args[1]->getValue())
			return new NumValue(args[0]->getValue()%args[1]->getValue());
		else
			return 0;
	}
};
class Add: public MiddlePriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new NumValue(args[0]->getValue()+args[1]->getValue());
		else
			return 0;
	}
};
class Substract: public MiddlePriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new NumValue(args[0]->getValue()-args[1]->getValue());
		else
			return 0;
	}
};
class Smaller: public LowPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new BoolValue(args[0]->getValue()<args[1]->getValue());
		else
			return 0;
	}
};
class Bigger: public LowPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new BoolValue(args[0]->getValue()>args[1]->getValue());
		else
			return 0;
	}
};
class Equal: public LowPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new BoolValue(args[0]->getValue()==args[1]->getValue());
		else
			return 0;
	}
};
class Inequal: public LowPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new BoolValue(args[0]->getValue()!=args[1]->getValue());
		else
			return 0;
	}
};
class SmallerEqual: public LowPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new BoolValue(args[0]->getValue()<=args[1]->getValue());
		else
			return 0;
	}
};
class BiggerEqual: public LowPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()&&args[1]->isNum())
			return new BoolValue(args[0]->getValue()>=args[1]->getValue());
		else
			return 0;
	}
};
class And: public HighPriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()||args[1]->isNum())
			return 0;
		else
			return new BoolValue(args[0]->getValue()&&args[1]->getValue());
	}
};
class Or: public MiddlePriority{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum()||args[1]->isNum())
			return 0;
		else
			return new BoolValue(args[0]->getValue()||args[1]->getValue());
	}
};
class Not: public HyperPriorityUnary{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum())
			return 0;
		else
			return new BoolValue(!args[0]->getValue());
	}
};
class Negation: public LowPriorityUnary{
public:
	Value * getValue(Value * args[]){
		if(args[0]->isNum())
			return new NumValue(-args[0]->getValue());
		else
			return 0;
	}
};
//----------------------[MAIN:]
int main(){
	char exp[1024];
	cout << "exp>" ;
	cin.getline(exp,1024);
	lowercase(exp);
	char * e=exp;
	Token * onpstack[1024];
	Value * valstack[1024];
	int onpsc=0;
	int valsc=0;
	while(*e){
		Token * tk=0;
		switch(*e++){
		case ' ':case '\t':case '\n':case '\r':case '\f'://ignoring spaces
		break;case '0'://special case for 0,  012 is illegal
			if(isdigit(*e))
				DIE("Leading zeros illegal in numeric constants, wykrzaczam")
			else
				tk= new Number(0);
		break;case 't':
			if(e[0]=='r'&&e[1]=='u'&&e[2]=='e'){
				tk= new Bool(1);
				e+=3;
			}else
				DIE("unrecognized text [expected 'true'] at : t"<< e)
		break;case 'f':
			if(e[0]=='a'&&e[1]=='l'&&e[2]=='s'&&e[3]=='e'){
				tk= new Bool(0);
				e+=4;
			}else
				DIE("unrecognized text [expected 'false'] at : f"<< e)
		break;case '+':
			tk= new Add();
		break;case '*':
			tk= new Multiply();
		break;case 'd':
			if(e[0]=='i'&&e[1]=='v'){
				tk= new Divide();
				e+=2;
			}else
				DIE("unrecognized text [expected 'div'] at : d"<< e)
		break;case '-':
			if(onpsc)
				if(onpstack[onpsc]->getArity()==2)
					DIE("found - after binary operator, zieff...")
				else if(onpstack[onpsc]->getArity()==0)
					tk= new Substract();
				else if(onpstack[onpsc]->outPriority())					
					tk= new Negation();
				else
					tk= new Substract();
			else
				tk= new Negation();
		break;case 'm':
			if(e[0]=='o'&&e[1]=='d'){
				tk= new Modulo();
				e+=2;
			}else
				DIE("unrecognized text [expected 'mod'] at : m"<< e)
		break;case '<':
			if(e[0]=='='){
				tk= new SmallerEqual();
				e++;
			}else if(e[0]=='>'){
				tk= new Inequal();
				e++;
			}else
				tk= new Smaller();
		break;case '>':
			if(e[0]=='='){
				tk= new BiggerEqual();
				e++;
			}else
				tk= new Bigger();
        break;case '=':
        	tk= new Equal();
		break;case 'a':
			if(e[0]=='n'&&e[1]=='d'){
				tk= new And();
				e+=2;
			}else
				DIE("unrecognized text [expected 'and'] at : a"<< e)
		break;case 'o':
			if(e[0]=='r'){
				tk= new Or();
				e++;
			}else
				DIE("unrecognized text [expected 'or'] at : o"<< e)
		break;case 'n':
			if(e[0]=='o'&&e[1]=='t'){
				tk= new Not();
				e+=2;
			}else
				DIE("unrecognized text [expected 'not'] at : n"<< e)
		break;case '(':
			tk=new LeftBracket();
		break;case ')':
			tk=new RightBracket();
		break;case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			e--;
			int v;
			v=0;
			while(isdigit(*e)){
				v*=10;
				v+=(*e++)-'0';
			}
			tk= new Number(v);
		break;default:
			DIE("unrecognized text at:" << (e-1))
		}
		if(tk){
			while(onpsc&&(onpstack[onpsc]->inPriority()>tk->outPriority())){
				//sciagamy ze stosu ONP i od razu sciagamy parametry itd i wrzucamy na stos wartosci.
				if(0>=(valsc-=onpstack[onpsc]->getArity()-1))
					DIE("Stack under flow [sprawdz arnosci], wybijam")
				if(!(valstack[valsc]=onpstack[onpsc]->getValue(valstack+valsc)))
					DIE("Typ miszmasz, jebudu")
				onpsc--;
			}
			if(onpsc){
				if(tk->outPriority()!=onpstack[onpsc]->inPriority())
					onpstack[++onpsc]=tk;
				else if(tk->outPriority())
					DIE("Syntax era, are you normal or not?")
				else 
					onpstack[onpsc]=tk;//right bracket
			}else if(tk->outPriority())
				onpstack[++onpsc]=tk;
			else
				DIE("Unbalanced Right Bracket, z rownowagi wytroncon")			
		}
	}
	while(onpsc){
		if(onpstack[onpsc]->inPriority()){
			if(0>=(valsc-=onpstack[onpsc]->getArity()-1))
				DIE("Stack under flow [sprawdz arnosci], wybijam")
			if(!(valstack[valsc]=onpstack[onpsc]->getValue(valstack+valsc)))
				DIE("Typ miszmasz, jebudu")
			onpsc--;
		}else
			DIE("Unbalanced Left Bracket, z rownowagi wytroncon")			
	}
	if(valsc!=1)
		DIE("Failed to find result!");
	if(valstack[1]->isNum())
		cout << "Value: " << valstack[1]->getValue() << " as Integer";
	else
		if(valstack[1]->getValue())
			cout << "Value: True as Boolean";
		else
			cout << "Value: False as Boolean";
	return 0;
}
