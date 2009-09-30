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
int period(char const * selfmaximal,int limit){
	const char * l=selfmaximal;
	const char * p=l+1;
	char const * end=selfmaximal+limit;
	for(p=l+1;p<end;)
		if(*p++!=*l++)
			l=selfmaximal;
	return p-l;
}
char * strstr(const char * const needle,const char * const haystack){
	const char * const v=maxsuffix(needle);
	const char * v_candidate=haystack;
	const char * v_ignore=haystack;
	const int u_len=v-needle;
	int v_amount=0;
	int v_alternative_amount=0;
	while(v_candidate[v_amount]){
		while(v_candidate[v_amount]==v[v_amount]&&v[v_amount]){
			if(v[v_amount++]!=v[v_alternative_amount++])
				v_alternative_amount=0;
		}
		if(!v[v_amount]){
			//znaleziono wystapienie v
			if(v_candidate>v_ignore){
				const char *n=needle;
				for(const char *u=v_candidate-u_len;u<v_candidate;)
					if(*u++!=*n++)
						break;
				if(n==v)//znaleziono wystapienie uv
					return (char *)v_candidate-u_len;
			}
			v_ignore=v_candidate+u_len;
		}
		const int okres=v_amount-v_alternative_amount;
		//przesuwamy sie
		v_candidate+=okres;
		v_amount=v_alternative_amount;
		//jesli okres jest krotszy niz nowa dlugosc dopasowania
		if(okres<v_amount){
			//to mozna go dalej uwazac za okres
			v_alternative_amount-=okres;
		}else{
			//jak nie to trzeba go wyznaczyc
			v_alternative_amount=period(v,v_amount);
		}
	}
	return 0;
}
#include<iostream>
using namespace std;
int main(){
	char n[256];
	char h[256];
	cin >> n >> h;
	cout << strstr(n,h);
}

