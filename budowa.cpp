#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
typedef pair<int, pair<int,int> > info; // (typ= -1 start , 0=check , 1=end)* ( y,id  lub  y1,y2 ) 
typedef pair<int,info> event;// x * info
int sat[25000];
int n,q;
vector<event> events;
set< pair<int,int> >  miotla;
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    int x1,y1,x2,y2;
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    x1*=2;
    y1*=2;
    x2*=2;
    y2*=2;    
    events.push_back( make_pair(x1, make_pair(-1, make_pair(y1,y2 ) ) ));
    events.push_back( make_pair(x2, make_pair(1, make_pair(y1,y2 ) ) ));
  }
  scanf("%d",&q);
  for(int i=0;i<q;i++){
    int x1,y1,x2,y2;
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    int x=x1+x2;
    int y=y1+y2;
    x1*=2;
    y1*=2;
    x2*=2;
    y2*=2;    
    events.push_back( make_pair(x1, make_pair(0,make_pair(y1,i)  )  ));
    events.push_back( make_pair(x1, make_pair(0,make_pair(y2,i)  )  ));
    events.push_back( make_pair(x2, make_pair(0,make_pair(y1,i)  )  ));
    events.push_back( make_pair(x2, make_pair(0,make_pair(y2,i)  )  ));
    events.push_back( make_pair(x, make_pair(0,make_pair(y,i)  )  ));
    events.push_back( make_pair(x, make_pair(0,make_pair(y,i)  )  ));
    events.push_back( make_pair(x, make_pair(0,make_pair(y,i)  )  ));
  }
  sort(events.begin(),events.end());
  for(int i=0;i<events.size();i++){
    switch(events[i].second.first){
      case -1:
          miotla.insert( make_pair( events[i].second.second.first , -1 ));
          miotla.insert( make_pair( events[i].second.second.second , 1 ));
      case 0:{
        set< pair<int,int> >::iterator j=miotla.upper_bound(make_pair( events[i].second.second.first,0) );
        if(j!= miotla.end() && (*j).second==1){
          sat[events[i].second.second.second]++;
        }
      }case 1:
          miotla.erase( make_pair( events[i].second.second.first , -1 ));
          miotla.erase( make_pair( events[i].second.second.second , 1 ));
    }
  }
  for(int i=0;i<q;i++)
    printf((sat[q]>2)?"TAK\n":"NIE\n");
}
