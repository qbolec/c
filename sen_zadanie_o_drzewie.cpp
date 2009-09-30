#include<cstdio>
int n;
int deg[1000000];
int firstchild[1000000];
int main(){
  int x=1;  
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    scanf("%d",deg+i);
    firstchild[i]=x;
    x+=deg[i];
  }
}
