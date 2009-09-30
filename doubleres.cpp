#include<iostream.h>
#include<iomanip.h>
int test(double d){
	double n=d+1;
	if(n==d)return 0;
	if(n-d!=1)return 0;
	return 1;
}
double binsearch(double f,double t){
	if(!test(f))
		return f;
	double c=(f+t)/2;
	if(c==f)
		return c;
	if(c==t)
		return c;
	if(test(c)&&(test(c-1)))
		return binsearch(c,t);
	else
		return binsearch(f,c);
}
int main(){
	double d=1;
	while(1){
		if(!test(d)){
			d=binsearch(0,d);
			cout << "Maximal good resolution double is:" << setiosflags(ios::fixed) << d << endl;
			return 0;
		}
		d*=2;
	}
	return 0;
}
