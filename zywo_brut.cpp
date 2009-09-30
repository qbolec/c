#include<cstdio>
#include<algorithm>
using namespace std;
int n;
int h[1000000];
int odpowiedz[1000000];
int sumakar=0;
int kara(int ile,int gdzie){
    return (gdzie>0?abs(h[gdzie-1]-ile):0)+(gdzie+1<n?abs(h[gdzie+1]-ile):0);
}
void zamien(int a,int b){
  if(a<0 || a>=n || b<0 || b>=n)return;
  if(a==b)return;
  int w=(a+1==b)?
    (sumakar-kara(h[a],a)-kara(h[b],b)+kara(h[b],a)+kara(h[a],b)+2*abs(h[a]-h[b])):
    (sumakar-kara(h[a],a)-kara(h[b],b)+kara(h[b],a)+kara(h[a],b));
  odpowiedz[a]<?=w;
  odpowiedz[b]<?=w;
}
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++)
    scanf("%d",h+i);
  for(int i=1;i<n;i++)
    sumakar+=abs(h[i]-h[i-1]);
  for(int i=0;i<n;i++)
    odpowiedz[i]=sumakar;
  for(int i=0;i<n;i++)
    for(int j=i;j--;)
      zamien(j,i);

  for(int i=0;i<n;i++)
    printf("%d\n",odpowiedz[i]);

  return 0;
}
