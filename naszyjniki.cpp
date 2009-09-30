#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
char t[9000];
int prev[9000][26];
int n;
int bestCut;
int bestResult;
short r[2][9000];
short c[2][9000];
void palindrome(){
  for(int from=0;from<2;from++)
    for(int to=0;to<n;to++){
      r[from][to]=0;
      c[from][to]=0;
    }
  for(int from=n-1;from>=0;from--){
    int fake_from=from&1;
    int fake_from_plus_1=!fake_from;
    for(int to=0;to<from;to++)
      r[fake_from][to]=c[fake_from][to]=0;
    for(int to=from;to<n;to++){
      if(t[from]==t[to]){
        if(from==to){
          r[fake_from][to]=0;
          c[fake_from][to]=from-1;
        }else{
          r[fake_from][to]=1+r[fake_from_plus_1][to-1];
          if(from+1==to)
            c[fake_from][to]=from;
          else
            c[fake_from][to]=c[fake_from_plus_1][to-1];
        }
      }else{
        if(r[fake_from_plus_1][to] > r[fake_from][to-1]){
          r[fake_from][to]=r[fake_from_plus_1][to];
          c[fake_from][to]=c[fake_from_plus_1][to];
        }else{
          r[fake_from][to]=r[fake_from][to-1];
          c[fake_from][to]=c[fake_from][to-1];
        }
      }
    }
  }
  bestResult=r[0][n-1];
  bestCut=c[0][n-1];
}
vector< vector< pair<int,int> > > pasmo;
bool dominates(const pair<int,int> &A,const pair<int,int> &B){
  return A.first<B.first && A.second<B.second;
}
bool kills(const pair<int,int> &A,const pair<int,int> &B){
  return A.first<=B.first && A.second<=B.second;
}
void dump(char * text="DUMPING\n"){
///*
  printf("%s\n",text);
  printf("pasmo.size=%d\n",pasmo.size());
  for(int i=0;i<pasmo.size();i++){
    printf("pasmo[%d].size=%d\n",i,pasmo[i].size());
    for(int j=0;j<pasmo[i].size();j++){  
      printf("pasmo[%d][%d]=(%d,%d)\n",i,j,pasmo[i][j].first,pasmo[i][j].second);
    }
  }
//*/
}
void lcses(){
  for(int i=0;i<26;i++)
    prev[0][i]=-1;
  for(int p=1;p<=n;p++)
    for(int i=0;i<26;i++)
      if(t[p-1]==i)
        prev[p][i]=p-1;
      else
        prev[p][i]=prev[p-1][i];
  pasmo.clear();
  //first = row = prefix
  //second = col = suffix
  int suffix_len=0;
  int prefix_len=n;
  pasmo.push_back();
  pasmo[0].push_back( make_pair( n,n ));
  while(1){
    printf("\n\n CUT:%d\n\n",prefix_len);
    dump("Delete");
    if(pasmo.size()-1>=bestResult){
      if(pasmo.size()-1>bestResult){
        bestResult=pasmo.size()-1;
        bestCut=prefix_len-1;
      }else{
        if(prefix_len-1<bestCut)
          bestCut=prefix_len-1;
      }
    }
    if(prefix_len<2)
      break;
    //shrink prefix:
    //1.delete 
    prefix_len--;
    if(pasmo.size()>1 && pasmo[1].size() && pasmo[1].back().first==prefix_len){
      int col=pasmo[1].back().second;
      int row=prev[prefix_len][t[col]];
      pasmo[1].pop_back();
      if(row!=-1){
        if(!pasmo[1].size() || pasmo[1].back().first<row)
          pasmo[1].push_back(make_pair(row,col));
      }
      //2.reduse unused
      dump("Reduse");
      if(!pasmo[1].size()){
        for(int l=2;l<pasmo.size();l++)
          swap(pasmo[l-1],pasmo[l]);
        pasmo.pop_back();
      }
      //3.merge fragments
      dump("Merge");
      int last=1;
      for(int l=2;l<pasmo.size();l++){
        vector< pair<int,int> > moveme;
        while(pasmo[l].size() && pasmo[l].back().second < pasmo[last].back().second
            && pasmo[l].back().first >= pasmo[last].back().first){
            //if(pasmo[l].back().first > pasmo[last].back().first)
            moveme.push_back( pasmo[l].back());
            pasmo[l].pop_back();
        }
        while(moveme.size()){
          //wyznaczanie nastepcy:
          int row=moveme.back().first;
          int col=moveme.back().second;
          row= prev[row][t[col]];
          while(row!=-1 && row>=pasmo[last].back().first)
            row= prev[row][t[col]];
          if(row!=-1){
            if(!pasmo[l].size() || pasmo[l].back().first<row)
              pasmo[l].push_back(make_pair(row,col));  
          }
          if(moveme.back().first > pasmo[last].back().first)
            pasmo[last].push_back( moveme.back() );
          moveme.pop_back();
        }
        if(pasmo[l].size()){
          last=l;
        }
      }
      //4.again reduce unused
      dump("Again");
      int free=0;
      for(int l=0;l<pasmo.size();l++)
        if(pasmo[l].size())
          swap(pasmo[free++],pasmo[l]);
      while(pasmo.size()>free)
        pasmo.pop_back();
    }    
    //2.enlarge
    dump("Enlarge");
    suffix_len++;
    int col=n-suffix_len;
    int row=prev[prefix_len][t[col]];
    int l=0;
    while(row!=-1){
      while(l<pasmo.size() && row< pasmo[l].back().first)
        l++;
      if(l==pasmo.size()){
        if( pasmo[l-1].back().second==col ){
          if(pasmo[l-1].size()>1 && row<pasmo[l-1][pasmo[l-1].size()-2].first){
            pasmo.push_back();
            pasmo[l].push_back( make_pair(row,col));          
          }
        }else{
          pasmo.push_back();
          pasmo[l].push_back( make_pair(row,col));
        }
      }else if( row==pasmo[l].back().first ){
//        pasmo[l].back().second=col;
      }else if( pasmo[l-1].back().second==col ){
        if(pasmo[l-1].size()>1 && row<pasmo[l-1][pasmo[l-1].size()-2].first)
          pasmo[l].push_back( make_pair(row,col));
      }else
        pasmo[l].push_back( make_pair(row,col));
      row= prev[row][t[col]];
    } 
    dump("Costam");
  }
}
void solve(){
  bestCut=0;
  bestResult=0;
  scanf(" %s",t);
  n=strlen(t);
  for(int i=0;i<n;i++)
    t[i]-='a';
  palindrome();
  lcses();
  printf("%d %d\n",bestResult*2,bestCut+1);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
  return 0;
}
