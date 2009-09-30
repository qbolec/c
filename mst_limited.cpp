#include<cstdio>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
int n,m,d;
typedef pair<int,int>edge;
typedef pair<int,edge>cedge;
vector<cedge> edges;
vector<int> uf;
vector<cedge> md;
vector<vector<cedge> > tree;
int find(int id){
	if(uf[id]<0)return id;
	return uf[id]=find(uf[id]);
}
void unite(int a,int b){
	if(uf[a]<uf[b]){
		uf[b]=a;
	}else if(uf[b]<uf[a]){
		uf[a]=b;
	}else{
		uf[a]=b;
		uf[b]--;
	}
}
vector<int> visited;
const int MAX_COST=666000000;
vector<vector<int> > mincost;
vector<vector<int> > mincost_help;
vector<int> shortcut;

void dfs(int id){
  visited[id]=1;
  vector<int> children;
  vector<int> childrencost;
  for(int i=0;i< tree[id].size();i++){
    int x=tree[id][i].second.first;
    int y=tree[id][i].second.second;
    int oder= x==id ? y:x;
    if(!visited[oder]){             
      dfs(oder);
      children.push_back(oder);
      childrencost.push_back(tree[id][i].first);
    }
  }  
//     printf("children count:%d\n",children.size());   

  for(int i=0;i<=d;i++){
    mincost_help[id][i]=0;
  }
  if(shortcut[id]<MAX_COST){
     mincost[id][0]=MAX_COST;
     for(int i=1;i<=d;i++){
       mincost[id][i]=shortcut[id];
     }         
  }else{
    for(int i=0;i<=d;i++){
      mincost[id][i]=MAX_COST;
    }         
  }
  for(int c=0;c<children.size();c++){
    int cid=children[c];
    vector<int> mincost_help2(d+1,MAX_COST);
    vector<int> mincost2(d+1,MAX_COST);
    //with help
    for(int i=0;i<=d;i++){
      if(i)mincost_help2[i]<?=mincost_help2[i-1];
      for(int k=0;k<=i;k++){
        //lacze sie z dzieckiem
        mincost_help2[i]<?= mincost_help[id][i-k]+mincost_help[cid][k]+childrencost[c];
        //nie lacze sie
        mincost_help2[i]<?= mincost_help[id][i-k]+mincost[cid][k];
      }            
    }
  //without help
    for(int i=0;i<=d;i++){
      if(i)mincost2[i]<?=mincost2[i-1];
      for(int k=0;k<=i;k++){
        //lacze sie z dzieckiem i ono mi pomaga
        mincost2[i]<?= mincost_help[id][i-k]+mincost[cid][k]+childrencost[c];
        //lacze sie i mu pomagam
        mincost2[i]<?= mincost[id][i-k]+mincost_help[cid][k]+childrencost[c];
        //nie lacze sie
        mincost2[i]<?= mincost[id][i-k]+mincost[cid][k];                
      }            
    } 
    
    for(int i=0;i<=d;i++){
      mincost[id][i]=mincost2[i];
      mincost_help[id][i]=mincost_help2[i]<?mincost2[i];
    }
  }
}
void solve(){
	scanf("%d %d %d",&n,&m,&d);
	edges.clear();
	for(int i=0;i<m;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		if(x>y)swap(x,y);
		edges.push_back(cedge(z ,edge(x,y)));
		//edges.push_back(cedge(z ,edge(y,x)));
	}
	sort(edges.begin(),edges.end());
	uf.clear();
	uf.resize(n+1,-1);
	md.clear();
	shortcut.clear();
	shortcut.resize(n+1,MAX_COST);
	for(int i=0;i<edges.size();i++){
		int x=find(edges[i].second.first);
		int y=find(edges[i].second.second);
		if(edges[i].second.first!=1){		
			if(x!=y){
				unite(x,y);
				md.push_back(edges[i]);
			}
		}else{
      shortcut[ edges[i].second.second ]<?= edges[i].first;
		}
	}
	tree.clear();
	tree.resize(n+1, vector<cedge>() );
	for(int i=0;i<md.size();i++){
    int x= md[i].second.first;
    int y= md[i].second.second;
    tree[x].push_back(md[i]);
    tree[y].push_back(md[i]);
  }
   	

  visited.clear();
  visited.resize(n+1,0);
  mincost.clear();
  mincost.resize(n+1,vector<int>(d+1));
  mincost_help.clear();
  mincost_help.resize(n+1,vector<int>(d+1));
  vector<int> best(d+1,0);
  for(int id=2;id<=n;id++){
    if(!visited[id] && shortcut[id]<MAX_COST){
      dfs(id);
      vector<int> best2(d+1,MAX_COST);
      for(int i=0;i<=d;i++){
        if(i)best2[i]<?=best2[i-1];
        for(int k=0;k<=i;k++){
          best2[i]<?= best[i-k]+mincost[id][k];
        }
      }
      for(int i=0;i<=d;i++)best[i]=best2[i];
    }
  }
  for(int id=2;id<n+1;id++)
    if(!visited[id]){
      puts("NONE");
      return;
    }
  if(best[d]==MAX_COST){
    puts("NONE");
  }else{
    printf("%d\n",best[d]);
  }
}
int main(){
	int c;
	scanf("%d",&c);
	while(c--)
		solve();
}

