#include<cstdio>
#include<cstdlib>
#include<cassert>
int main(){
  int n,m;
  scanf("%d %d",&n,&m);
  printf("%d %d\n",n,m);
  assert(n-1<=m);
  for(int i=1;i<n;i++)
    printf("%d %d\n",rand()%i,i);
  for(int i=n-1;i<m;i++){
    int a=1+rand()%(n-1);
    int b=rand()%a;
    printf("%d %d\n",b,a);
  }
}
