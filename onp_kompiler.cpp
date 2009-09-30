// Conversion of std to polish notation
// by qbolec2002 [10.01.2003]

#include <iostream.h>
char math[256];
char * matt=math;
char stax[256]="(";
char * stack=stax;
double dstax[256];
double * dstack=dstax;
char output[256];
char * outt=output;
void drop(char a){
	*++stack=a;
}
void dropval(double v){
    *++dstack=v;
}
char pick(){
	return *stack--;
}
double pickval(){
	return *dstack--;
}
char show(){
	return *stack;
}
void foo_add_out(char a){
	*outt++=a;
}
void flush(){
	while(*stack!='(')
		foo_add_out(*stack--);
	stack--;
}
int staxrux(char m,char s){
	if(m==':')return 0;
	if(s==':')return 1;
	if(m=='*')return 0;
	if(s=='*')return 1;
	if(m=='-')return 0;
	if(s=='-')return 1;
	if(m=='+')return 0;
	if(s=='+')return 1;
	return 0;
}
void convert(){
	int minus=0;
	while(*matt){
		switch(*matt){
   		case '-':
			if(minus==0){
				foo_add_out('0');
				foo_add_out(' ');
			}
   		case '+':
   		case '*':
   		case ':':
   			while(staxrux(*matt,show()))
   				foo_add_out(pick());
        	drop(*matt++);
			minus=0;
        break;case ')':
        	flush();
			minus=1;
			matt++;
		break;case '(':
        	drop('(');
			minus=0;
 			matt++;
		break;default:
			while(('0'<=*matt)&&(*matt<='9'))
				foo_add_out(*matt++);
			foo_add_out(' ');
			minus=1;
		}
 	}
	while(stack>stax-1)
		flush();
}
double count(){
	double a,b;
	char * comm=output;
	while(comm<outt){
		switch(*comm){
		case '-':
			a=pickval();
			b=pickval();
			dropval(b-a);
   		break;case '+':
   			a=pickval();
   			b=pickval();
   			dropval(b+a);
   		break;case '*':
   			a=pickval();
   			b=pickval();
   			dropval(b*a);
   		break;case ':':
   			a=pickval();
   			b=pickval();
   			dropval(b/a);
   		break;default:
			a=0;
			while(*comm!=' '){
				a*=10;
				a+=*comm++-'0';
			}
			dropval(a);
		}
		comm++;
	}
	return dstax[1];
}
void toasm(){
	char * comm=output;
	while(comm<outt){
		switch(*comm){
		case '-':
			cout << "pop edx"<<endl;
			cout << "pop eax"<<endl;
			cout << "sub eax,edx"<<endl;
			cout << "push eax"<<endl;
		break;case '+':
   			cout << "pop edx"<<endl;
			cout << "pop eax"<<endl;
			cout << "add eax,edx"<<endl;
			cout << "push eax"<<endl;
		break;case '*':
   			cout << "pop eax"<<endl;
			cout << "pop edx"<<endl;
			cout << "imul edx"<<endl;
			cout << "push eax"<<endl;
		break;case ':':
   			cout << "pop ebx"<<endl;
			cout << "pop eax"<<endl;
   			cout << "cdq"<<endl;
			cout << "idiv ebx"<<endl;
			cout << "push eax"<<endl;
		break;default:
			long a=0;
			while(*comm!=' '){
				a*=10;
				a+=*comm++-'0';
			}
			cout << "push.l "<<a<<endl;
		}
		comm++;
	}
}
void optasm(){
	long lastpush=0;//0=eax,1=stala
	long a=0;
	char * comm=output;
	while(comm<outt){
		switch(*comm){
		case '-':
			if(lastpush)cout << "mov edx,"<<a<<endl;
			else cout << "mov edx,eax"<<endl;
			cout << "pop eax"<<endl;
			cout << "sub eax,edx"<<endl;
			lastpush=0;
		break;case '+':
   			if(lastpush)cout << "mov eax,"<<a<<endl;
			cout << "pop edx"<<endl;
			cout << "add eax,edx"<<endl;
			lastpush=0;
		break;case '*':
			if(lastpush)cout << "mov eax,"<<a<<endl;
			cout << "pop edx"<<endl;
			cout << "imul edx"<<endl;
			lastpush=0;
		break;case ':':
			if(lastpush)cout << "mov ebx,"<<a<<endl;
			else cout << "mov ebx,eax"<<endl;
			cout << "pop eax"<<endl;
   			cout << "cdq"<<endl;
			cout << "idiv ebx"<<endl;
			lastpush=0;
		break;default:
			if(comm!=output){
				if(lastpush)cout << "push.l " << a << endl;
				else cout << "push eax" << endl;
			}
			a=0;
			while(*comm!=' '){
				a*=10;
				a+=*comm++-'0';
			}
			lastpush=1;
		}
		comm++;
	}
	if(lastpush)cout << "mov eax," << a << endl;
}
void optmaxasm(){
	/*
	idea:
	wszystkie operacje zapisujemy tak aby dzialaly  eax= eax OP ebx
	te ktore sie da zapisujemy tez jako eax= ebx OP eax
	te ktore sie da zapisujemy tez w wersji ebx= eax OP ebx
	te ktore sie da zapisujemy tez w wersji ebx= ebx OP eax
	*/


}

int main(){
        cout << "Prosze wpisac wyrazenie, np. (2+3)*7-1 albo (3*(-6)-3):7"<<endl;
        cin >> math;
        convert();
        cout << endl << "w onp wyglada to tak:" << endl<< output << endl ;
        cout << endl << "w asm[arytmetyka calkowitoliczbowa]wyglada to tak:" << endl;
        toasm();
        cout << "(wynik zostaje na stosie)" << endl;
        cout << endl << "w nieco zoptymalizowanym asm, wyglada to tak:" << endl;
        optasm();
        cout << "(wynik zostaje w eax)"<<endl;
        cout << endl <<  math << '=' << count();

        return 0;
}


