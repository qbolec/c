/*
	qbolec presents : pentium optimized strinx.h
	strlen - 11 sec vs. 21 sec @ duron 750
	strcmp - 17 sec vs. 47 sec 
	strcpy + strlen + strcmp - 48 sec vs. 89 sec  //  dif:41 seconds
	strcpy + strlen + strcmp + strstr - 98 sec vs. 133 //  dif:32 seconds
	on some compilers [other than VC++] the _asm directive may be incopatible
	in such cases use : #define NO_ASM
	strstr uses KMP method which is sometimes not very effective [it uses external, nonregister variables]
	you might #define NO_KMP to use also very effective hash style foo
 */
#define NO_ASM
#define NO_KMP
#define CONSTSPACE
#ifdef NO_ASM 
int strlen(const char *s){
	int * d=(int *)s;
	while(1){
		if((*d&0x000000FF)==0)
			return ((char *)d)-s;
		if((*d&0x0000FF00)==0)
			return ((char *)d)-s+1;
		if((*d&0x00FF0000)==0)
			return ((char *)d)-s+2;
		if((*d&0xFF000000)==0)
			return ((char *)d)-s+3;
		d++;
	}
}
#ifdef NO_KMP
#ifdef CONSTSPACE
//madafaka strstr in O(n+m) and const space:D
//'for own sat'
const char * maxsuffix(const char * pattern){
	const char *a=pattern;
	const char *b=a;
	while(1){
   		if(a==b)b++;//szturchamy
   		int i;
   		for(i=0;b[i]==a[i];i++){}
   		if(!b[i])
       		return a;
   		if(!a[i])
       		return b;
   		if(b[i]>a[i])
     		a+=i+1;
   		else
     		b+=i+1;
	}
}
char * period(char const * const selfmaximal,char const * const limit){
	const char * l=selfmaximal;
	const char * p=l+1;	
	for(p=l+1;p<limit;)
		if(*p++!=*l++)
			l=selfmaximal;
	return (char *)l;
}
char * strstr(const char * const haystack,const char * const needle,int l){
	const char * const v=maxsuffix(needle);
	const char * v_candidate_testin_pos=haystack;
	const char * v_ignore=haystack;
	const char * v_good=v;
	const char * v_worse=v;
	const int u_len=v-needle;
	while(*v_candidate_testin_pos){
		while(*v_candidate_testin_pos==*v_good){
			v_candidate_testin_pos++;
			if(v_good>v)
				if(*v_good!=*v_worse)
					v_worse=v;
				else
					v_worse++;			
			if(!*++v_good)
				break;
		}
		if(v_good>v){
			if(!*v_good){				
				if(v_candidate_testin_pos>v_ignore){//znaleziono wystapienie v
					const char *n=needle;
					for(const char *u=v_candidate_testin_pos-l;n<v;)
						if(*u++!=*n++)
							break;
					if(n==v)//znaleziono wystapienie uv
						return (char *)v_candidate_testin_pos-l;
				}
				v_ignore=v_candidate_testin_pos+u_len;
			}
			const int okres=v_good-v_worse;
			//przesuwamy sie
			v_good=v_worse;			
			if(v_good>v+1)
				if(okres<v_good-v)//jesli okres jest krotszy niz nowa dlugosc dopasowania
					v_worse-=okres;//to mozna go dalej uwazac za okres
				else					
					v_worse=period(v,v_good);//jak nie to trzeba go wyznaczyc
			else//krotkie slowo nie ma okresu wlasciwego				
				v_worse=0;
		}else
			while(*++v_candidate_testin_pos!=*v){}				
	}
	return 0;
}
#else//nodef for constspace
char * strstr(const char *haystack,const char * needle){
	const int q=12823;
	const int q256=q<<8;
	int goodhash=0;
	int thishash=0;
	int powerone=1;
	int powertwo=1;
	const char * n=needle;
	unsigned char * h=(unsigned char *)haystack;
	unsigned char * ho=(unsigned char *)haystack;
	for(;*n&&*h;h++,n++){
		powerone=powertwo;
		goodhash<<=8;
		powertwo<<=8;
		thishash<<=8;
		goodhash|=*n;
		thishash|=*h;
		thishash%=q;
		goodhash%=q;
		powertwo%=q;
	}
	if(*n)return 0;
	if(thishash==goodhash){
		n=needle;
		for(unsigned char * hm=ho;*n;hm++,n++)
			if(*n!=*hm)
				break;
		if(*n==0)
			return (char *)ho;
	}
	while(*h){
		thishash+=q256;
		thishash-=powerone*(*ho);
		thishash<<=8;
		thishash|=*h;
		thishash%=q;
		h++;
		ho++;
		if(thishash==goodhash){
			n=needle;
			for(unsigned char * hm=ho;*n;hm++,n++)
				if(*n!=*hm)
					break;
			if(*n==0)
				return (char *)ho;
		}		
	}	
	return 0;
}
#endif
#else//KMP+NO_ASM
char * strstr(const char *haystack,const char * needle){
	char * r=0;
	long l=strlen((char *)needle);
	if(!l)return (char *)haystack;
	long kmp[1024];	
	kmp[0]=0;
	for(long i=1;i<l;i++){
		long k=i-1;
		while(k&&(needle[i]!=needle[kmp[k]+1]))k=kmp[k];
		if(k)kmp[i]=kmp[k]+1;
		else kmp[i]=0;
	}
	int s=0;
	while(*haystack){
		if(*haystack==needle[s]){
			haystack++;
			s++;
			if(s==l)
				return (char *)haystack-l;
		}else{
			if(s)
				s=kmp[s];
			else
				haystack++;
		}
	}	
}
#endif//NO_ASM
char * strcpy(char * dest,char * source){
	int * c=(int *)dest;
	int * d=(int *)source;
	while(1){
		if((*d&0x000000FF)==0){
			*(char *)c=0;
			return dest;			
		}
		if((*d&0x0000FF00)==0){
			*(char *)c=*(char *)d;
			((char *)c)[1]=0;
			return dest;			
		}
		if((*d&0x00FF0000)==0){
			*(short int *)c=*(short int *)d;
			((char *)c)[2]=0;
			return dest;			
		}
		if((*d&0xFF000000)==0){
			*(short int *)c=*(short int *)d;
			((char *)c)[2]=((char *)d)[2];
			((char *)c)[3]=0;
			return dest;			
		}
		*c=*d;
		c++;
		d++;
	}	
}
char * strcat(char * dest,char * source){
	strcpy(dest+strlen(dest),source);
	return dest;
}
int strcmp(char * a,char * b){
	int * c=(int *)a;
	int * d=(int *)b;
	int ea;
	int eb;
	ea=*c;
	eb=*d;
	if(ea==eb){
		do{
		if((ea&0x000000FF)==0)
			return 0;
		if((ea&0x0000FF00)==0)
			return 0;
		if((ea&0x00FF0000)==0)
			return 0;
		if((ea&0xFF000000)==0)
			return 0;
		c++;
		d++;
		ea=*c;
		eb=*d;
		}while(ea==eb);
	}
	while(1){
		if((char)ea>(char)eb)
			return 1;
		else if((char)ea<(char)eb)
			return -1;
		else if((char)ea==0)
			return 0;
		ea>>=8;
		eb>>=8;
	}
}

