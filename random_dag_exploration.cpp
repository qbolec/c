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
#define zero(X) memset(X,0,sizeof(X));
const int MAX_n=20;
const int MAX_m=250;
const int TOT=MAX_n*MAX_m;
const int S=MAX_m*2;
namespace WMCM{
int n,w[S][S];
int m[2*S];
int lab[2*S],s[S],lam,sla[S],q[S],qb,qe,ba[S];
void clear(){
  n=0;
  zero(w);
  zero(m);
  zero(lab);
  zero(s);
  zero(sla);
  zero(q);
  zero(ba);
  lam=0;
  qb=0;
  qe=0;
}
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
int go(int id){
  for(int i=0;i<MAX_n;i++)
    todo[i].clear();
  seen.clear();
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
    id=cid;
    goto g;
  }else{
    vector<pair<int,int> > now,then;
    set<int> marked;
    assert(now.empty() && marked.empty() && then.empty());
    for(int i=dag[id].size();i--;){
      now.push_back(make_pair(dag[id][i],dag[id][i]));
      marked.insert(dag[id][i]);
    }
    sort(now.begin(),now.end());
    now.push_back(make_pair(0,0));
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
        id=how;
        goto g;
      }
      for(int i=dag[cid].size();i--;)
        if(!marked.count(dag[cid][i])){
          then.push_back(make_pair(dag[cid][i],how));
          marked.insert(dag[cid][i]);
        }
    }
    //still here?
    //printf("moves:%d seen:%d es=%d n=%d m=%d\n",moves,(int)seen.size(),es,n,m);
    return moves;
  }
}
const char * wiatrak="/|\\-";
int wiatrak_c;
int main(){
  srand(42);
  double largest_seen_ratio=1.01;
  while(true){
    n=2+rand()%(MAX_n-1);
    m=((rand()%MAX_m)+n-1)<?MAX_m;
    dag.clear();
    edges.clear();
    zero(nodeDist);
    dag.resize(n,vector<int>());
    WMCM::clear();
    for(int i=1;i<n;i++){
      int a=rand()%i;
      int b=i;
      dag[a].push_back(b);
      edges.push_back(make_pair(a,b));
    }
    for(int i=n-1;i<m;i++){
      int b=1+rand()%(n-1);
      int a=rand()%b;
      dag[a].push_back(b);
      edges.push_back(make_pair(a,b));
    }
    int algmoves=go(0);
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
    double ratio=(double)algmoves/moves;
    if(ratio<1.0){
      puts("WTF???");
      printf("%d %d\n",n,m);
      for(int i=0;i<n;i++)
        for(int j=dag[i].size();j--;)
          printf("%d %d\t",i,dag[i][j]);
      puts("\nWTF");
      printf("ALG: %d OPT :%d edges:%d nodes:%d ratio:%.3lf\n",algmoves,moves,m,n,ratio);
      system("PAUSE");
    }
    if(ratio>largest_seen_ratio){
      largest_seen_ratio=ratio;
      printf("%d %d\n",n,m);
      for(int i=0;i<n;i++)
        for(int j=dag[i].size();j--;)
          printf("%d %d\t",i,dag[i][j]);
      printf("\nALG: %d OPT :%d edges:%d nodes:%d ratio:%.3lf\n",algmoves,moves,m,n,ratio);
    }
    printf("\r%c%d",wiatrak[wiatrak_c++&3],wiatrak_c);
  }
}
