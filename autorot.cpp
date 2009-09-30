#include<iostream.h>
typedef unsigned int uint;
uint rotate(uint what,uint amount){
	return (what<<amount)|(what>>(32-amount));
}
uint collide(uint a,uint b){
	return (rotate(31,a)&rotate(31,b))&(rotate(a,a)^rotate(b,b));
}
uint ones(uint n){
	uint o=0;
	while(n){
		n&=n-1;
		o++;
	}
	return o;
}
uint choosen[33];
uint mask[33]={0};
uint count=0;
uint total=0;
void subsets(){
	if(count&1)
		total+=1<<(32-ones(mask[count]));
	else
		total-=1<<(32-ones(mask[count]));
	uint from=count?choosen[count-1]+1:0;
	for(int i=from;i<32;i++){
		if(count&&(collide(choosen[count-1],i)||collide(choosen[0],i)))
			continue;
		choosen[count++]=i;
		mask[count]=mask[count-1]^rotate(31,i);
		subsets();
		count--;
	}
}
int main(){
	subsets();
	cout << total << endl;
	return 0;
}
