#include <iostream.h>
int main(int argc,char * args[]){
	cout << "otrzymano " << argc << "parametr�w :" << endl;
	for(int i=0;i<argc;i++)
		cout << "parametr :" << i << '[' << args[i] << ']' << endl;
	return 0;
}
