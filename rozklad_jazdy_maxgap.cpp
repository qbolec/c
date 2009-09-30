#include<cstdio>
#include<cmath>
int n,modulo;
int plan[1000000];
int minimumkubelka[1000010];
int maximumkubelka[1000010];
int main(){
  scanf("%d %d",&n,&modulo);
  int maximum=0;
  plan[0]=0;  
  for(int i=1;i<n;i++){
    int ignored,s;
    scanf("%d %d",&ignored,&s);
    maximum>?=plan[i]=(plan[i-1]+s)%modulo;
  }
  int gap=(maximum+n-2)/(n-1);// mozna by zaokraglic w dol to potegi dwojki zeby shiftowac...
  if(gap){
    for(int i=0;i<n;i++){
      maximumkubelka[i]=-1;
      minimumkubelka[i]=modulo;
    }
    for(int i=0;i<n;i++){
      int kubelek=plan[i]/gap;
      minimumkubelka[kubelek]<?=plan[i];
      maximumkubelka[kubelek]>?=plan[i];
    }
    int last=0;
    int best=maximum;
    for(int k=0;k<n;k++){
      if(minimumkubelka[k]>=0){
        best<?= modulo-minimumkubelka[k]+last;
        last=maximumkubelka[k];
      }
    }
    printf("%d\n",best);
  }else{
    puts("0");
  }
}


