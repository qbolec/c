#include<cstdio>
int main(){
  int n=10;
  scanf("%d",&n);
  int x=17;
  for(int t=10;t--;)
    for(int i=0;i<n;i++)
      x*=x;

  printf("%d",x);
  return 0;
}
