/*
	To jest kopiec przeznaczony specjalnie do dikstry, pozwala wyciagac kolejny element,
	albo zmniejszac jakis element.
*/
typedef int DIST;
const DIST INF=0x7FFFFFFF;
struct kopiec{
	int size;
	int * whereis;
	int * cox;
	DIST * dist;
	int min(){
		return cox[1];
	}
	void swap(int i,int j){
		whereis[cox[i]]=j;
		whereis[cox[j]]=i;
		int x=cox[i];
		int y=cox[j];
		cox[i]=y;
		cox[j]=x;
	}
	void delete_min(){
		swap(1,size--);
		for(int p=1;;){
			int c1=p*2;
			if(c1>size)
				return;
			int c2=c1+1;
			if(c2<=size && dist[cox[c2]]<dist[cox[c1]])
				c1=c2;
			if(dist[cox[c1]]<dist[cox[p]]){
				swap(c1,p);
				p=c1;
			}else
				return;
		}
	}
	void relax(int node,DIST newdist){
		if(newdist< dist[node]){
			dist[node]=newdist;
			for(int p=whereis[node];p>1;){
				int f=p/2;
				if( dist[cox[p]] < dist[cox[f]] ){
					swap(p,f);
					p=f;
				}else
					return;
			}
		}
	}
	kopiec(int size):size(size){
  	cox=new int[size+1];
  	whereis=new int[size];
  	dist=new DIST[size];
  	for(int i=0;i<size;i++){
  		dist[i]=INF;
  		whereis[i]=i+1;
  		cox[i+1]=i;
  	}
  }
  ~kopiec(){
  	delete cox;
  	delete whereis;
  	delete dist;
  }
};

// Przyk³adowe u¿ycie dla grafu nieskierowanego

#include<iostream>
#include<vector>
using namespace std;
vector< vector<pair<int,DIST> > > graf;
int main(){
	int n,m;
	cin >> m >> n;
	graf.resize(n);
	for(int i=0;i<m;i++){
		int f,t,c;
		cin >> f >> t >> c;
		graf[f-1].push_back( make_pair( t-1, c) );
		graf[t-1].push_back( make_pair( f-1, c) );
	}
	kopiec heap(n);
	heap.relax(0,0);
	while(heap.size){
		int v=heap.min();
		heap.delete_min();
		if(v==n-1)
			break;
		for(int i=0;i<graf[v].size();i++)
			heap.relax(graf[v][i].first,heap.dist[v]+graf[v][i].second);
	}
	cout << heap.dist[n-1] << endl;
	return 0;
}
