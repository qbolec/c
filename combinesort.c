#define SWAP(a, b) {int c=*b;*b=*a;*a=c;}
#define SORT2(a,b) {if(*a>*b)SWAP(a,b)}
#define SORT3(a,b,c) {SORT2(a,b);if(*b>*c){SWAP(b,c);SORT2(a,b);}}
#define SORT4(a,b,c,d) {SORT2(a,b);SORT2(c,d);SORT2(a,c);SORT2(b,d);SORT2(b,c);}

void merge(int * a,int as,int * b,int bs,int * d){
	while(1){
		if(*a<*b){
			*d++=*a++;
			if(--as==0){
				memcpy(d,b,bs<<2);
				return;
			}
		}else{
			*d++=*b++;
			if(--bs==0){
				memcpy(d,a,as<<2);
				return;
			}
		}
	}
}
void mergesort(int * from,int * to){
	int s=from-to+1;
	int tmp[1024];
	int *A=from;
	int *B=tmp;
	int b;
	int bb;
	int c;
	int * f;
	int * t;
	c=s/5;
	for(f=from;c--;f+=5);/*sort5(f);*/
	if(f<to)combinesort(f,to);

	for(b=5;b<s;b++){
		bb=b<<1;
		c=s/bb;
		for(f=A,t=B;c--;f+=bb,t+=bb)
			merge(f,b,f+b,b,t);
		if(A+s-f-b>0)
			merge(f,b,f+b,A+s-f-b,t)
		else
			memcpy(t,f,(A+s-f)<<2)
		{int *swp=A;A=B;B=swp;}
	}
	if(B==tmp)
		memcpy(A,B,s<<2)
}
void quicksort(int * from,int * to){
	int * f=from;
	int * t=to;
	int * c=f+((t-f)>>1);
	SORT2(f,c);
	SORT2(c,t);
	SORT2(f,c);
	int p=*c;
	while(1){
		while(*f<p)f++;
		while(*t>p)t--;
		if(f>=t)break;
		SWAP(f,t);
		f++;
		t--;
	}
	combinesort(from,t);
	combinesort(t+1,to);
}
void combinesort(int * from,int * to){
	if(to>=from)return;
	switch(to-from){
	case 1:SORT2(from,to);return;
	case 2:SORT3((from+1),from,to);return;
	case 3:sort4(from);return;
	case 4:sort5(from);return;
	default:
		if(to-from<1024){
			mergesort(from,to);
			return;
		}else quicksort(from,to);
	}
}
