#include<cstdio>
const int p=5;
int v[p*p*p];
int main(){
  for(int a=0;a<p;a++)
  for(int b=0;b<p;b++)
  for(int x=0;x<p;x++)
    v[a*p+b]|= 1<<(x*p + (a*x+b)%p );
  puts("GOALS:");
  for(int i=0;i<p*p;i++){
    printf("%2d.",i);
    for(int j=0;j<p*p;j++){
      if(j%p==0)printf(" ");
      printf("%d",!!(v[i]&(1<<j)));
    }
    printf("\n");
  }
  puts("NODES:");
  for(int i=0;i<p*p;i++){
    v[i]=1<<i;
    printf("%2d.",i);
    for(int j=0;j<p*p;j++){
      if(j%p==0)printf(" ");
      printf("%d",!!(v[i]&(1<<j)));
    }
    printf("\n");
  }

  for(int i=p*p;;i++){
    int l,r;
    scanf("%d %d",&l,&r);
    v[i]=v[l]^v[r];
    printf("%2d.",i);
    for(int j=0;j<p*p;j++){
      if(j%p==0)printf(" ");
      printf("%d",!!(v[i]&(1<<j)));
    }
    printf("\n");
  }
}
/*
0 5
11 25
11 15
0 17
5 22
26 27
26 28
26 29
*/
