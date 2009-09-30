#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int random(int f,int t){
  return f+ (((rand()<<16) ^ rand())%t);
}
int main(){
  int g,t,k,q;
  scanf("%d %d %d %d",&g,&t,&k,&q);
  printf("%d\n",t);
  while(t--){
    printf("%d %d\n",k,q);
    int p[100000];
    for(int i=0;i<k;i++)
      p[i]=random(1,64000/g)*g;
    sort(p,p+k);
    for(int i=0;i<k;i++)
      printf("%d\n", p[i]);
  
    for(int i=0;i<q/2;i++)
      printf("%d\n", random(0,1000000000));
    for(int i=q/2;i<q;i++)
      printf("%d\n", random(0,p[k-1]*7));
  }
  
}
