#include <stdio.h>
int data[6]={1,1,1,1,10};
void qsort_(unsigned int * from,unsigned int * to,unsigned int mask){
	unsigned int *f=from;
	unsigned int *t=to;
	while( (*t&mask) && (from<=t) )t--;
	while(!(*f&mask) && (f<=to)   )f++;
	if( (f>to) || (t<from) ){
		if(mask!=1)qsort_(from,to,mask>>1);
		return;
	}
	while(f<t){
		{int i=*t;*t=*f;*f=i;}
		t--;f++;
		while( (*t&mask) )t--;
		while(!(*f&mask) )f++;
	}
	if(mask!=1){
		if(from<t)
			qsort_(from,t,mask>>1);
		if(f<to)
			qsort_(f,to,mask>>1);
	}
}
void qsort(unsigned int * tab,int size){
	if(size>1)
		qsort_(tab,tab+(size-1),1<<31);
}
int main(){
	qsort(data,5);
	printf("%d %d %d %d %d",data[0],data[1],data[2],data[3],data[4]);
	return 0;
}
