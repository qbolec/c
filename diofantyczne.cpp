#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cstring>
using namespace std;
int a[200][100];
int b[100];
int x[100];
int f[100];
int h,w;
void solve(){
  scanf("%d %d",&h,&w);
  if(h>w)
    throw "rownania na pewna sa zalezne bo jest ich za malo";
  memset(a,0,sizeof(a));
  memset(b,0,sizeof(b));
  for(int r=0;r<h;r++){
    for(int c=0;c<w;c++)
      scanf("%d",&a[r][c]);
    scanf("%d",&b[r]);
  }
  for(int r=h;r<h+w;r++)
    a[r][r-h]=1;
  for(int r=0;r<h;r++){
    int cnt,best;
    while(1){//ta petla, to w zasadzie GCD r-tych elementow dla kolumn od r-tej do w-tej
      cnt=0;
      best=-1;
      for(int c=r;c<w;c++)
        if(a[r][c]){
          if(!cnt || abs(a[r][best])>abs(a[r][c]))
            best=c;
          cnt++;
        }
      if(!cnt)
        throw "rownania sa zalezne liniowo";
      for(int i=0;i<h+w;i++)
        swap(a[i][r],a[i][best]);
      if(cnt==1)
        break;
      for(int c=r+1;c<w;c++){
        int g=a[r][c]/a[r][r];
        for(int i=0;i<h+w;i++)
          a[i][c]-=g*a[i][r];//tutaj mieszkaja owerflowy, ktorych ponoc da sie uniknac
      }
    }
  }
  memset(x,0,sizeof(x));
  for(int r=0;r<h;r++){
    int s=b[r];
    for(int c=0;c<r;c++)
      s-=a[r][c]*f[c];
    if(s%a[r][r])
      throw "nie ma rozwiazan calkowitych";
    f[r]=s/a[r][r];
    for(int i=0;i<w;i++)
      x[i]+=a[h+i][r]*f[r];
  }
  puts("rozwiazaniem jest wektor postaci:");
  for(int i=0;i<w;i++)
    printf("%c%d",i?',':'(',x[i]);
  puts(")");
  if(h<w){
    puts("plus dowolna kombinacja wektorow:");
    for(int c=h;c<w;c++){
      for(int r=0;r<w;r++)
        printf("%c%d",r?',':'(',a[h+r][c]);
      puts(")");
    }
  }
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    try{
      solve();
    }catch(const char * s){
      puts(s);
    }
  }
}
