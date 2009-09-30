#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define INF 10000

double sqr(double x) { return x*x; }

typedef pair<double,double> p2;

double dist(const p2 &a,const p2 &b) {
  return sqr(a.first-b.first)+sqr(a.second-b.second);
}

int main() {
  int n,i,j,active,current;
  double ans,x,y;
  vector<p2> tab;
  set<p2> s;
  set<p2>::const_iterator iter,iter2;
  p2 next;

  scanf("%d",&n);
  while (n) {
    tab.clear();
    while (n--) {
      scanf("%lf %lf",&x,&y);
      tab.push_back(p2(x,y));
    }
    sort(tab.begin(),tab.end());
    ans=INF*INF;
    active=0;
    s.clear();
    for (current=0; current<tab.size(); current++) {
      while (active<current && ans<sqr(tab[current].first-tab[active].first)) {
        s.erase(p2(tab[active].second,tab[active].first));
        active++;
      }
      next=p2(tab[current].second,tab[current].first);
      iter2=iter=s.lower_bound(next);
      i=0;
      while (iter2!=s.end() && i++<5)
        ans<?=dist(next,(p2)*iter2++);
      iter2=iter;
      while (iter2!=s.begin() && i++<10)
        ans<?=dist(next,(p2)*--iter2);
      s.insert(next);
    }
    if (ans<INF*INF)
      printf("%.4lf\n",sqrt(ans));
    else
      printf("INFINITY\n");
    scanf("%d",&n);
  }

  return 0;
}

