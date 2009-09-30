#include<stdio.h>
#include<stdlib.h>
FILE* input=fopen("REGS.IN","r");
FILE* output=fopen("REGS.OUT","w");
struct node{
	int id;
	int c;
	int arity;
	node * arg;
	int regs;
	char storeinreg;
};
node todo;
int Cl;
int Cs;
int N;
int freeid=0;
int cost=0;
int cmp(const void * a,const void * b){
	node * A=(node *)a;
	node * B=(node *)b;
	return B->regs-A->regs;
}
void load(node & root){
	root.id=++freeid;
	fscanf(input,"%d",&root.arity);
	if(root.arity==0){
		root.c=0;
		root.regs=1;
		cost+=Cl;
	}else{
		root.arg=new node[root.arity];
		fscanf(input,"%d",&root.c);
		for(int i=0;i<root.arity;i++)
			load(root.arg[i]);
		qsort(root.arg,root.arity,sizeof(node),cmp);
		int storeneed=0;
		for(int i=0;i<root.arity;i++)
			if(i-storeneed+root.arg[i].regs>N){
				storeneed=i+root.arg[i].regs-N;
			}
		if(storeneed){
			root.regs=N;
		}else{
			root.regs=0;
			for(int i=0;i<root.arity;i++)
				if(root.arg[i].regs+i>root.regs)
					root.regs=root.arg[i].regs+i;
		}
		for(int i=0;i<storeneed;i++)
			root.arg[i].storeinreg=0;
		for(int i=storeneed;i<root.arity;i++)
			root.arg[i].storeinreg=1;
		cost+=storeneed*(Cl+Cs);
		cost+=root.c;
	}
}
void show(node & root){
	if(root.arity){
		for(int i=0;i<root.arity;i++)
			show(root.arg[i]);
		fprintf(output,"%d %d\n",root.id,root.storeinreg);
	}
}
int main(){
	fscanf(input,"%d",&N);
	fscanf(input,"%d %d",&Cl,&Cs);
	load(todo);
	fprintf(output,"%d\n",cost);
	todo.storeinreg=1;
	show(todo);
	fclose(input);
	fclose(output);
	return 0;
}
