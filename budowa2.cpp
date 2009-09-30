#include<utility>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
int n,q;
typedef pair<int,int> rest;// y1,y2  lub y,what
typedef pair<int,rest > info;// typ
typedef pair<int,info> event;//x
vector<event> ev;
vector<int> c;
map<int,int> miotla;
void pkt(int x,int y,int id){
  ev.push_back(make_pair(x,make_pair(-2,make_pair(y,id))));
  ev.push_back(make_pair(x,make_pair(2,make_pair(y,id))));
}
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    int l,b,t,r;
    scanf("%d%d%d%d",&l,&b,&r,&t);
    ev.push_back(make_pair(l*2,make_pair(1,make_pair(b*2 ,t*2 ) )));
    ev.push_back(make_pair(r*2,make_pair(-1,make_pair(b*2 ,t*2 ) )));
  }
  scanf("%d",&q);
  for(int i=0;i<q;i++){
    int l,b,t,r;
    scanf("%d%d%d%d",&l,&b,&r,&t);
    pkt(l*2,b*2,7*i+0);
    pkt(l*2,t*2,7*i+1);
    pkt(r*2,b*2,7*i+2);
    pkt(r*2,t*2,7*i+3);
    pkt(r+l,b+t,7*i+4);
    pkt(r+l,b+t,7*i+5);
    pkt(r+l,b+t,7*i+6);
  }
  c.resize(q*7,0);
  sort(ev.begin(),ev.end());
  for(int i=0;i<ev.size();i++){
    switch(ev[i].second.first){
      case -2:
      case 2:{
          map<int,int>::iterator it=miotla.lower_bound( ev[i].second.second.first );
          if(it!=miotla.end() && (it->first==ev[i].second.second.first || it->second==1) )
            c[ev[i].second.second.second]=1;          
        }
        break;
      case -1:
        miotla[ev[i].second.second.first]++;
        if(!miotla[ev[i].second.second.first])
          miotla.erase(ev[i].second.second.first);
        miotla[ev[i].second.second.second]--;
        if(!miotla[ev[i].second.second.second])
          miotla.erase(ev[i].second.second.second);
        break;
      case 1:
        miotla[ev[i].second.second.first]--;
        if(!miotla[ev[i].second.second.first])
          miotla.erase(ev[i].second.second.first);
        miotla[ev[i].second.second.second]++;
        if(!miotla[ev[i].second.second.second])
          miotla.erase(ev[i].second.second.second);
        break;
    }
  }
  for(int i=0;i<q;i++)
    printf(c[7*i]+c[7*i+1]+c[7*i+2]+c[7*i+3]+c[7*i+4]+c[7*i+5]+c[7*i+6]>2?"TAK\n":"NIE\n");
}
  
