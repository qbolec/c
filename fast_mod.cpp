#include<cstdio>
#include<cstdlib>
int main(){
  int x,n,a;
  const int t=1000000000;
/*/normalny program
  scanf("%d %d",&x,&n);
  a=1;
  for(int i=0;i<t;i++)
    a=(a*x)%n;
  printf("%d\n",a);
//nienormalny program*/
  scanf("%d %d",&x,&n);
  int r=(1LL<<32)/n;
  a=1;
  for(int i=0;i<t;i++){
    a*=x;
    a-=(((long long)r*a)>>32)*n;
    if(a>=n)a-=n;
  }
  printf("%d\n",a);
system("PAUSE");
  return 0;
  
}
