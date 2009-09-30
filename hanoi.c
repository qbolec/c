#include <stdio.h>
/*hanoi for mark*/
int core[3][100];
int cc[3];
void showmove(int n,int a,int b){
	int i,j;
	core[b][cc[b]++]=core[a][--cc[a]];
	printf("krazek %d: %d->%d\n",n,a+1,b+1);
	for(i=0;i<3;i++){
		for(j=0;j<cc[i];j++)
			printf("[%d]",core[i][j]);
		printf("\n");
	}
}
void hanoi(int f,int t,int n){
	int c=3-f-t;
	if(n>1){
		hanoi(f,c,n-1);
		showmove(n,f,t);
		hanoi(c,t,n-1);
	}else{
		showmove(1,f,t);
	}
}
int main(){
	int n,i;
	printf("Prosze podaæ iloœæ kr¹¿ków :");
	scanf("%d",&n);
	cc[0]=n;
	for(i=0;i<n;i++)
		core[0][i]=n-i;
	hanoi(0,1,n);
	return 0;
}
