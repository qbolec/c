#include<iostream>
#include<cmath>

using namespace std;
int main(){
	int a=13;
	int c=312;
	cin >> c;
	for(int i=0;i!=0xFFFFFF;i++)
		c*=sqrt(a+c);
	cout << c << endl;
	return 0;
}
