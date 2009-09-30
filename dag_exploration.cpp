#include<cstdio>
#include<vector>
#include<cassert>
#include<set>
#include<algorithm>
//#define VERBOSE

using namespace std;
int n,m;
vector< vector<int> > dag;
#define REP(i,n) for(int i=0;i<n;i++)
const int MAX_n=500;
const int MAX_m=500;
const int TOT=MAX_n*MAX_m;
const int S=MAX_m*2;
namespace WMCM{
int n,w[S][S];
int m[2*S];
int lab[2*S],s[S],lam,sla[S],q[S],qb,qe,ba[S];

void km3() {
  int f,of;
  REP(i,2*n) lab[i]=0, m[i]=-1;
  REP(i,n) REP(j,n) lab[i] >?= w[i][j];
  REP(faza,n) {
    REP(i,n) s[i]=0, sla[i]=1000000000; qb=qe=0;
    REP(i,n) if (m[i]==-1) s[ q[qe++]=i ]=1;
    f=-1;
    for(;;) {
	    while (qb!=qe) {
	      int v=q[qb++];
	      REP(i,n) if (sla[i] > lab[v]+lab[i+n]-w[v][i]) {
	        sla[i]=lab[v]+lab[i+n]-w[v][i]; ba[i]=v;
	        if (sla[i]==0) {
		        if (m[i+n]==-1) { f=i; goto kon; }
		        else if (!s[m[i+n]]) s[ q[qe++]=m[i+n] ]=1;
	        }
	      }
	    }
	    lam=1000000000; REP(i,n)if(sla[i]) lam<?=sla[i];
      REP(i,n) if (s[i]) lab[i]-=lam;
      REP(i,n) if (sla[i]==0) lab[i+n]+=lam; else sla[i]-=lam;
	    REP(i,n) if (sla[i]==0) {
	      if (m[i+n]==-1) { f=i; goto kon; }
	      else if (!s[m[i+n]]) s[ q[qe++]=m[i+n] ]=1;
	    }
    }
kon:
    while (f!=-1) { m[f+n]=ba[f]; of=m[ba[f]]; m[ba[f]]=f; f=of; }
   }
}
};

vector<pair<int,int> > edges;
int nodeDist[MAX_n][MAX_n];
vector<int> todo[MAX_n];
set<int> seen;
set<pair<int,int> > traversed;
void go(int id){
int moves=0;
int es=0;
g:moves++;
#ifdef VERBOSE
  printf("visit node %d\n",id);
#endif
  if(!seen.count(id)){
    todo[id]=dag[id];
    sort(todo[id].begin(),todo[id].end());
    seen.insert(id);
  }
  if(todo[id].size()){
    int cid=todo[id].back();
    todo[id].pop_back();
    es++;
    traversed.insert(make_pair(id,cid));
    id=cid;
    goto g;
  }else{
    vector<pair<int,int> > now,then;
    set<int> marked;
    for(int i=0;i<dag[id].size();i++){
      now.push_back(make_pair(dag[id][i],dag[id][i]));
      marked.insert(dag[id][i]);
    }
    now.push_back(make_pair(0,0));
    sort(now.begin(),now.end());
    marked.insert(0);
    while(!now.empty()||!then.empty()){
      if(now.empty()){
        swap(then,now);
        sort(now.begin(),now.end());
      }
      int cid=now.back().first;
      int how=now.back().second;
      now.pop_back();
      if(!todo[cid].empty()){
        if(how)
          traversed.insert(make_pair(id,how));
        id=how;
        goto g;
      }
      for(int i=0;i<dag[cid].size();i++)
        if(!marked.count(dag[cid][i])){
          then.push_back(make_pair(dag[cid][i],how));
          marked.insert(dag[cid][i]);
        }
    }
    //still here?
    printf("moves:%d traversed:%d seen:%d es=%d n=%d m=%d\n",moves,(int)traversed.size(),(int)seen.size(),es,n,m);
    return;
  }
}
int main(){
  scanf("%d %d",&n,&m);
  dag.resize(n,vector<int>());
  for(int i=0;i<m;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    assert(a<b);
    dag[a].push_back(b);
    edges.push_back(make_pair(a,b));
  }
  go(0);
  for(int i=n;i--;){
    nodeDist[i][i]=TOT-0;
    for(int j=dag[i].size();j--;){
      int k=dag[i][j];
      nodeDist[i][k]=TOT-1;
      for(int l=i+1;l<n;l++){
        nodeDist[i][l]>?=nodeDist[k][l]-1;
      }
    }
  }
  for(int i=m;i--;)
    for(int j=m;j--;){
      WMCM::w[i][j]=0>?(nodeDist[edges[i].second][edges[j].first]-1);
      WMCM::w[m+i][j]=0>?(nodeDist[0][edges[j].first]-1);
      WMCM::w[i][m+j]=TOT-1;
      WMCM::w[m+i][m+j]=TOT-0;
    }
  WMCM::n=2*m;
  WMCM::km3();
  int moves=0;
  for(int i=0;i<m;i++)
    if(WMCM::m[m+i]<m){
#ifdef VERBOSE
      puts("start from the root ...");
      puts("\tvisit the node 0");
#endif
      int id=WMCM::m[m+i];
      int where=0;
      while(id<m){
#ifdef VERBOSE
        printf("go to the edge %d->%d\n",edges[id].first,edges[id].second);
#endif
        while(where!=edges[id].first){
          for(int j=dag[where].size();j--;)
            if(nodeDist[where][edges[id].first]==nodeDist[dag[where][j]][edges[id].first]-1){
              where=dag[where][j];
              break;
            }
          moves++;
#ifdef VERBOSE
          printf("\tvisit the node %d\n",where);
#endif
        }
        where=edges[id].second;
        moves++;
#ifdef VERBOSE
        printf("\tvisit the node %d\n",where);
#endif
        id=WMCM::m[id];
      }
      moves++;
    }
  printf("OPT moves:%d edges:%d\n",moves,m);
}
