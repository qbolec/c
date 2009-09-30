#include <iostream.h>
int value[256];
char vars[256];
int varsc=0;
class boolexp{
public:
	int virtual getValue()=0;
	int virtual getArity(){return 2;}
	int virtual inPriority()=0;
	void virtual setArgs(boolexp * args[]){}
	int outPriority(){return inPriority()^1;}
};
class and:public boolexp{
public:
	boolexp * left;
	boolexp * right;
	int getValue(){return (left->getValue())?right->getValue():0;}
	int inPriority(){return 5;}
	void setArgs(boolexp * args[]){
		left=args[0];
		right=args[1];
	}
};
class or:public boolexp{
public:
	boolexp * left;
	boolexp * right;
	int getValue(){return (left->getValue())?1:right->getValue();}
	int inPriority(){return 3;}
	void setArgs(boolexp * args[]){
		left=args[0];
		right=args[1];
	}
};
class imp:public boolexp{
public:
	boolexp * left;
	boolexp * right;
	int getValue(){return (left->getValue())?right->getValue():1;}
	int inPriority(){return 0;}
	void setArgs(boolexp * args[]){
		left=args[0];
		right=args[1];
	}
};
class iff:public boolexp{
public:
	boolexp * left;
	boolexp * right;
	int getValue(){return (left->getValue()==right->getValue())?1:0;}
	int inPriority(){return 0;}
	void setArgs(boolexp * args[]){
		left=args[0];
		right=args[1];
	}
};
class not:public boolexp{
public:
	boolexp * right;
	int getValue(){return !right->getValue();}
	void setArgs(boolexp * args[]){right=args[0];}
	int inPriority(){return 7;}
	int getArity(){return 1;}
};
class variable:public boolexp{
public:
	char v;
	int getValue(){return value[v];}
	int inPriority(){return 9;}
	int getArity(){return 0;}
	variable(char w){v=w;}
};
class truth:public boolexp{
public:
	int getValue(){return 1;}
	int getArity(){return 0;}
	int inPriority(){return 9;}
};
class lay:public boolexp{
public:
	int getValue(){return 0;}
	int getArity(){return 0;}
	int inPriority(){return 9;}
};
class something:public boolexp{
private:
	boolexp * root;
public:
	int getValue(){return root->getValue();}
	int getArity(){return 0;}
	int inPriority(){return 9;}
	something(char *& exp){
		boolexp * be[1024];
		int bec=0;
		while(*exp){
			switch(*exp++){
			case 'T':
				be[bec++]=new truth;
			break;case 'F':
				be[bec++]=new lay;
			break;case '!':case '~'://both negations
				be[bec++]=new not;
			break;case '|':
				if(*exp=='|')exp++;//C++ style?
				be[bec++]=new or;
			break;case '&':
				if(*exp=='&')exp++;//C++ style?
				be[bec++]=new and;
			break;case ' ':case '\t':case '\r':case '\n'://eat whites nigga'
			break;case '<':
				if((exp[0]=='=')&&(exp[1]=='>')){
					be[bec++]=new iff;
					exp+=2;
				}else{
					cout << "too abitious:" << (exp-1);
					return ;
				}
			break;case '=':
				if(exp[0]=='>'){
					be[bec++]=new imp;
					exp++;
				}else{
					cout << "too abitious:" << (exp-1);
					return ;
				}
			break;case '(':
				be[bec++]=new something(exp);
			break;case ')':
				goto outside;
			break;default:
				be[bec++]=new variable(exp[-1]);
			}
		}
		outside:
		boolexp * stack[1024];
		boolexp * onp[1024];
		int oc=0;
		int sc=-1;
        for(int t=0;t<bec;t++){
			while((sc>=0) &&( stack[sc]->inPriority()>be[t]->outPriority()))
  				onp[oc++]=stack[sc--];
			stack[++sc]=be[t];
        }
        while(sc>=0)
        	onp[oc++]=stack[sc--];
        for(int t=0;t<oc;t++){
        	sc-=onp[t]->getArity()-1;
        	onp[t]->setArgs(stack+sc);
        	stack[sc]=onp[t];
        }
        root=stack[0];
	}
};
int main(){
	cout<<"Formua!Dzie jes formua?"<<endl;
	char * exp=new char[1024];
	cin>>exp;
	for(int i=0;exp[i];i++)
		if((exp[i]<='z')&&(exp[i]>='a'))
			if(!value[i]){
				value[i]=1;
				vars[varsc++]=exp[i];
			}
	something st(exp);
	if(varsc){
		int sat=0;
		for(int mask=(1<<varsc)-1;mask>=0;mask--){
			for(int i=0,m=mask;i<varsc;i++,m>>=1)
				value[vars[i]]=m&1;
			if(st.getValue())
				sat++;
		}
    	if(sat==0)
	    	cout<<"Formua'es sprzeczna"<< endl;
	    else if(sat==(1<<varsc))
    		cout<<"Formua'es tautologiom"<<endl;
    	else
	    	cout<<"Formua'es speunialna"<<endl;
	}else
		cout << "To nie'es formua ale ... " << (st.getValue()?"TRUE":"FALSE");
	return 0;
}

