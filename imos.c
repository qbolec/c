
int podnapis(char wzor[],char napis[]){
	int i,j;
	for(i=0;napis[i];i++){
		for(j=0;wzor[j]&&napis[i+j];j++)
			if(wzor[j]!=napis[i+j])
				break;
		if(!wzor[j])
			return i;
	}
	return -1;
}
double findzero(double from,double to,double  foo(double x) ){
	double mid=(from+to)/2;
	if(to-from<0.0001)
		return mid;
	if(foo(mid)*foo(from)<0)
		return findzero(from,mid,foo);
	else
		return findzero(mid,to,foo);
}
int power(int x,int n){
	int p;
	if(n==0)
		return 1;
	if(n==1)
		return x;
	for(p=2;p*p<=n;p++)
		if(n%p==0)
			return power(x*power(x,p-1),n/p);
	return x*power(x,n-1);
}
void strncpy(char * s,char * t,int n){
	while((n--)&&(*t))
		*s++=*t++;
}
void strncat(char * s,char * t,int n){
	while(*s++);
	while((n--)&&(*t))
		*s++=*t++;
}
int strncmp(char * s,char * t,int n){
	while(n--)
		if(*s<*t)
			return -1;
		else if(*s>*t++)
			return 1;
		else if(*s++==0)
			return 0;
	return 0;
}


#include <stdio.h>

int main(){
	int day,month,year,s_day,s_weekday,t_day,t_month,t_year,t_weekday;
	char text[256];
	int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	char week[7][14]={"poniedzialek","wtorek","sroda","czwartek","piatek","sobota","niedziela"};
	printf("Podaj dzisiejsza date, oraz kombinacje, której szukasz\n");
	printf("np. 21 02 2003 piatek 13\n");
	scanf("%d %d %d %s %d",&day,&month,&year,text,&s_day);
	for(s_weekday=0;strncmp(week[s_weekday],text,13);s_weekday++);
	t_day=26;
	t_month=1;
	t_year=2003;
	t_weekday=6;
	while((t_day!=day)||(t_month!=month)||(t_year!=year)){
		t_weekday++;
		if(months[t_month]==t_day){
			t_month++;
			t_day=1;
			if(t_month==13){
				t_year++;
				t_month=1;
				if(t_year%4==0)
					months[2]=29;
				else
					months[2]=31;
			}
		}else{
			t_day++;
		}
	}
	t_weekday%=7;
	printf("dzisiaj jest %s\n" , week[t_weekday]);
	while((t_day!=s_day)||(t_weekday!=s_weekday)){
		t_weekday++;
		t_weekday%=7;
		if(months[t_month]==t_day){
			t_month++;
			t_day=1;
			if(t_month==13){
				t_year++;
				t_month=1;
				if(t_year%4==0)
					months[2]=29;
				else
					months[2]=31;
			}
		}else{
			t_day++;
		}
	}
	printf("najbli¿szy %s %d nastapi dnia %d %d %d",week[s_weekday],s_day,t_day,t_month,t_year);
	return 0;
}
