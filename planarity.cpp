#include<vector>
#include<utitlity>
using namespace std;
const int MAX_EDGES=400000;
const int MAX_NODES=100000;
typedef vector<vector<int>> Graf;
typedef vector<int> Tab;
int NEXT_[MAX_EDGES+1];
int * NEXT=NEXT_+1;
int f[MAX_EDGES+1];
int PATH[MAX_NODES];
int STACK[MAX_EDGES];
pair<int,int> B[MAX_EDGES];
Graf graf;
void PATHFINDER(int v){
  int s=0;
  int p=0;
  PATH.resize(graf.size());
  for(Tab::iterator w=graf[v].begin();w!=graf[v].end();++w){
    if(ENTERTIME[v]<ENTERTIME[w]){
      if(!s){
        s=v;
        p++;
      }
      PATH(w)=p;
      PATHFINDER(w);
      while(B.size() && (ENTERTIME[STACK[B.back().first]]>=ENTERTIME[v] || !B.back().first ) && (ENTERTIME[STACK[B.back().second]]>=ENTERTIME[v] || !B.back().second) )
        B.pop_back();
      if(B.size()){
        if(ENTERTIME[STACK[B.back().first]]>=ENTERTIME[v]){
          B.back().first=0;
        }
        if(ENTERTIME[STACK[B.back().second]]>=ENTERTIME[v]){
          B.back().second=0;
        }
      }      
      while(NEXT[-1] && ENTERTIME[STACK[NEXT[-1]]]>=ENTERTIME[v])
        NEXT[-1]=NEXT[NEXT[-1]];
      while(NEXT[0] && ENTERTIME[STACK[NEXT[0]]]>=ENTERTIME[v])
        NEXT[0]=NEXT[NEXT[0]];
      if(PATH[w]!=PATH[v]){
        int Lprim=0;
        while(B.size() && (ENTERTIME[STACK[B.back().first]]>ENTERTIME[f[PATH[w]]] ||ENTERTIME[STACK[B.back().second]]>ENTERTIME[f[PATH[w]]])&&(STACK[NEXT)){
        
        }
      }
    }
  }
}
