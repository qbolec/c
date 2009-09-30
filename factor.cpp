#include <iostream.h>
//0x11*0x101*0x10001 = 0x11111111
//0x11*0x101*0x10001*3*5= 0xFFFFFFFF
//17  *257  *65537  *3*5= 0xFFFFFFFF
//
const char bignumlen=5;
char dabignum[bignumlen]={7,3,5,5,6};


//  806515533049393 =86020717*9375829
//const char bignumlen=3;//edit
//char dabignum[bignumlen]={3,4,1};//edit


const char divisorlen=1+(bignumlen>>1);
char divisor[divisorlen];
char todiv[bignumlen+3];
char divby[bignumlen+3];
int cmp(char *a,char *b){
	//compares a b
	//result is to 0 as a is to b
	if(a[0]>b[0])return 1;
	if(a[0]<b[0])return -1;
	for(int i=a[0];i;i--){
		if(a[i]>b[i])return 1;
		if(a[i]<b[i])return -1;
	}
	return 0;
}
void div10(char * a){
	//shifts a one position
	for(int i=1;i<a[0];i++)
		a[i]=a[i+1];
	a[0]--;
}
void substract(char *a,char *b){
	//performs a-=b;
	int i;
	for(i=1;i<=b[0];i++){
		a[i]-=b[i];
		if(a[i]<0){
			a[i+1]--;
			a[i]+=10;
		}
	}
	while((i<=a[0]) && (a[i]<0)){
		a[i]+=10;
		i++;
		a[i]--;
	}
	while(a[0]>0 && (a[ a[0] ]==0))a[0]--;
}
int divide(char * a,int al ,char * b ,int bl){
	//written division a/b - whitout result : only testing the divisibility
	int i;
	for(i=0;i<al;i++)
		todiv[i+1]=a[i];
	todiv[0]=al;
	for(i=0;i<bl;i++)
		divby[i+al-bl+1]=b[i];
	for(i=1;i<=al-bl;i++)
		divby[i]=0;
	divby[0]=al;
	while(1){
		while(cmp(divby,todiv)>0)
			if(divby[0]>bl)div10(divby);
			else return 0;

		while(cmp(todiv,divby)>=0)
			substract(todiv,divby);

		if(todiv[0]==0)return 1;
	}

}
int main(){
	for(int t=2;;t++){
		int c=t;
		int dl=0;
		while(c){
			divisor[dl++]=c%10;
			c/=10;
		}
		if(divide(dabignum,bignumlen,divisor,dl)){
			cout << "Found divisor:" << t;
			return 0;
		}
	}
}

