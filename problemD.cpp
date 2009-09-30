#include<iostream.h>
#include<stdlib.h>
int num[1000];
int n;
int m;
int q;
int cas=1;
int best;
int dist;
int cmp(const void *a,const void * b){
	return *(int *)a-*(int *)b;
}
int abs(int a){
	if(a<0)return -a;
	return a;
}
void check(int c){
	if(abs(q-c)<dist){
		dist=abs(q-c);
		best=c;
	}
}
int bsercz(int d,int from,int to){
	if(to<from+2)
		return from;
	int c=(from+to)>>1;
	if(num[c]==d)
		return c;
	if(num[c]<d){
		return bsercz(d,c,to);
	}else{
		return bsercz(d,from,c);
	}
}
int getbest(){
	best=num[0]+num[1];
	dist=abs(q-best);
	check(num[n-1]+num[n-2]);
	for(int i=0;i<n;i++){
		int dif=q-num[i];
		if(dif<0){
			if(i>0)
				check(num[0]+num[i]);
			return best;
		}else if(dif>num[n-1]){
			if(i!=n-1)
				check(num[n-1]+num[i]);
		}else{
			int b=bsercz(dif,0,n);
			if(b!=i)
				check(num[i]+num[b]);
			if((b>0)&&(b-1!=i))
				check(num[i]+num[b-1]);
			if((b<n-1)&&(b+1!=i))
				check(num[i]+num[b+1]);
		}
	}
	return best;
}
int main(){
	while(1){
		cin >> n;
		if(!n)
			return 0;
		cout << "Case " << cas++ << ':' << endl;
		for(int i=0;i<n;i++)
			cin >> num[i];
		qsort(num,n,sizeof(int),cmp);
		cin >> m;
		for(int i=0;i<m;i++){
			cin >> q;
			cout << "Closest sum to " << q <<" is "<< getbest() << '.' << endl;
		}
	}
}
