/*
	ta klas ma pomoc wykrywac niezainicjowane zmienne.
	plan dzialania jest taki, ze w swoim programie robisz np:
	#define double init_guarded_double
	a potem implementujesz funkcjê void init_guarded_double::init_error()
*/
const double avoid_value=1337.1337;
#define act_as_double(op)double operator op(double v){if(value==avoid_value)init_error();return value op v;}
struct init_guarded_double{
	double value;
	void init_error();
	init_guarded_double():value(avoid_value){}
	init_guarded_double(double v):value(v){}
	operator double(){
		if(value==avoid_value)
			init_error();
		return value;
	}
	act_as_double(+=)
	act_as_double(-=)
	act_as_double(/=)
	act_as_double(*=)
};
#include<iostream.h>
void init_guarded_double::init_error(){
	cout <<"BLAD"<<endl;
}
#define double init_guarded_double
double a,b;
#undef double
#define double double
double x,y;
void main(){
	cout << a << endl;
	cout << x << endl;
}
