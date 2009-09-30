#include<iostream.h>
const int N=4;
const int tasks=8;
const int sums=N*2+2;
int tab[N*N];
int task[tasks]={36,45,51,62,125,137,171,259};
int p10[10]={1,10,100,1000,10000,100000,1000000,10000000};
void check(){
	for(int i=0;i<N;i++)
		if(!tab[i]||!tab[i*N])
			return;
	int sum[sums];
	for(int i=0;i<sums;i++)
		sum[i]=0;
	for(int x=0;x<N;x++){
		int *p=tab+N*(N-1)+x;
		int *w=p10;
		for(int y=N;y>0;y--){
			sum[x]+=(*w)*(*p);
			p-=N;
			w++;
		}
	}
	for(int y=0;y<N;y++){
		int *p=tab+y*N+N-1;
		int *w=p10;
		for(int x=N;x>0;x--){
			sum[y+N]+=(*w)*(*p);
			p--;
			w++;
		}
	}
	int *w=p10;
	for(int i=N-1;i>=0;i--){
		sum[N+N]+=(*w)*tab[i*N+i];
		sum[N+N+1]+=(*w)*tab[i*N+N-1-i];
		w++;
	}
	for(int i=0;i<sums;i++)
		for(int j=0;j<i;j++)
			if(sum[i]==sum[j])
				return;
	for(int t=0;t<tasks;t++){
		int i=0;
		for(;i<sums;i++)
			if(sum[i]%task[t]!=0)
				break;
		if(i==sums){
			cout << "Solved task:" << (t+3) << " that is M=" << task[t] << endl;
			cout << N << endl;
			for(int y=0;y<N;y++){
				for(int x=0;x<N;x++)
					cout << tab[y*N+x] << ' ';
				cout << endl;
			}
		}
	}

}
void broot(int pos){
	if(pos==N*N)
		check();
	else{
		for(int i=0;i<10;i++){
			tab[pos]=i;
			broot(pos+1);
		}
	}
}
int main(){
	broot(0);
	return 0;
}
