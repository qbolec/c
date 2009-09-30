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

#include<cstdio>
#include<vector>
#include<map>
using namespace std;
long long pack(){
  char name[32];
  scanf("%s",name);
  long long x=1;
  for(int j=0;name[j];j++)
    x=(x<<6)|(name[j]-'a');
  return x;
}
void solve(){
  int n,m;
  scanf("%d",&n);
  vector< vector<pair<int,DIST> > > graf(n);
  map<long long,int> name2id;
  for(int i=0;i<n;i++){
    name2id[pack()]=i;
    scanf("%d",&m);
    graf[i].resize(m);
    while(m--){
      scanf("%d %d",&graf[i][m].first,&graf[i][m].second);
      graf[i][m].first--;
    }    
  }
  scanf("%d",&m);
  while(m--){
    kopiec heap(n);
    heap.relax(name2id[pack()],0);
    long long dst=name2id[pack()];
    while(heap.size){
    	int v=heap.min();
    	heap.delete_min();
    	if(v==dst)
    		break;
    	for(int i=0;i<graf[v].size();i++)
    		heap.relax(graf[v][i].first,heap.dist[v]+graf[v][i].second);
    }
    printf("%d\n", heap.dist[dst] );
  }	
}
int main(){
  int s;
  scanf("%d",&s);
  while(s--)
    solve();  
  return 0;
}
