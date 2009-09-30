#include<iostream.h>
int ok[8]={2,3,5,7,13,17,19,31};
int prime[11]={2,3,5,7,11,13,17,19,23,29,31};
char * perf[100]={"6","28","496","8128","33550336","8589869056","137438691328",
           "2305843008139952128"};
void solve(int n){
	for(int i=0;i<8;i++)
		if(ok[i]==n){
			cout << "Perfect: "<< perf[i] << '!' << endl;
			return;
		}
	for(int i=0;i<11;i++)
		if(prime[i]==n){
			cout << "Given number is prime. But, NO perfect number is available." << endl;
			return;
		}
	cout << "Given number is NOT prime! NO perfect number is available." << endl;
}
int main(){
	while(1){
		int n;
		cin >> n;
		if(n==0)
			return 0;
		solve(n);
	}

}
