// sortnextgen.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "memory.h"
#include "stdlib.h"

#define ILE 2200

#define SWAP(a__, b__) {int c__=*b__;*b__=*a__;*a__=c__;}
#define SORT2(a, b) {if(*a>*b)SWAP(a,b);}
#define SORT3(a,b,c) {SORT2(a,b);if(*b>*c){SWAP(b,c);SORT2(a,b);};}

#define aa (from)
#define bb (from+1)
#define cc (from+2)
#define dd (from+3)
#define ee (from+4)

int tab[ILE]={0, 45543, 433, -44543, 444, 665566665, 56, -566, -66, 0, 5555};	

void combinesort(int * from,int * to);
void mergesort(int * from,int * to);

void sort4(int *from)
{
 if(*aa>*bb)SWAP(aa,bb);
 if(*cc<*dd)SWAP(cc,dd);
 if(*bb>*cc){SWAP(bb,cc);SWAP(aa,dd);};
 SWAP(dd,ee);
 if(*dd>*bb)
 {
   if(*dd<*cc)SWAP(dd,cc);
 }
 else
 {
   if(*dd<*aa){SWAP(dd,cc);SWAP(cc,bb);SWAP(aa,bb);}
   else {SWAP(dd,cc);SWAP(cc,bb);}
 }
}

void sort5(int *from)
{
 if(*aa>*bb)SWAP(aa,bb);
 if(*cc<*dd)SWAP(cc,dd);
 if(*bb>*cc){SWAP(bb,cc);SWAP(aa,dd);};
 SWAP(dd,ee);
 if(*dd>*bb)
 {
   if(*dd<*cc)SWAP(dd,cc);
 }
 else
 {
   if(*dd<*aa){SWAP(dd,cc);SWAP(cc,bb);SWAP(aa,bb);}
   else {SWAP(dd,cc);SWAP(cc,bb);}
 }
 if(*ee>*bb)
 {
   if(*ee<*cc){SWAP(ee,dd); SWAP(dd,cc)}
   else {SWAP(ee,dd);}  
 }
 else
 {
   if(*ee<*aa){SWAP(ee,dd);SWAP(dd,cc);SWAP(cc,bb);SWAP(aa,bb);}
   else {SWAP(ee,dd);SWAP(dd,cc);SWAP(cc,bb);}
 }
}

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
	int s=to-from+1;
	int tmp[1024];
	int *A=from;
	int *B=tmp;
	int b, bbb;
	int c;
	int * f;
	int * t;
	c=s/5;
	for(f=from;c--;f+=5)
		sort5(f);
	if(f<to)combinesort(f,to);
	for(b=5;b<s;b=bbb){
		bbb=b<<1;
		c=s/bbb;
		for(f=A,t=B;c--;f+=bbb,t+=bbb)
			merge(f,b,f+b,b,t);
		if(A+s-f-b>0)
			merge(f,b,f+b,A+s-f-b,t);
		else
			memcpy(t,f,(A+s-f)<<2);
		{int *swp=A;A=B;B=swp;}
	}
	if(A==tmp)
		memcpy(B,A,s<<2);
}

void quicksort(int * from,int * to){
	int * f=from;
	int * t=to;
	int * c=f+((t-f)>>1);
	SORT2(f,c)
	SORT2(c,t);
	SORT2(f,c);
	int p=*c;
	while(1){
		while(*f<p)f++;
		while(*t>p)t--;
		SWAP(f,t);
		if(f>=t)break;		
		f++;
		t--;
	}
	combinesort(from,t);
	combinesort(t+1,to);
}
void combinesort(int * from,int * to){
	if(to<=from)return;
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

int main(int argc, char* argv[])
{
	int i;
	int *w;
    for (w = tab + ILE - 1; w > tab; w--) {
        *w = rand ();
    }

	//for(int i=0;i<size;i++)
	//	printf("%d ",tab[i]);
	combinesort(tab, tab+ILE-1);
	for(i=1;i<ILE;i++)if(tab[i]<tab[i-1])
		printf("error");
	return 0;
}

