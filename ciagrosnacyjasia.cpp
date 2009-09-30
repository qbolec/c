#include<cstdio>
int t[1000000]={1,2,4};
int main(){
  int a=1;
  for(int i=3;i<1000000;i++){
    if(i>=t[a])
      a++;
    t[i]=t[i-1]+a;
    printf("%d %d\n",i,t[i]);
    if(t[i]>2000000000)
      break;
  }
  scanf("%d");
}
