#include<cstdio>
int r[2000000];
int p[2000000];
int main(){
  while(1){
    int n;
    scanf("%d",&n);
    if(!n)
      return 0;
    for(int i=0;i<n;i++)
      scanf("%d",r+i+1);
    bool dupa=false;
    for(int i=1;i<=n;i++)
      if(i!= r[r[i]] ){
        dupa=true;
        break;
      }
    puts(dupa?"not ambiguous":"ambiguous");
  }
  return 0;
}
