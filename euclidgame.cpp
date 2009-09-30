#include<cstdio>
#include<vector>
using namespace std;
int p,q;
int main(){
  while(1){
    scanf("%d%d",&p,&q);
    if(!p && !q)
      return 0;
    if(p<q){
      int t=p;
      p=q;
      q=t;
    }
    vector<int> g;
    while(q){
      g.push_back(p/q);
      int t=p%q;
      p=q;
      q=t;
    }
    bool start_wins=false;
    while(g.size()){
      start_wins=(g.back()>1)?true:!start_wins;
      g.pop_back();
    }
    puts(start_wins?"Stan wins":"Ollie wins");
  }
  return 0;
}
