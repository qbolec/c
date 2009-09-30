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
int main(){
        cout << "Program dziala jak kalkulator[tworzac na swoje potrzeby kod w notacji onp]"<<endl ;
        cout << "Prosze wpisac wyrazenie, np. (2+3)*7-1 albo (3*(-6)-3):7"<<endl;
        cout << "[ujemne w nawiasach,max 9 cyfr na liczbe, zadnych spacji!]"<<endl;
        cin >> math;
        convert();
        cout << endl << "w onp wyglada to tak:" << endl<< output << endl ;
        cout << math << '=' << count();
        return 0;
}


