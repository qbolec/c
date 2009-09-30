#include<iostream.h>
int pasc(int n,int k){
	if(n<k)return 0;
	if(n==k)return 1;
	if(k<0)return 0;
	if(k==0)return 1;
	return pasc(n-1,k-1)+pasc(n-1,k);
}
int q(int n){
	int s=0;
	for(int k=0;(k<<1)<=n;k++)
		if(k&1)
			s-=pasc(n-k,k);
		else
			s+=pasc(n-k,k);
	return s;
}
int fun(int a,int b){
	int s=0;
	for(int k=-a;k<=a;k++)
		if(k&1)
			s-=pasc(a+b,a+k)*pasc(b+a,b+k);
		else
			s+=pasc(a+b,a+k)*pasc(b+a,b+k);
	return s;
}
int main(){

	while(1){
	int a,b;
	cin >> a >> b;
	cout << pasc(a+b,a) << '=' << fun(a,b) << endl;
	}
	return 0;
}