#else///asm below
int strlen(const char *s){
	int r;
	_asm{
			mov edx,s
			mov ecx,edx
next4:		mov eax,[edx]
			test eax,0x000000FF
			jz returns
			test eax,0x0000FF00
			jz returns1
			test eax,0x00FF0000
			jz returns2
			test eax,0xFF000000
			jz returns3
			add edx,4
			jmp next4
returns3:	inc edx
returns2:	inc edx
returns1:	inc edx
returns:	sub edx,ecx
			mov r,edx
	}
	return r;
}
char * strcpy(char * dest,char * source){
	_asm{
		mov ecx,dest
		mov edx,source
next4:		mov eax,[edx]
			test eax,0x000000FF
			jz returns
			test eax,0x0000FF00
			jz returns1
			test eax,0x00FF0000
			jz returns2
			test eax,0xFF000000
			jz returns3
			mov [ecx],eax
			add ecx,4
			add edx,4						
			jmp next4
returns3:	mov [ecx],al
			inc ecx
			shr eax,8
returns2:	mov [ecx],al
			inc ecx
			shr eax,8
returns1:	mov [ecx],al
			inc ecx				
returns:	mov ax,0
			mov [ecx],al

	}
	return dest;
}
char * strcat(char * dest,char * source){
	strcpy(dest+strlen(dest),source);
	return dest;
}
int strcmp(char * a,char * b){
	int r=0;
	_asm{
		mov ecx,a
		mov edx,b
		
		mov eax,[ecx]
		mov ebx,[edx]
		cmp eax,ebx
		jne decide
		
checklen:
		test eax,0x000000FF
		jz equal
		test eax,0x0000FF00
		jz equal
		test eax,0x00FF0000
		jz equal
		test eax,0xFF000000
		jz equal

		add ecx,4
		add edx,4
		
		mov eax,[ecx]
		mov ebx,[edx]
		cmp eax,ebx
		je checklen		

decide:	cmp al,bl
		ja aisbigger
		jb bisbigger
		test al,al
		jz equal
		shr eax,8
		shr ebx,8
		jmp decide
aisbigger:	mov r,1
		jmp equal
bisbigger:	mov r,-1
equal:	
	}
	return r;
}
#ifdef NO_KMP//+ASM
char * strstr(const char *haystack,const char * needle){
	const int q=0xFFF1;
	int goodhash=0;
	int thishash=0;
	int powerone=1;
	int powertwo=1;
	const char * n=needle;
	unsigned char * h=(unsigned char *)haystack;
	unsigned char * ho=(unsigned char *)haystack;
	for(;*n&&*h;h++,n++){
		powerone=powertwo;
		goodhash<<=8;
		powertwo<<=8;
		thishash<<=8;
		goodhash|=*n;
		thishash|=*h;
		thishash%=q;
		goodhash%=q;
		powertwo%=q;
	}
	if(*n)return 0;
	if(thishash==goodhash){
		n=needle;
		for(unsigned char * hm=ho;*n;hm++,n++)
			if(*n!=*hm)
				break;
		if(*n==0)
			return (char *)ho;
	}
	char * retval=0;
	_asm{
		mov edx,thishash
		push esi
		push edi
		mov edi,powerone
		mov esi,ho
		mov ecx,h
		sub ecx,esi				
		mov bh,[esi+ecx]
		test bh,bh
		jz  notfound
whileh:	push ecx		
		add edx,0xFFF100//q*256
		push edx
		//mov bl,[esi]
		movzx eax,[esi]//bl
		//mov ecx,edi
		mul edi//ecx
		pop edx
		sub edx,eax
		shl edx,8
		mov dl,bh
		mov eax,edx//
		xor edx,edx//
		mov ecx,12823//0x3217
		div ecx//          te cztery linijki to edx%=12823 i trwaja okolo 42 taktów
		inc esi
		cmp edx,goodhash
		je foundsome
wasnt:	pop ecx		
		mov bh,[esi+ecx]
		test bh,bh
		jnz whileh
foundsome:
		mov eax,esi
		mov ecx,needle
forn:	mov bh,[eax]
		mov bl,[ecx]
		test bl,bl
		jz	foundebp
		cmp bh,bl
		jne wasnt
		inc ecx
		inc eax
		jmp forn
foundebp:
		mov retval,esi
notfound:
		pop edi
		pop esi
	}
	return retval;
}
#else
char * inline strstr_kmp(const char *haystack,const char * needle,int l){
	char * r=0;
	//long l=strlen((char *)needle);
	//if(!l)return (char *)haystack;
	long * kmp=new long[l];	
	kmp[0]=0;
	for(long i=1;i<l;i++){
		long k=i-1;
		while(k&&(needle[i]!=needle[kmp[k]+1]))k=kmp[k];
		if(k)kmp[i]=kmp[k]+1;
		else kmp[i]=0;
	}
	_asm{
		xor eax,eax
		mov ebx,needle
		xor ecx,ecx
		mov edx,haystack

wh:		mov cl,[edx]
		jcxz endh
		
		xor cl,[ebx+eax] // autor mia³ na myœli cos ala cmp cl,needle[eax]
		
		jne diffrent

same:	inc edx
		inc eax		
		jmp wh
diffrent:
		test cl,[edx]
		je found
		test eax,eax
		je kmp0

kmpN0:	add eax,kmp		
		mov eax,[eax]  // eax=kmp[eax]		
		jmp wh

kmp0:	inc edx
		jmp wh


endh:	cmp eax,l
		jne notfound
found:	sub edx,eax
		mov r,edx		// r= edx-l
notfound:
	}
	delete kmp;
	return r;
}
char * inline shiftor(const char *haystack,const char * needle,int l){
	unsigned int tmp[256];
	unsigned int *mask=tmp;
	//int l=strlen(needle);
	//if(l>32)return 0;
	for(unsigned int * p=mask+255;p>=mask;p--)
		*p=0xFFFFFFFF;	
	unsigned int w=1;
	for(const char * p=needle;*p;p++,w<<=1)
		mask[(unsigned char)*p]^= w;
	w=1<<(l-1);
	char * retval=0;
	_asm{
		mov eax,0xFFFFFFFF
		xor ebx,ebx
		mov ecx,w
		mov edx,haystack		
		push esi
		mov esi,mask
next:
		mov bl,[edx]
		test bl,bl
		jz	notfound
		shl eax,1
		or eax,[esi+ebx*4]
		inc edx
		test eax,ecx		
		jnz next
		sub edx,l
		mov retval,edx
notfound:
		pop esi
	}
	return retval;
}
char * strstr(const char * haystack,const char * needle){
	long l=strlen((char *)needle);
	if(!l)return (char *)haystack;
	if(l<33)return shiftor(haystack,needle,l);
	else return strstr_kmp(haystack,needle,l);
}
#endif
#endif
