#include<cstdio>
long long sum[100001],top,res;
int desc_c,x,n,i,desc[100001];
int main(){
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&x);
    sum[i+1]=sum[i]+x;
  }
  desc[0]=0;
  top=sum[n]-1;
  for(i=1;i<=n;i++)
    if(sum[i]<sum[desc[desc_c]])
      desc[++desc_c]=i;
  for(i=n+1;i--;)
    if(sum[i]>top){
      top=sum[i];
      while(desc[desc_c]>i)
        desc_c--;
      res>?=top-sum[desc[desc_c]];
    }
  printf("%lld\n",res);
}
