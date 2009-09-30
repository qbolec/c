#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct treenode{
  vector<treenode *> children;
  treenode * parent;  
  bool seen;
  bool visited;
  bool interesting;
  int dfs_start;
  int dfs_end;
  int name;
  treenode(treenode * parent,int name):parent(parent),name(name){
    children.clear();
    interesting=visited=seen=false;
    if(parent)
      parent->children.push_back(this);
  }
  void make_root(){
    if(!parent)return;
    parent->make_root();
    for(int i=parent->children.size();i--;)
      if(parent->children[i]==this){
        swap(parent->children[i],parent->children.back());
        parent->children.pop_back();
        parent->parent=this;
        children.push_back(parent);
        parent=0;
        break;
      }
  }
  int dfs(int t=0){
    dfs_start=t++;
    for(int i=children.size();i--;)
      t=children[i]->dfs(t);
    return dfs_end=t++;
  }
  void visit(){
    seen=visited=true;
    if(parent)parent->seen=true;
    for(int i=children.size();i--;)
      children[i]->seen=true;
  }
  bool isparentof(treenode * other){
    for(int i=children.size();i--;)
      if(children[i]==other)
        return true;
    return false;
  }
  treenode * moveup(int steps){
    if(!steps || !parent)
      return this;
    return parent->moveup(steps-1);
  }
  treenode * movetoward(treenode * goal){
    if(contains(goal)){
      for(int i=children.size();i--;)
        if(children[i]->contains(goal)){
          return children[i];          
        }      
    }else
      return parent;    
  }
  int distanceto(treenode * other){
    if(other==this)return 0;
    return 1+movetoward(other)->distanceto(other);
  }
  bool contains(treenode * other){
    return (dfs_start<= other->dfs_start && other->dfs_end <=dfs_end );    
  }
  vector<treenode *> seen_but_not_visited(){
    vector<treenode *> result;
    if(seen && !visited){
      result.push_back(this);
      return result;
    }
    for(int i=children.size();i--;){
      vector<treenode *> r=children[i]->seen_but_not_visited();
      copy(r.begin(),r.end(),back_inserter(result));
    }
    return result;
  }
};
struct bot{
  treenode * pos;
  treenode * goal;
  int battery;  
  int wastedbattery;
  
  bot(treenode * start):pos(start),goal(start),battery(0),wastedbattery(0){}
  void move(){
	if(goal==pos)
      return;
    pos=pos->movetoward(goal);
	if(!pos->visited)
	  pos->visit();
	else 
	  wastedbattery++;    
    battery++;
  }
};

struct matcher{
#define REP(x,n) for(int x=n;x--;)
#define S 1024

  int n;
  int lam,qb,qe;
  vector<int> lab,s,sla,q,ba,m;
  vector<vector<int> > w;
  void km3() {
    int f,of;
    REP(i,2*n) lab[i]=0, m[i]=-1;
    REP(i,n) REP(j,n) if(lab[i]<w[i][j]) lab[i] = w[i][j];
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
  	    lam=1000000000; REP(i,n)if(sla[i] && sla[i]<lam) lam=sla[i];
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
  void costofassigningAtoB(int A,int B,int cost){
    w[A][B]=1000000-cost;
  }
  matcher(int n):n(n),lab(2*n,0),s(n,0),sla(n,0),q(n,0),ba(n,0),m(2*n,0),w(n,vector<int> (n,0)){    
  }
};
vector<treenode *> moveup(vector<treenode *> ts,int steps){
  vector<treenode *> result;
  for(int i=ts.size();i--;)
    result.push_back( ts[i]->moveup(steps) );
  return result;
}

struct alg{
  vector<bot> bots;
  vector< vector<treenode *> >  goals;
  treenode * root;
  treenode * originalroot;
  void rebuild_and_rotate(){
    if(goals[0].size())
    for(int i=goals[0].size();i--;){
      treenode * e=goals[0][(i+1)%goals[0].size()];
      for(treenode * g=goals[0][i];g!=e;g=g->movetoward(e))
        g->interesting=true;
    }
    vector<treenode *> now,then;
    now=goals[0];
    treenode * lastprocessed;    
    while(now.size()||then.size()){
      if(!now.size())swap(now,then);
      lastprocessed=now.back();
      now.pop_back();
      if(!lastprocessed->interesting)
        continue;
      lastprocessed->interesting=false;
      if(lastprocessed->parent && lastprocessed->parent->interesting)
        then.push_back(lastprocessed->parent);
      for(int i=lastprocessed->children.size();i--;)
        if(lastprocessed->children[i]->interesting)
          then.push_back(lastprocessed->children[i]);
    }
    lastprocessed->make_root();
    root=lastprocessed;
	root->dfs();
  }
  void assign_goals(int totalgoals){
    vector<treenode *> flatgoals;	
    matcher m(totalgoals);
    for(int level=goals.size();level--;){
      for(int g=goals[level].size();g--;){
        for(int b=bots.size();b--;)
          m.costofassigningAtoB(b,flatgoals.size(),1000*level+bots[b].pos->distanceto(goals[level][g]));        
        flatgoals.push_back(goals[level][g]);
      }
    }
    m.km3();
    for(int b=bots.size();b--;)
      bots[b].goal=flatgoals[m.m[b]];
  }
  bool step(){
    goals.clear();
    goals.push_back(root->seen_but_not_visited());
	random_shuffle(goals[0].begin(),goals[0].end());
    int totalgoals=goals[0].size();
    if(!totalgoals){
      for(int i=bots.size();i--;)
        bots[i].goal=originalroot;
    }else{
      
      for(int step=1;totalgoals<bots.size();step++){
        goals.push_back(moveup(goals[step-1],1<<step));
        totalgoals+=goals[step].size();        
      }  
	  assign_goals(totalgoals);
    }
    
    for(int i=bots.size();i--;)
      bots[i].move();
	if(totalgoals){
		rebuild_and_rotate();
		return true;
	}
	for(int i=bots.size();i--;)
      if(bots[i].pos!=originalroot)
		  return true;
	return false;
  }
  void describe(){
    printf("bots:%d\n",bots.size());
	int totalwasted=0;
	int totalbattery=0;
	for(int i=0;i<bots.size();i++){
		printf("bot %c at node %d with goal %d (battery %d wasted %d)\n",'A'+i,bots[i].pos->name,bots[i].goal->name,bots[i].battery,bots[i].wastedbattery);
		totalwasted+=bots[i].wastedbattery;
		totalbattery+=bots[i].battery;
	}
	printf("CPR %d\n",totalbattery/((totalbattery-totalwasted)*2));
    puts("===");
  }
  alg(int k,treenode * root):root(root),originalroot(root){
    bots.resize(k,bot(root));
    root->dfs();
    root->visit();    
  }
};
int main(){
  treenode root(0,0);
  int k=40;
  treenode * hook=&root;
  int name=1;
  for(int i=0;i<k*100;i++){
    treenode * hook2=hook;
    for(int j=1;j<k;j++){
      hook2 = new treenode(hook2,name++);
    }
    hook=new treenode(hook,name++);
  }
  alg a(k,&root);
  int opt=2*(k*100+k);
  for(int step=0;step<opt*3;step++){
    printf("step: %d\n",step);
    if(!a.step())
		break;
    a.describe();
  }
  a.describe();
}
