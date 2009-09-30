#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
typedef pair<int,int> p2;
#define X first
#define Y second
p2 operator - (const p2 & a,const p2 & b){
  return p2(a.X-b.X,a.Y-b.Y);
}
long long operator *(const p2 & a,const p2 & b){
  return ((long long)a.X*b.Y)-((long long)a.Y*b.X);
}
bool na_prawo(const p2 &a,const p2 &b){
  return a*b<0LL;
}
bool skret_w_prawo(p2 &a,p2 &b,p2 &c){
  return na_prawo(b-a,c-b);
}
void solve(){
  int n;
  scanf("%d",&n);
  p2 w[n+1];
  for(int i=0;i<n;i++){
    p2 p;
    scanf("%d %d",&p.X,&p.Y);
    w[i]=p;
  }
  int mini=0;
  for(int i=1;i<n;i++)
    if(w[i]>w[mini])
      mini=i;
  rotate(w,w+mini,w+n);
  w[n++]=w[0];
  stack<int> s;
  s.push(0);
  s.push(1);
  for(int i=2;i<n;i++){
    printf("\tprzetwarzam (%d,%d)\n",w[i].X,w[i].Y);
    while(s.size()>1){
      int last=s.top();
      s.pop();
      int prev=s.top();
      if(skret_w_prawo(w[prev],w[last],w[i])){
        s.push(last);
        break;
      }
      printf("removed (%d,%d)\n",w[last].X,w[last].Y);
    }
    if(s.size()==1){
      printf("push (%d,%d)\n",w[i].X,w[i].Y);
      s.push(i);
    }else{
      int last=s.top();
      int prev=last-1;//tak wlasnie
      if(skret_w_prawo(w[prev],w[last],w[i])){
        printf("pusch (%d,%d)\n",w[i].X,w[i].Y);
        s.push(i);
      } else{
        printf("punkt %d (%d,%d) wchodzi do wnetrza\n",i,w[i].X,w[i].Y);
        s.pop();
        prev=s.top();
        for(int j=i;j<n;j++)
          if(na_prawo(w[last]-w[prev],w[j]-w[prev])){
            printf("punkt %d (%d,%d) jest wewnatrz\n",j,w[j].X,w[j].Y);
            i=j;
          }else
            break;
        s.push(last);
      }
    }
  }
  puts("otoczka");
  while(!s.empty()){
    printf("%d (%d,%d)\n",s.top(),w[s.top()].X,w[s.top()].Y);
    s.pop();
  }
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
  return 0;
}
