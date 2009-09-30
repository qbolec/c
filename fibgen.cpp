#include <iostream.h>
int main(){
	unsigned long n=1;
	unsigned long fn=1;
	unsigned long fnn=1;
	while(n!=2147483646){
		fn+=fnn;
		fnn=fn-fnn;
		n++;
	}
	cout << fn;

	return 0;
}
