#include<cstdio>
#include<vector>
using namespace std;
vector<vector<int> > graf;
vector<int> mark;
vector<int> stos;
vector<int> skladowa;
int n,m;
int skl=0;
void dfs(int v){
	if(!mark[v]){
		mark[v]=true;
		for(int i=0;i<graf[v].size();i++)
			dfs(graf[v][i]);
		stos.push_back(v);
	}
}
void revdfs(int v){
	if(!skladowa[v]){
		skladowa[v]=skl;
		int neg=v^1;
		if(skladowa[neg]==skl)
		  throw 666;
		for(int i=0;i<graf[ neg ].size();i++)
			revdfs(graf[neg][i]^1);
	}
}
void solve(){
	scanf("%d %d",&n,&m);
	graf.clear();
	mark.clear();
	stos.clear();
	skladowa.clear();
	graf.resize(n*2);
	mark.resize(n*2,false);
	skladowa.resize(n*2,0);
	for(int i=0;i<m;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		x=((x<0)? -x*2:x*2+1)-2;// ogolnie p_i =>  2*i+1  ,  !p_i  =>  2*i
		y=((y<0)? -y*2:y*2+1)-2;
		graf[x^1].push_back(y);
		graf[y^1].push_back(x);
	}
	for(int i=0;i<2*n;i++)
		if(!mark[i])
			dfs(i);
	skl=0;
	try{
  	while(!stos.empty()){
	 	  int v=stos.back();
  	 	stos.pop_back();
		  if(!skladowa[v] && ++skl)
			  revdfs(v);
	  }
	}catch(int){
		printf("Not satisfiable\n");
		return;	
	}
	vector<int>  graf2[skl];
	int reprezentant[skl];
	vector<int> deg;
	deg.resize(skl,0);
	for(int i=0;i<2*n;i++)
		reprezentant[ --skladowa[i] ]=i;
	for(int i=0;i<2*n;i++)
		for(int j=0;j<graf[i].size();j++){
			int a=skladowa[graf[i][j]];
			int b=skladowa[i];
			if(b!=a){
				graf2[a].push_back(b);
				deg[b]++;
			}
		}
  vector<int> q;
	for(int i=0;i<skl;i++)
  	if(!deg[i])
  		q.push_back(i);
  while(q.size()){
  	int s=q.back();
  	q.pop_back();
  	if(!deg[s]){
      deg[skladowa[reprezentant[s]^1]]=-1;
  		for(int i=0;i<graf2[s].size();i++)
  			if(!--deg[graf2[s][i]])
  				q.push_back(graf2[s][i]);
  	}
  }
  for(int i=0;i<n;i++)
  	printf("Value of %d is %d\n",i+1,(int)(deg[skladowa[2*i]]==-1));//oto jak pobrac rozwiazanie
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}
/*Przykladowe dane:
1           //#testow

2 3         //#niewiadomych #klauzul

1 2					//a || b
-1 -2       //!a||!b
-1 -1       //!a
*/
