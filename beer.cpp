#include<cstdio>
#include<cstring>
int t[1024];
int next[1024];
int prev[1024];
int ans[1024][1024];
void solve(){
  int n;
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    scanf("%d",t+i);
  }
  if(n%2){
    puts("0");
    return ;
  }
  for(int i=0;i<n;i++){
    for(next[i]=(i+1)%n;t[next[i]]!=t[i];next[i]=(next[i]+1)%n)
    {
    }
    prev[next[i]]=i;
  }
  memset(ans,0,sizeof(ans));
  for(int len=2;len<n;len+=2)
    for(int i=0;i<n;i++){
      int j=(i+len+n-1)%n;
      ans[i][j]>?=(t[i]==t[j])+ ((i+1)%n!=j ? ans[(i+1)%n][(j+n-1)%n]:0);
      if((i+1)%n!=j)
        ans[i][j]>?=ans[(i+1)%n][(j+n-1)%n];
      for(int k=next[i];k!=i && k!=j && (i<j ? (i<k && k<j ): (i<k || k<j) ); k=next[k])
        if((k-i+n)%2)
          ans[i][j]>?=1+( (i+1)%n!=k  ? ans[(i+1)%n][(k+n-1)%n]:0  )+( ans[(k+1)%n][j]);
      for(int k=prev[j];k!=i && k!=j && (i<j ? (i<k && k<j ): (i<k || k<j) ); k=prev[k])
        if((k-j+n)%2)
          ans[i][j]>?=1+(ans[i][(k+n-1)%n]  )+( (k+1)%n!=j ? ans[(k+1)%n][(j+n-1)%n] : 0);

    }
  int m=0;
  for(int i=0;i<n;i++)
    for(int k=next[i];k!=i; k=next[k])
      if((k-i+n)%2)
        m>?=1+( (i+1)%n!=k  ? ans[(i+1)%n][(k+n-1)%n]:0  )+( (k+1)%n!=i ? ans[(k+1)%n][(i+n-1)%n]:0);

  printf("%d\n",m);

}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
}
