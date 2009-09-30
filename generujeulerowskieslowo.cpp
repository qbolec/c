#include<cstdio>
#include<vector>
//nie dziala dla k=1, i wypadaloby tez wypisac na koncu etykiete wierzcholka czasem
using namespace std;
vector< vector<int> > graf;
void go(int id){
  if(!graf[id].size())return;
  int j=graf[id].back();
  graf[id].pop_back();
  go(j);
  putchar('a' + j%4 );
  go(id);
}
void solve(){
  int k;
  scanf("%d",&k);
  int n=1;
  for(int i=1;i<k;i++)
    n*=4;
  graf.clear();
  graf.resize( n );
  for(int i=0;i<n;i++)
    for(int a=0;a<4;a++)
      graf[i].push_back( (i * 4 + a) % n );
  go(0);  
}
int main(){
  int z;
  scanf("%d",&z);
  while(z--)
    solve();
  return 0;
}
