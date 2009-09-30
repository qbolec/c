#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX_K 100
#define MAX_Q 100000
#define MAX_P 100000
#define INF 1100000000
int p[MAX_K],ans[MAX_Q],d[MAX_P],id[MAX_P],next_id,first[MAX_P],last[MAX_P];
typedef pair<int,int> p2;
struct node {
  int d,r;
  node(int _d,int _r) { d=_d; r=_r; }
  bool operator<(const node &n) const { return d>n.d; }
};

int main() {
  int c,k,q,i,j,r;

  scanf("%d",&c);
  while (c--) {
    vector<p2> e;
    priority_queue<node> t;
    
    scanf("%d %d",&k,&q);
    for (i=0; i<k; i++) scanf("%d",p+i);
    sort(p,p+k);
    d[0]=0;
    for (i=1; i<p[0]; i++) d[i]=INF;
    t.push(node(0,0));
    next_id=0;
    for (i=0; i<p[0]; i++) id[i]=next_id;
    first[next_id]=0;
    last[next_id++]=p[0];
    for (i=0; i<q; i++) {
      scanf("%d",&j);
      e.push_back(p2(j,i));
    }
    sort(e.begin(),e.end());
    i=0;
    while (i<e.size())
      if (!t.empty() && d[t.top().r]<=e[i].first) {
        r=t.top().r; t.pop();
        if (r-first[id[r]]<last[id[r]]-r) {
          first[next_id]=first[id[r]];
          last[next_id]=r;          
          first[id[r+1]]=r+1;
          for (j=first[next_id]; j<=last[next_id]; j++) id[j]=next_id;          
          next_id++;
        } else {
          first[next_id]=r+1;
          last[next_id]=last[id[r]];
          last[id[r]]=r;
          for (j=first[next_id]; j<=last[next_id]; j++) id[j]=next_id;
          next_id++;
        }
        for (j=0; j<k; j++) if (d[r]+p[j]<d[(r+p[j])%p[0]]) t.push(node(d[(r+p[j])%p[0]]=d[r]+p[j],(r+p[j])%p[0]));
      } else {
        ans[e[i].second]=e[i].first-e[i].first%p[0]+last[id[e[i].first%p[0]]];
        if (!t.empty()) ans[e[i].second]<?=d[t.top().r];
        i++;
      }
    for (i=0; i<q; i++) printf("%d\n",ans[i]);
  }

  return 0;
}
