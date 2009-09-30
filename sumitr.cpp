#include<cstdio>
int n,t,b[2000],i,j,x,o,z;
int main(){scanf("%d",&t);while(t--){scanf("%d",&n);for(i=0;i++<n;o=0)for(int j=0;j<i;j++){scanf("%d",&x);z=o>?b[j];o=b[j];b[j]=x+z;}z=0;for(j=n;j--;b[j]=0)z>?=b[j];printf("%d\n",z);}return 0;}
