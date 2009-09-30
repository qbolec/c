#include <iostream.h>
struct mask{
	unsigned long h;
	unsigned long l;
};
mask none;
mask all;
mask town[35];
int perm[35];
int best;
int n;
void add(int a,int b){
	if(a<32)
		town[b].l|= 1<<a;
	else
		town[b].h|= 1<< (a-32);
}
void permute(int p,int l, int h){
	if(n-p>=best)
		return;
	int i,s;
	for(i=0;i<=p;i++){
		if(((l|town[perm[i]].l)==all.l)&&((h|town[perm[i]].h)==all.h)){
			best=n-p;
			return;
		}
	}
	permute(p-1,l|town[perm[p]].l,h|town[perm[p]].h);
	
	for(i=0;i<p;i++){
		s=perm[i];
		perm[i]=perm[p];
		perm[p]=s;
		permute(p-1,l|town[s].l,h|town[s].h);
	}
	s=perm[0];
	for(i=0;i<p;i++)
		perm[i]=perm[i+1];
	perm[p]=s;
}
int main(){
	int m,a,b;
	while(1){
		cin >> n >> m;
		if(n||m){
			best=n;
			if(n<32){
				all.l=(1<<n)-1;
				all.h=0;
			}else{
				all.l=0xFFFFFFFF;
				all.h=(1<<(n-32))-1;
			}
			for(int i=0;i<n;i++){
				town[i].h=town[i].l=0;
				add(i,i);
				perm[i]=i;
			}
			while(m--){
				cin >> a >> b;
				add(--a,--b);
				add(b,a);
			}
			permute(n-1,0,0);
			cout << best << endl;
		}else
			return 0;

	}
}
