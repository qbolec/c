#include<cstdio>
#include<vector>
using namespace std;
vector<vector< pair<int,int> > > graf;
vector<vector< pair<int,int> > > grafR;
int from[10010];
int toward[10010];
int bilans[10010];
int sum[10010];
bool find(int fr,int to){
  if(fr==to)return true;
  for(int i=graf[fr].size();i--;)
    if(!from[graf[fr][i].first]){
      from[graf[fr][i].first]=fr;
      if(find(graf[fr][i].first,to)){
        toward[fr]=graf[fr][i].first;
        return true;
      }
    }
  return false;
}
void solve(){
  memset(from,0,sizeof(from));
  memset(bilans,0,sizeof(bilans));
  memset(sum,0,sizeof(sum));
  int n;
  scanf("%d",&n);
  vector<vector< pair<int,int> > > g(n+1,vector< pair<int,int> >());
  vector<vector< pair<int,int> > > gR(n+1,vector< pair<int,int> >());
  for(int i=1;i<n;i++){
    int a,b,cab,cba;
    scanf("%d %d %d %d",&a,&b,&cab,&cba);
    sum[a]+=cba;
    sum[b]+=cab;
    bilans[a]+=cba-cab;
    bilans[b]+=cab-cba;
    g[a].push_back(make_pair(b,cab));
    gR[a].push_back(make_pair(b,cba));
    g[b].push_back(make_pair(a,cba));
    gR[b].push_back(make_pair(a,cab));
  }
  swap(g,graf);
  swap(gR,grafR);
  int fr,to;
  scanf("%d %d",&fr,&to);
  from[fr]=-1;
  find(fr,to);
  int minimum=sum[to];
  int maximum=sum[to];
  for(int i=from[to];i!=fr;i=from[i]){
    int f=from[i];
    int t=toward[i];
 //   printf(" f%d  ->  i%d  -> t%d\n",f,i,t);
    int fj,tj;
    for(int j=graf[i].size();j--;)
      if(graf[i][j].first==f)
        fj=j;
      else if(graf[i][j].first==t)
        tj=j;
    int input=grafR[i][fj].second;
    int output=graf[i][tj].second;
    int minimum_lokalne=0>?(input-(sum[i]-graf[i][fj].second-graf[i][tj].second));
    int maximum_lokalne=input<?output;
//    printf("s: %d %d\n",minimum_lokalne,maximum_lokalne);
    for(int j=graf[i].size();j--;)
      if(j==fj)
        continue;
      else if(j==tj){
        minimum_lokalne>?=((grafR[i][j].second+input)-(sum[i]-output));
//        printf("ujscie mowi ze minimum to %d\n",((grafR[i][j].second+input)-(sum[i]-output)));
      }else{
        maximum_lokalne<?=output-(0>?grafR[i][j].second-(sum[i]-graf[i][j].second-output));
//        printf("wierzcholek %d, twierdzi ze nie wiecej jak %d\n",graf[i][j].first,output-(0>?grafR[i][j].second-(sum[i]-graf[i][j].second-output)));
      }
//    printf("lokalne minimum: %d , maximum:%d\n",minimum_lokalne,maximum_lokalne);
    maximum<?=maximum_lokalne;
    minimum= (minimum_lokalne-(output-minimum))>?0 ;
  }
  printf("%d %d\n",minimum,maximum);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
  return 0;
}
