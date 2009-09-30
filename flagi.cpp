#include<cstdio>
#include<algorithm>
using namespace std;
pair<int,int> p[50];
unsigned int m;
struct matrix{
  unsigned int a[30][30];
  matrix(){memset(a,0,sizeof(a));}
};
matrix multo(matrix x,matrix y){//to dziala dla symetrycznych tylko:)
  matrix r;
  for(int i=30;i--;)
  for(int j=i+1;j--;){
    unsigned long long d=0ULL;
    for(int k=30;k--;)
      d+=(unsigned long long)x.a[i][k]*y.a[j][k]%m;
    r.a[j][i]=r.a[i][j]=d%m;
  }
  return r;
}
matrix powerade(matrix x,int k){
  matrix r;
  for(int i=30;i--;)r.a[i][i]=1;
  for(int i=0;k&&i<31;i++){
    if(k&1){
      r=multo(r,x);
      k>>=1;
    }
    x=multo(x,x);
  }
  return r;
}
int main(){
  int n,k,r;
  scanf("%d %u %d",&n,&m,&k);
  matrix a;
  for(int i=0;i<k;i++)
    for(int j=i;j<k;j++){
      scanf("%u",&a.a[i][j]);
      a.a[j][i]=a.a[i][j];
    }
  scanf("%d",&r);
  for(int i=0;i<r;i++)
    scanf("%d %d",&p[i].first,&p[i].second);
  sort(p,p+r);
  r=unique(p,p+r)-p;
  for(int i=1;i<r;i++)
    if(p[i].first==p[i-1].first){
      puts("0");
      return 0;
    }
  unsigned int result=1;
  for(int i=0;i<r;i++){
    if(i){
      matrix g=powerade(a,p[i].first-p[i-1].first);
      result=((long long)result * g.a[p[i-1].second-1][p[i].second-1])%m;
    }else{
      matrix g=powerade(a,p[i].first-1);
      unsigned int new_result=0;
      for(int j=k;j--;)
        new_result=(new_result+(unsigned int)(((long long)result * g.a[j][p[i].second-1])%m))%m;
      result=new_result;
    }
    if(!result)break;
  }
  if(!r){
    matrix g=powerade(a,n-1);
    unsigned int new_result=0;
    for(int j=k;j--;)
    for(int i=k;i--;)
      new_result=(new_result+g.a[i][j])%m;
    result=new_result;
  }else if(p[r-1].first!=n){
    matrix g=powerade(a,n-p[r-1].first);
    int new_result=0;
    for(int j=k;j--;)
      new_result=((unsigned int)new_result+(unsigned int)(((long long)result * g.a[p[r-1].second-1][j])%m))%m;
    result=new_result;
  }
  printf("%d\n",result);
}
