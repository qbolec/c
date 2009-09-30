#include<iostream.h>
int freecolor;
int BFS[1000];
int DFS[1000];
int n;
struct tree{
	int brat;
	int syn;
	int color;
};
tree node[1001];
void ACM_assert(int shouldbetrue){
    if(!shouldbetrue)
    	*((int *)0)=1337;
}
int next(int * fs,int color,int i){
	while(++i<n)
		if(node[fs[i]].color==color)
			return i;
	return 0;
}
void doit(int bi,int di,int color){
	int tato=BFS[bi];
	int bn=next(BFS,color,bi);
	int dn=next(DFS,color,di);
	if(!bn)
		return;
	if(BFS[bn]==DFS[dn]){
		node[tato].syn=BFS[bn];
		doit(bn,dn,color);
	}else{
		node[tato].syn=DFS[dn];
		node[tato].brat=BFS[bn];
		ACM_assert(BFS[bn]<tato);
		freecolor++;
		int cn;
		for(cn=dn;(cn<n)&&(DFS[cn]!=BFS[bn]);cn++)
			node[DFS[cn]].color=freecolor;
		if(cn==n)
			for(cn=0;DFS[cn]!=BFS[bn];cn++);
		doit(bn,cn,color);
		doit(next(BFS,freecolor,bn),dn,freecolor);
	}
}
int main(){
	int i;
	cin >> n;
	for(i=0;i<n;i++)
		cin >> BFS[i];
	for(i=0;i<n;i++)
		cin >> DFS[i];
	doit(0,0,0);
	for(i=1;i<=n;i++){
		cout << i << ':';
		for(int j=node[i].syn;j;j=node[j].brat)
			cout <<' ' << j;
		cout << endl;
	}
	return 0;
}
