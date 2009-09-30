/*
	This is EMU LISP written by qbolec2003
	It does nothing...
	It works in conversation mode...
 */
#include <iostream.h>
#include <string.h>
#include <ctype.h>
const int HEAP_SIZE=0x10000;
const int ATOM_TEXT_SPACE_SIZE=0x800;
char atomtextspace[ATOM_TEXT_SPACE_SIZE];
int atompos=0;
char wordbuff[256];
class thing{
public:
	union{
		char * atom;//pointer to text of atom
		thing * left;
	};
	thing * right;//also known as next,also used to determine wether is an atom or not
	char needed;
	void iNeddYou();
	int isAtom();
    thing * eval();
    void show(ostream & s);
	thing(istream & s,int asmuchasyoucan=0);//creates a thing from source file
	thing(thing * l,thing * r);//creates a thing consoliding two other thinx
	thing(char * t);//creates atomic thing from its name
	thing();
};
thing heap[HEAP_SIZE];
int heapused=0;//for statistics
thing * keepalive=0;//main handle
inline void garbagecollector(){
	int i;
	cout << endl << "(:garbage::collector::" << HEAP_SIZE << "::" << heapused << "::";	
	for(i=0;i<HEAP_SIZE;i++)
		if(heap[i].needed<2)
			heap[i].needed=0;
	keepalive->iNeddYou();
	for(i=0;i<HEAP_SIZE;i++)
		if(heap[i].needed==2)
			heap[i].iNeddYou();	
	heapused=0;
	for(i=0;i<HEAP_SIZE;i++)
		if(heap[i].needed)
			heapused++;
	cout << heapused << ')' << endl;	
}
inline char * createstring(int size){
	if(size+atompos>=ATOM_TEXT_SPACE_SIZE)
		throw("Out of memory - TWO MANY ATOMS");
	int ret=atompos;
	atompos+=size;
	return atomtextspace+ret;
}
inline thing * create(const thing & suchas){
	static int last=0;
	while((last<HEAP_SIZE) && heap[last].needed)last++;
	if(last==HEAP_SIZE){
		garbagecollector();		
		for(last=0;(last<HEAP_SIZE) && heap[last].needed;last++);
		if(last==HEAP_SIZE)
			throw("Out of memory - HEAP IS FULL");		
	}
	heap[last]=suchas;
	heap[last].needed=1;
	heapused++;
	return heap+last;
}
inline void resetmemory(){
	atompos=0;
	if(keepalive)
		while(!keepalive->isAtom())
			keepalive=keepalive->right;
	else
		keepalive=create(thing("NIL"));
	garbagecollector();
}
inline void lock(thing * what){
	what->needed=2;
}
inline void unlock(thing * what){
	what->needed=1;
}
inline void link(char * atom,thing * what){
	lock(what);
	thing * name=create(thing(atom));
	lock(name);
	thing * pair=create(thing(name,what));
	lock(pair);
	keepalive=create(thing(pair,keepalive));
	unlock(what);
	unlock(name);
	unlock(pair);
}
inline void unlink(int amount){
	while(amount--)
		keepalive=keepalive->right;
}
inline thing * getlink(char * atom){
	for(thing * p=keepalive;!p->isAtom();p=p->right)
		if(!strcmp(p->left->left->atom,atom))
			return p->left->right;
	return 0;
}
inline thing * call(thing * foo,thing * args){
	int varcnt=0;
	if(foo->isAtom())
		throw("Not-a-function called");
	if(!foo->left->isAtom())
		throw("Not-a-function called");		
	if(strcmp(foo->left->atom,"LAMBDA"))
		throw("Not-a-function called");
	if(foo->right->isAtom())
		throw("Argument list missing after LAMBDA");
	if(foo->right->left->isAtom())
		throw("Argument list missing after LAMBDA");
	for(thing * varnam=foo->right->left;!varnam->isAtom();varnam=varnam->right,args=args->right){
		if(args->isAtom())
			throw("Too few arguments supplied for function call");
		if(!varnam->left->isAtom())
			throw("Unexpected list inside argument list");
		link(varnam->left->atom,args->left->eval());
		varcnt++;
	}
	if(!args->isAtom())
		throw("Too many arguments supplied for function call");
	if(foo->right->right->isAtom())
		throw("Body of LAMBDA missing");
	thing * tmp=foo->right->right->left->eval();
	unlink(varcnt);
	return tmp;
}
void thing::iNeddYou(){
	if(needed==1)
		return;
	needed=1;
	if(isAtom())
		return;
	left->iNeddYou();
	right->iNeddYou();
}
void thing::show(ostream & s){
	if(isAtom()){
		s << atom ;
	}else{
		s << '(';
		left->show(s);
		s << '.';
		right->show(s);
		s << ')';
	}
}
inline int thing::isAtom(){
	//return (right==0);
	if(right)
		return 0;
	return 1;
}
inline thing::thing(){
	needed=0;
}
inline thing::thing(char * t){
	right=0;
	atom=t;
}
inline thing::thing(thing * l,thing * r){
	left=l;
	right=r;
}
thing::thing(istream & s,int asmuchasyoucan){
	char a;
	s >> a;
	if(!asmuchasyoucan){
		if(a=='('){	 
			*this = thing(s,1);
		}else if(isalnum(a)){		
			right=0;
			int i=0;
			while(isalnum(a)){
				wordbuff[i++]=a;
				s.get(a);
			}
			s.putback(a);
			wordbuff[i]=0;
			atom=createstring(i+1);
			strcpy(atom,wordbuff);
		}else
			throw("Syntax error");		
	}else{//as much as you can
		if(a==')'){
			atom="NIL";
			right=0;
		}else if(a=='.'){
			*this=thing(s);
			s>>a;
			if(a!=')')
				throw("Syntax error");
		}else{
			s.putback(a);
			left=create(thing(s));
			right=create(thing(s,1));
		}
	}
}
thing * thing::eval(){
	if(isAtom()){
		if(!getlink(atom))
			throw("Cannot Evaluate ATOM [possible reason: unbound variable]");
		return getlink(atom);
	}
	if(left->isAtom()){
		if(!strcmp(left->atom,"CAR"))
			if(right->isAtom())
				throw("Cannot perform CAR on ATOM");
			else{
				thing * tmp=right->left->eval();
				if(tmp->isAtom())
					throw("Cannot perform CAR due to ATOMIC result of argument");
				return tmp->left;
			}
		if(!strcmp(left->atom,"CDR"))
			if(right->isAtom())
				throw("Cannot perform CDR on ATOM");
			else{
				thing * tmp=right->left->eval();
				if(tmp->isAtom())
					throw("Cannot perform CDR due to ATOMIC result of argument");
				return tmp->right;
			}
		if(!strcmp(left->atom,"CONS")){
			if(right->isAtom())
				throw("Not enought arguments for CONS");
			if(right->right->isAtom())
				throw("Not enought arguments for CONS");
			thing * tmp1=right->left->eval();
			link("(ARG)",tmp1);
			thing * tmp2=right->right->left->eval();
			link("(ARG)",tmp2);
			thing * tmp=create(thing(tmp1,tmp2));
			unlink(2);
			return tmp;
		}
        if(!strcmp(left->atom,"QUOTE")){
        	if(right->isAtom())
        		throw("No argument for QUOTE");
        	return right->left;
        }
        if(!strcmp(left->atom,"ATOM")){
        	if(right->isAtom())
        		throw("No argument for ATOM");
        	thing * tmp=right->left->eval();
        	if(tmp->isAtom())
        		return create(thing("T"));
        	else
        		return create(thing("F"));
        }
        if(!strcmp(left->atom,"EQ")){
        	if(right->isAtom())
        		throw("No argument for EQ");
        	if(right->right->isAtom())
        		throw("Not enought arguments for EQ");
        	thing * tmp1=right->left->eval();
			link("(ARG)",tmp1);
			thing * tmp2=right->right->left->eval();
			unlink(1);			
			if(!tmp1->isAtom()||!tmp2->isAtom())
				throw("EQ needs ATOMic arguments");
			if(!strcmp(tmp1->atom,tmp2->atom))
				return create(thing("T"));
			else
				return create(thing("F"));
        }
        if(!strcmp(left->atom,"COND")){
        	for(thing * c=right;c;c=c->right){
        		if(c->isAtom())
        			throw("Failed to find proper COND condition");
        		if(c->left->isAtom())
        			throw("Not good COND syntax [expected LIST, found an ATOM]");
        		thing * tmp=c->left->left->eval();
        		if(tmp->isAtom() && !strcmp(tmp->atom,"T"))
        			return c->left->right->left->eval();
        	}
        }
        //not a known string ... so... must be a function name;D
        if(!getlink(left->atom))
        	throw("Undefined function name OR Unexpected ATOM at TOPLEVEL");
		return call(getlink(left->atom),right);
	}else{
		//list - must be a function definition
		//we expect only LABEL or LAMBDA
		if(!left->left->isAtom())
			throw("Expected LAMBDA or LABEL - found another list");
		if(!strcmp(left->left->atom,"LABEL")){
			if(left->right->isAtom())
				throw("Expected function name");
			if(left->right->right->isAtom())
				throw("Couldn't find body of function after LABEL");
			if(!left->right->left->isAtom())
				throw("Expected function name - found list");
			link(left->right->left->atom,left->right->right->left);
			thing * tmp=call(left->right->right->left,right);
			unlink(1);
			return tmp;
		}
		if(strcmp(left->left->atom,"LAMBDA"))
        	throw("Expected LAMBDA or LABEL");
		return call(left,right);
	}
}
int main(){
	cout << "(:emu::lisp::written::by::qbolec::2003:)";
	while(1){
		atompos=0;
		cout << endl << "(:enter::expression:)" << endl;
        try{
			thing * exp=create( thing(cin));
			link("(EXP)",exp);
			cout <<"(:understood::evaluating:)"<< endl;
			thing * result=exp->eval();
			cout << "(:got::result:)"<<endl;
			result->show(cout);
			unlink(1);
		}catch(char * run_time_error){
			cout << run_time_error;
			resetmemory();
		}
	}
}


