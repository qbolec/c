#include<iostream.h>
int primes[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int kappa[25];
void addfantom(int k){
	for(int i=0;(i<25) && (k>1); i++)
		while((k%primes[i])==0){
			kappa[i]++;
			k/=primes[i];
		}
}
int subfantom(int k){
	for(int i=0;(i<25) && (k>1); i++)
		while((k%primes[i])==0){
			kappa[i]--;
			k/=primes[i];
		}
	for(int i=0;i<25;i++)
		if(kappa[i]<0)
			return 0;
	return 1;
}

int main(){
	while(1){
		int n,d;
		cin >> n >> d;
		if(!n&&!d)
			break;
		for(int i=0;i<25;i++)
			kappa[i]=0;
		for(int i=2;i<=n;i++)
			addfantom(i);
		if(d<0)
			d=-d;
		if(subfantom(d)){
			double s=1;
			cout.setf(ios::fixed);
			cout.precision(0);
			for(int i=0;i<25;i++)
				if(kappa[i])
					s*= (1+kappa[i]);
			cout << s << endl;
		}else{
			cout << 0 << endl;
		}
	}
	return 0;
}

