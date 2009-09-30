#include<cstdio>
int main(){
  int p;
  while(scanf("%d",&p)==1){
    int n=p*p;
    for(int i=1;i<n;i++){
      bool b[2000]={};
      int g=i;
      int j;
      for(j=1;j<=(p-1)*p;j++){
        b[g]=true;
        g=(g*i)%n;
        if(b[g])break;
      }
      if(j==(p-1)*p){
        printf("%d\n",i);
      }
    }
  }
}
