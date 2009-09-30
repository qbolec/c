#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int x1[300];
int y1[300];
int x2[300];
int y2[300];
int W,H,w,h,n;
bool overlap(int i,int x,int y){
  int l= x1[i] >? x;
  int r= x2[i] <? x+w;
  int b= y1[i] >? y;
  int t= y2[i] <? y+h;
  return (l<r && b<t);    
}
void solve(){
  scanf("%d %d %d",&n,&W,&H);
  for(int i=0;i<n;i++){    
    scanf("%d %d %d %d",x1+i,y1+i,x2+i,y2+i);
  }
  scanf("%d %d",&w,&h);
  vector<int> xs;
  vector<int> ys;  
  for(int i=0;i<n;i++){
    xs.push_back(x2[i]);
    ys.push_back(y2[i]);
  }
  xs.push_back(0);
  ys.push_back(0);
  sort(xs.begin(),xs.end());
  xs.erase(unique(xs.begin(),xs.end()) ,xs.end());
  sort(ys.begin(),ys.end());
  ys.erase(unique(ys.begin(),ys.end()) ,ys.end());
  for(int b=0;b<ys.size();b++)
    for(int l=0;l<xs.size();l++){
      int x=xs[l];
      int y=ys[b];
      if(x+w>W || y+h>H)
        continue;
      bool dupa=false;
      for(int i=0;i<n;i++)
        if(overlap(i,x,y)){
          dupa=true;
          break;
        }
      if(!dupa){
        printf("%d %d\n",x,y);
        return;
      }
    }
  puts("Fail!");
}
int main(){
  int c;
  scanf("%d",&c);
  while(c--)
    solve();
}
