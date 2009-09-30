#include<iostream.h>
#include<math.h>
#define ACM_assert(x) {if(!(x))*((long *)0)=666;}
typedef double number;
int n;//towary
int m;//dzieci
const int MAX_DZIECI=100;
const int MAX_TOWAR=100;
number cena[MAX_TOWAR];
number total[MAX_DZIECI+MAX_TOWAR];
number fun[MAX_DZIECI+MAX_TOWAR][MAX_TOWAR];
number answer;
int clock=0;

int var_number;
int which_eqs[MAX_DZIECI];
int which_var[MAX_TOWAR];

number uklad[MAX_TOWAR][MAX_TOWAR+1];
int perm[MAX_TOWAR];
number solved[MAX_TOWAR];

inline void swap(int &a,int &b){
	int s=a;
	a=b;
	b=s;
}
void solveit(int size){
	if(size==1){
		if(!uklad[perm[0]][1])
			throw 0;
		solved[0]= uklad[perm[0]][0] / uklad[perm[0]][1];
		if(solved[0]<0)
			throw 0;
		return;
	}
	int bestr=0,r,i;
	number best=fabs(uklad[perm[0]][size]);
	for(r=1;r<size;r++)
		if(fabs(uklad[perm[r]][size])>best){
			best=fabs(uklad[perm[r]][size]);
			bestr=r;
		}
	if(!best)
		throw 0;
	swap( perm[size-1], perm[bestr] );
	number * main_row=uklad[perm[size-1]];
	best=main_row[size];
	for(r=0;r<size-1;r++){
		number * this_row=uklad[perm[r]];
		number * ptr=main_row;
		number factor=this_row[size]/best;
		if(factor){
			for(i=size;i;i--)
				(*this_row++)-=factor*(*ptr++);		
		}
	}
	solveit(size-1);
	number x=main_row[0];
	number * ptr=main_row+1;
	number * sol=solved;
	for(i=1;i<size;i++)
		x-= (*sol++)*(*ptr++);
	if((solved[size-1]=(x/best))<0)
		throw 0;
}
inline void prepareuklad(){
	for(int r=0;r<var_number;r++){
		for(int i=0;i<var_number;i++)
			uklad[r][i+1]=fun[which_eqs[r]][which_var[i]];
		uklad[r][0]=total[which_eqs[r]];
		perm[r]=r;
	}
}
void combine(int pos,int limit,int * result,void signal()){
	if(pos==0){		
			signal();
	}else{
		pos--;
		for(int i=pos;i<limit;i++){
			result[pos]=i;
			combine(pos,i,result,signal);
		}
	}	
}
void got_vars(){
	prepareuklad();
	try{
		solveit(var_number);
		number cost=0;
		for(int i=0;i<var_number;i++)
			cost+=cena[which_var[i]]*solved[i];
		if(cost>answer){
			for(int d=0;d<m;d++){
				number happy=0;
				for(int i=0;i<var_number;i++)
					happy+=fun[d][which_var[i]]*solved[i];
				if(happy>total[d])
					return;
			}
			answer=cost;
		}
	}catch(int){}
}
void got_eqs(){
	combine(var_number,n,which_var,got_vars);
}
inline void gogo(){
	answer=0;
	for(var_number=1;var_number<=n;var_number++)
		combine(var_number,n,which_eqs,got_eqs);		
	answer*=m;
	int ans=(long)ceil(answer);
	cout << "Nasa can spend " << ans << " taka." << endl;
}
inline void read(){
	for(int i=0;i<n;i++)
		cin >> cena[i];
	for(int d=0;d<m;d++){
		for(int i=0;i<n;i++)
			cin >> fun[d][i];
		cin >> total[d];
	}
}
int main(){
	while(1){
		cin >> n >> m;
		// n=12   n+m=20
		if(cin.eof())
			return 0;
		read();
		
	}
}
