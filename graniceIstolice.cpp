#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
typedef pair<long long,long long> p2;
using namespace std;
struct border{
  int reversed;
  int country;
  int next;
  int color;
  int id;
  int pos;
  double alfa;
  p2 f;
  p2 t;
  border(p2 f,p2 t):reversed(-1),country(-1),next(-1),color(0),id(-1),pos(-1),f(f),t(t){
  	alfa= atan2( t.second-f.second, t.first-f.first);
  }
};
int m,n;
map< p2 , vector< int> > outgoing;
vector< border > bord;
vector< p2 > cap;
void addedge(p2 from,p2 to){
	bord.push_back( border(from,to) );
	bord.push_back( border(to,from) );
	int s=bord.size();
	bord[s-1].reversed=s-2;
	bord[s-2].reversed=s-1;
	bord[s-1].id=s-1;
	bord[s-2].id=s-2;
	outgoing[from].push_back( s-2 );
	outgoing[to].push_back( s-1 );
}
bool cmpang(const int & A,const  int &B){
	return bord[A].alfa<bord[B].alfa ;
}
bool inside( p2 p , vector<int> & cycle){
	int cnt=0;
	for(int i=0;i<cycle.size();i++){
		border & b=bord[cycle[i]];
		if(
			( b.f.second!=b.t.second)
			&&
			(
				( b.f.second>=p.second && b.t.second<p.second)
				||
				( b.f.second<=p.second && b.t.second>p.second)
			)
		){
			double x= (b.f.first*( b.t.second-p.second  ) + b.t.first*(p.second-b.f.second) )/(b.t.second-b.f.second )  ;
			if(x>= p.first)
				cnt++;
		}
	}
	return cnt&1;
}
int main(){
	while(1){
		scanf("%d %d",&n,&m);
		if(!n)
		  return 0;
		cap.clear();
		outgoing.clear();
		bord.clear();
		for(int i=0;i<n;i++){
	  	int x,y;
	  	scanf("%d %d",&x,&y);
	  	cap.push_back( p2(x,y) );
		}
		for(int i=0;i<m;i++){
			int x1,y1,x2,y2;
		  scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		  addedge( p2(x1,y1), p2(x2,y2) );
		}
		for(map<p2,vector<int> >::iterator i=outgoing.begin();i!=outgoing.end();++i){
			vector<int> & vec=i->second;
		  sort(vec.begin(),vec.end(),cmpang);
		  for(int e=0;e<vec.size();e++){
		  	bord[vec[e]].pos=e;
		  }
		  vec.push_back(vec.front());
		}
		for(int e=0;e<bord.size();e++)
			bord[e].next= outgoing[ bord[e].t ][ bord[bord[e].reversed].pos + 1 ];
		vector< vector<int> > cycles;
		vector< double > areas;
		for(int e=0;e<bord.size();e++){
			if(!bord[e].color){
				areas.push_back(0.0);
				cycles.push_back();
				for( ; !bord[e].color; e=bord[e].next){
					bord[e].color=1;
				  cycles.back().push_back(e);
				}
			}
		}
		for(int c=0;c<cycles.size();c++){
			for(int e=0;e<cycles[c].size();e++){
				border & b=bord[cycles[c][e]];
				areas[c]+= (b.t.first-b.f.first)*(b.t.second + b.f.second);
			}
			if(areas[c]<0)
				areas[c]=1e40;
		}
		vector<int> outside;
		for(int s=0;s<n;s++){
			double bestArea=1e20;
			int best=-1;
			for(int c=0;c<cycles.size();c++)
				if( areas[c] < bestArea && inside(cap[s],cycles[c] )){
					bestArea=areas[c];
					best=c;
				}
			for(int i=0;i<cycles[best].size();i++)
				bord[cycles[best][i]].country=s;

			outside.push_back(-1);
			bestArea=1e20;
			for(int c=0;c<cycles.size();c++){
      	if(c==best){
      		continue;
      	}else if( areas[c] < bestArea && inside(cap[s],cycles[c] )){
					bestArea=areas[c];
					outside.back()=c;
				}
			}
		}
		bool war[600][600];
		int cnt[600];
		for(int i=0;i<600;i++){
			cnt[i]=0;
			for(int j=0;j<600;j++){
				war[i][j]=false;
			}
		}
		for(int e=0;e<bord.size();e++){
			int k=bord[e].country;
			if(k>=0 ){
				int t=bord[bord[e].reversed].country;
				if(t<0 && outside[k]>=0)
			   	t=bord[cycles[outside[k]][0]].country;
			  if(t>=0){
					if(!war[ k ] [ t]){
						war[ k ] [ t ] = true;
						war[ t ] [ k ] = true;
						cnt[ k ] ++;
						cnt[ t ] ++;
					}
				}
			}
		}
		for(int i=0;i<n;i++){
			printf("%d",cnt[i] );
			for(int j=0;j<n;j++){
				if(war[i][j]){
					printf(" %d",j+1);
				}
			}
			printf("\n");
		}
	}
  return 0;
}
