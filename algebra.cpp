#include<iostream.h>
int deg(int x,int z){
	int d=0;
	int r=x;
	while(r!=1){
		d++;
		r*=x;
		r%=z;
	}
	return d;
}
int main(){
	for(int i=1;i<23;i++)
		if(deg(i,23)>20)
			cout << i << "has deg:" << deg(i,23) << endl;
	return 0;
}
