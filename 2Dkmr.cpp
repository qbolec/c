#include<cstdio>
#include<utility>
#include<algorithm>
#include<vector>
using namespace std;
//jako funkcje hashujaca wezmiemy sobie
int N,n;
const int MAX_N=128;
char T[MAX_N][MAX_N];
char t[4][MAX_N][MAX_N];
short int H[MAX_N][MAX_N];
short int h[4][MAX_N][MAX_N];
int ok[4];
vector< pair<pair<pair<short int,short int>, pair<short int,short int> >, short int *> > hashes;
void collect(short int hash[][MAX_N],int N,int l){
  for(int r=0;r+l<N;r++)
    for(int c=0;c+l<N;c++)
      hashes.push_back(make_pair(
        make_pair(
          make_pair(hash[r][c],hash[r+l][c]),
          make_pair(hash[r][c+l],hash[r+l][c+l])
        ),
        &hash[r][c]
      ));
}
void pack(){
  * hashes.back().second = 0;
  int w=hashes.size()-1;
  int a=0;
  for(int i=hashes.size()-1;i--;){
    if(hashes[i].first!=hashes[w].first){
      w=i;
      a++;
    }
    *hashes[i].second=a;      
  }
}
void combine(int l){
  hashes.clear();
  collect(H,N,l);
  for(int v=4;v--;)
    collect(h[v],n,l);
  sort(hashes.begin(),hashes.end());
  pack();    
}
int main(){
  while(1){
    scanf("%d %d",&N,&n);
    if(!n && !N)
      return 0;
    for(int i=0;i<N;i++)
      scanf(" %s",T+i);
    for(int i=0;i<n;i++)
      scanf(" %s",t[0]+i);
    for(int v=1;v<4;v++)
      for(int r=0;r<n;r++)
        for(int c=0;c<n;c++)
          t[v][r][c]=t[v-1][n-c-1][r];        
    for(int v=4;v--;)
      for(int r=0;r<n;r++)
        for(int c=0;c<n;c++)
          h[v][r][c]=t[v][r][c];
    for(int r=0;r<N;r++)
      for(int c=0;c<N;c++)
        H[r][c]=T[r][c];
    int l;
    for(l=1;2*l<=n;l*=2)
      combine(l);
    if(n!=l)
      combine(n-l);
    for(int v=4;v--;){
      ok[v]=0;
      for(int r=0;r<N;r++)
        for(int c=0;c<N;c++)        
          if(h[v][0][0]==H[r][c])
            ok[v]++;
    }    
    printf("%d %d %d %d\n",ok[0],ok[1],ok[2],ok[3]);
  }
}
