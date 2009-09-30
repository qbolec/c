#include<cstdio>
#include<cstdlib>
unsigned long int wsp(int n,int k)
{
  unsigned long int tab[n-k+1];
  int i,j;
  for(i=0;i<n-k+1;++i)
    tab[i]=1;
  for(i=1;i<=k;++i)
    for(j=n-k-1;j>=0;--j)
      tab[j]+=tab[j+1];
  return tab[0];
}
int main(){
  for(int n=0;n<10;++n){
    for(int k=0;k<=n;++k){
      printf("%3d ",wsp(n,k));
    }
    puts("");
  }
  system("PAUSE");
}
