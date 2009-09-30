#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> jtoy;
typedef pair<int,int> p2;
typedef pair<int,p2> p3;//x,y1,y2
vector<p3> pad,pbc;
//ab
//cd
int n,c,g;
long long wynik;
struct node{
  int b,c,u,d;
  bool neg;  
};
node tree[5000];
long long len(int d,int u,int parity){
  // | { x :  d<=x < u  &&  x&1 == parity } |
  if((d&1) != parity) d++;
  if((u&1) != parity) u++;
  return (u-d)/2;
}
void init_tree(int parity){
  g=jtoy.size()-1;
  int l=g*2-1;
  int p=l;
  while(p&(p-1))p--;  
  int i=0;
  for(int z=p;;z++,i++){
    tree[z].u=jtoy[i+1];
    tree[z].d=jtoy[i];
    tree[z].b=len(tree[z].d,tree[z].u,parity);
    tree[z].c=0;    
    tree[z].neg=false;
    if(z==l)
      z=g-1;
    if(z==p-1)
      break;
  }
  for(int z=g-1;z;z--){
    tree[z].u=tree[z*2+1].u;
    tree[z].d=tree[z*2].d;
    tree[z].b=tree[z*2].b+tree[z*2+1].b;
    tree[z].c=0;
    tree[z].neg=false;
  }  
}
void invert(int d,int u,int z=1){
  if(d>=tree[z].u || u<=tree[z].d)
    return;
  if( d <=tree[z].d && tree[z].u<=u ){
    tree[z].neg=!tree[z].neg;
    swap(tree[z].b,tree[z].c);
    return;
  }else{
    invert(d,u,z*2);
    invert(d,u,z*2+1);
    tree[z].b=tree[z*2].b+tree[z*2+1].b;
    tree[z].c=tree[z*2].c+tree[z*2+1].c;
    if(tree[z].neg)
      swap(tree[z].b,tree[z].c);
  }
}
void proc(vector<p3> & ev,int pairityX,int pairityY){
  init_tree(pairityY);
  int x=0;
  for(int i=0;i<ev.size();i++){
    wynik+= len(x,ev[i].first,pairityX) * tree[1].c;
    invert(ev[i].second.first,ev[i].second.second);  
    x=ev[i].first;
  }  
}
int main(){
  scanf("%d",&c);
  while(c--){
    pad.clear();
    pbc.clear();
    jtoy.clear();
    scanf("%d",&n);
    for(int i=0;i<n;i++){
      int x1,x2,y1,y2;
      scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
      x2++;
      y2++;
      if((x1^y1)&1){//bc
        pbc.push_back(p3(x1, p2(y1,y2)));
        pbc.push_back(p3(x2, p2(y1,y2)));
      }else{//obie parzyste lub obie nieparzyste czyli ad
        pad.push_back(p3(x1, p2(y1,y2)));
        pad.push_back(p3(x2, p2(y1,y2)));
      }
      jtoy.push_back(y1);
      jtoy.push_back(y2);      
    }
    sort(jtoy.begin(),jtoy.end());
    jtoy.erase(unique(jtoy.begin(),jtoy.end()),jtoy.end());
    sort(pbc.begin(),pbc.end());
    sort(pad.begin(),pad.end());
    wynik=0;
    proc(pad,0,0);//A
    proc(pbc,1,0);//B
    proc(pbc,0,1);//C 
    proc(pad,1,1);//D 
    printf("%lld\n",wynik);     
  }  
  return 0;
}
