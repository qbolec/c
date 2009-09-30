#include<stdio.h>
//ifstream fin("GEMS.IN");
//ofstream fout("GEMS.OUT");
const int maxcolors=4;
struct slist{
	slist * next;
	int id;
};
struct node{
	char visited;
	char done;
	int min[maxcolors];
	slist * sa;
};
node graph[10001];
void addedge(int a,int b){
	slist * nexus=new slist;
	nexus->next=graph[a].sa;
	nexus->id=b;
	graph[a].sa=nexus;
}
void go(int id){
	if(graph[id].visited)
		return;
	graph[id].visited=1;
	for(slist * c=graph[id].sa;c;c=c->next)
		go(c->id);
	for(int mc=0;mc<maxcolors;mc++){
		graph[id].min[mc]=mc+1;
		for(slist * c=graph[id].sa;c;c=c->next)
			if(graph[c->id].done){
				int tmp=0x7FFFFFFF;
				for(int tc=0;tc<maxcolors;tc++)
					if(tc!=mc)
						if(graph[c->id].min[tc]<tmp)
							tmp=graph[c->id].min[tc];
				graph[id].min[mc]+=tmp;
			}
	}
	graph[id].done=1;
}
int main(){
	FILE* input=fopen("GEMS.IN","r");
	FILE* output=fopen("GEMS.OUT","w");
	int N,a,b;
	fscanf(input,"%d",&N);
	for(int i=1;i<N;i++){
		fscanf(input,"%d %d",&a,&b);
		addedge(a,b);
		addedge(b,a);
	}
	go(1);
	int tmp=0x7FFFFFFF;
	for(int c=0;c<maxcolors;c++)
		if(graph[1].min[c]<tmp)
			tmp=graph[1].min[c];
    fprintf(output,"%d\n",tmp);
	fclose(input);
	fclose(output);
	return 0;
}
