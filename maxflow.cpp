#include<vector>
#include<cstdio>
using namespace std;
typedef int flowt;
struct edge{
	int dest;//destination id
	flowt capacity;//potential flow thru this edge
};
struct node{
	vector<int> edges;//indexes of outgoing edges
	int frozen;//have we already been here in this round?
};
const int MAX_NODES=1024;
const int MAX_EDGES=4048;
node nodes[MAX_NODES];
edge edges[MAX_EDGES*2];//each edge has reversed copy with id^1
int freeEdge=0;//for allocating edges[]
int round;//global, for find_some and .frozen
int sink;//global, for find_some and to
void add_edge(int from,int to,flowt capacity,flowt reversed_capacity=0){
	int e=freeEdge;
	freeEdge+=2;
	edges[e].dest=to;
	edges[e].capacity=capacity;
	nodes[from].edges.push_back(e);
	e++;
	edges[e].dest=from;
	edges[e].capacity=reversed_capacity;
	nodes[to].edges.push_back(e);
}
flowt find_some(int from,flowt limit){
	node & n = nodes[from];
	if(!limit  || n.frozen==round)
		return 0;
	if(from==sink)
		return limit;
	n.frozen=round;
	flowt done=0;
	for(int i=n.edges.size();limit && i--;){
		int e=n.edges[i];
		if(flowt flow=find_some(edges[e].dest,limit <? edges[e].capacity )){
			edges[e].capacity-=flow;
			edges[e^1].capacity+=flow;
			done+=flow;
			limit-=flow;
		}
	}
        return done;
}
flowt max_flow(int from,int to){
	flowt result=0;
	sink=to;
	for(int i=0;i<MAX_NODES;i++)
		nodes[i].frozen=0;
	for(round=1;flowt flow=find_some(from,1000000);round++)
		result+=flow;
	return result;
}
void clear(){
	freeEdge=0;
	for(int i=0;i<MAX_NODES;i++)
		nodes[i].edges.clear();
}
//--- PRZYK£AD (maxymalne skojarzenie)
int main(){
	int kobiety,faceci,znajomosci;
	scanf("%d %d %d",&kobiety,&faceci,&znajomosci);
	const int zrodlo=0;
	const int ujscie=1+kobiety+faceci;
	const int warstwaA=1;
	const int warstwaB=1+kobiety;
	for(int i=0;i<znajomosci;i++){
		int kobieta,facet;
		scanf("%d %d",&kobieta,&facet);
		add_edge(warstwaA+kobieta,warstwaB+facet,1,0);
	}
	for(int i=0;i<kobiety;i++)
		add_edge(zrodlo,warstwaA+i,1,0);
	for(int i=0;i<faceci;i++)
		add_edge(warstwaB+i,ujscie,1,0);
	int best=max_flow(0,1+kobiety+faceci);
	printf("There are %d marriages:\n",best);
	for(int i=0;i<kobiety;i++)
		for(int j=nodes[warstwaA+i].edges.size();j--;)
			if(!edges[nodes[warstwaA+i].edges[j]].capacity && edges[nodes[warstwaA+i].edges[j]].dest>=warstwaB)
				printf("girl %d with boy %d\n",i,edges[nodes[warstwaA+i].edges[j]].dest-warstwaB);
	return 0;
}
