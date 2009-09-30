#include <iostream.h>
int main(int argc,char * args[]){
	cout << "otrzymano " << argc << "parametrów :" << endl;
	for(int i=0;i<argc;i++)
		cout << "parametr :" << i << '[' << args[i] << ']' << endl;
	return 0;
}
