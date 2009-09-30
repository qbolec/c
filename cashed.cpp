#include<iostream.h>
class cashed{
public:
	int	values[100][100];
	int (* myfoo)(cashed & c,int n,int k);
	int operator ()(int n,int k){
		if(values[n][k]==-1)
			return values[n][k]=myfoo(*this,n,k);
		else
			return values[n][k];
	}
	cashed(int (* foo)(cashed & c,int n,int k)){
		myfoo=foo;
		for(int n=0;n<100;n++)
			for(int k=0;k<100;k++)
				values[n][k]=-1;
	}
};
int newton_foo(cashed & c,int n,int k){
	if(n<0)return 0;
	if(k==0)return 1;
	if(k>n)return 0;
	return c(n-1,k-1)+c(n-1,k);
}
int cycles_foo(cashed & c,int n,int k){
	if(n<0)return 0;
	if(n==k)return 1;
	if(k==0)return 0;
	if(k>n)return 0;
	return c(n-1,k-1)+(n-1)*c(n-1,k);
}
int sets_foo(cashed & c,int n,int k){
	if(n<0)return 0;
	if(n==k)return 1;
	if(k==0)return 0;
	if(k>n)return 0;
	return c(n-1,k-1)+k*c(n-1,k);
}
int partitions_foo(cashed & c,int n,int k){
	if(n<0)return 0;
	if(n<k)return 0;
	if(k==0)return 0;
	if(k==n)return 1;
	if(k==1)return 1;
	return c(n-1,k-1)+c(n-k,k);
}
cashed newton( newton_foo );
cashed cycles( cycles_foo );
cashed sets( sets_foo );
cashed partitions( partitions_foo );
int main(){
	while(1){
		int n,k;
		cin >> n >> k;
		cout << "Newton:" << newton(n,k) << " Cycles:" << cycles(n,k) << " Sets:" << sets(n,k) << " Partitions:" << partitions(n,k) << endl;
	}
	return 0;
}
