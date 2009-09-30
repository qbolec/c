#include<vector>
#include<queue>
#include<iostream>
using namespace std;
int main(){
  int n,m;
  cin >> n >> m;
  vector< vector< pair <int, double> > >  G(n, vector< pair <int, double> > () );
  for(int i=0;i<m;i++){
    int a,b;
    double w;
    cin >> a >> b >> w;
    G[a].push_back( make_pair(b,w) );
  }
  priority_queue< pair<double,int>, vector< pair<double,int> > , greater< pair<double,int> > > q;
  vector<double> mind(n,1e60);
  q.push( make_pair(0,0));
  while(!q.empty()){
    int v=q.top().second;
    double d=q.top().first;
    q.pop();
    if(d<=mind[v])
      for(int i=G[v].size();i--;)
        if( d+G[v][i].second < mind[G[v][i].first]){
          mind[G[v][i].first]= d+G[v][i].second;
          q.push(make_pair(mind[G[v][i].first],G[v][i].first));
        }
  }
  cout << "Odleglosc z 0 do n-1 to " << mind[n-1] << endl;
}
