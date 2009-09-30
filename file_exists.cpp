#include<fstream>
#include<iostream>
using namespace std;
int main(){
	cout << "Podaj nazwe pliku";
	char nazwa[245];
	cin >> nazwa;
	ifstream test(nazwa,ios::in|ios::bin);
	if(test.good())
		cout << "Plik istnieje";
	else
		cout << "Plik nie istnieje";
	if(test)
		cout << "TEST OK" ;
	else
		cout << "TEST nie OK";
	return 0;
}
