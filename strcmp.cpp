//#include<string.h>
#include "strinx.h"
#include <iostream.h>
/*
string.h - strstr : 1 minuta 8 sek
shiftand - 2 minuty 47 sek
shiftand/ASM: 55 sek
shiftor/ASM: 44 sek
strinx.h - strstr/ASM/KMP: 1minuta 18 sek

*/
/*
char * inline shiftor_NOASM(const char *haystack,const char * needle,int l){
	unsigned int tmp[256];
	register unsigned int *mask=tmp;
	//int l=strlen(needle);
	//if(l>32)return 0;
	for(unsigned int * p=mask+255;p>=mask;p--)
		*p=0xFFFFFFFF;	
	unsigned int m=1;
	for(const char * p=needle;*p;p++,m<<=1)
		mask[(unsigned char)*p]^= m;
	register unsigned int w=1<<(l-1);
	register unsigned int a=0xFFFFFFFF;	
	for(register unsigned char * pt=(unsigned char *)haystack;*pt;){
		a<<=1;
		a|=mask[*pt];
		pt++;
		if(!(a&w))
			return (char *)(pt-l);
	}
	return 0;
}
*/
const int size=60006;
char shit[size];	
char test[size];
int main(){
	int j=0;
	
	for(int i=0;i<size;i++)
		shit[i]='a'+i%5;
	shit[size-10]=0;
	strcat(shit,"abcdef");
	for(int t=0;t<100000;t++){
//		j+=strlen(shit);
//		strcpy(test,shit);
//		j+=strcmp(test,shit);
		j+=strstr(shit,"abcdef",6)-shit;
		//j+=shiftand(shit,"abcdef")-shit;
		//j+=shiftor(shit,"abcdef")-shit;
		//j+=shiftor_NOASM(shit,"abcdef",6)-shit;
		
	}
	cout << j<< endl;
	return 0;
}
