#include<iostream.h>
int main(){
	while(1){
		double cows,cars,show;
		cin >> cows >> cars >> show;
		if(cin.eof())
			return 0;
		double total=cows+cars;
		double igotcar=cars/total;
		double igotcow=cows/total;
		double switchfromcar= (cars-1)/(total-show-1);
		double switchfromcow= (cars)/(total-show-1);
		double chance=igotcar*switchfromcar+igotcow*switchfromcow;
		cout.setf(ios::fixed);
		cout.precision(5);
		cout << chance << endl;
	}
	return 0;
}

