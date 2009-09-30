#include<cstdio>
const int N=20;
const int L=1<<N;
int ones[L];
int n;
int u[N];
long long w;
void solve(){
  scanf("%d",&n);
  
  for(int r=0;r<n;r++){
    u[r]=0;
    for(int c=0;c<n;c++){
      int x;
      scanf("%d",&x);
      u[r]=(u[r]<<1)|x;
    }
  }
  w=0;
  for(int i=0;i< (1<<n) ; i++){
    long long x=1;
    for(int j=0;j<n;j++)
      x*= ones[ u[j]&i  ];
    if( (n-ones[i])&1 )
      w-=x;
    else
      w+=x;
  }
  printf("%lld\n",w);
}
int main(){
  for(int i=0;i<L;i++){
    int j=i;
    int x=0;
    while(j){
      j&=j-1;x++;
    }
    ones[i]=x;
  }
  int c;
  scanf("%d",&c);
  while(c--)
    solve();
}
