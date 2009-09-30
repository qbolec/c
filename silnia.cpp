#include<cstdio>
int main(){
  int r=1;
  for(int i=1;i<=12;i++){
    r*=i;
    printf("%d,",r);
  }
  scanf("%d",&r);
}
