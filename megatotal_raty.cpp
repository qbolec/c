#include<cstdio>
#include<cmath>

void ratuj(int T,int kwota,int raty){
  double total=T;
  double part=0.0;
  double ret=0.0;
  for(int i=1;i<=raty;i++){
    int si=2.0*total*(pow(0.5*kwota/total+1.0, 1.0/(raty+1-i))-1.0);
    printf("rata %d:  %d gr\n",i,si);
    ret+= si*.5*part/total;
    total+=si*.5;
    part+=si*.5;
    kwota-=si;
    printf("  new total %.2lf  return %.2lf  perc %.2lf (%.2lf)\n",total,ret,100*part/total,50*part/total);
  }
}
int main(){
  while(1){
    char t[100];
    puts("total:");
    int T;
    do{
      gets(t);

      int j=0;
      for(int i=0;t[i];i++)
        if(t[i]>='0' && t[i]<='9')
          t[j++]=t[i];
      t[j]=0;
    }while(1!=sscanf(t,"%d",&T));
    int kwota;
    int raty;
    puts("kwota:");
    scanf("%d",&kwota);
    puts("liczba rat:");
    scanf("%d",&raty);
    ratuj(T,kwota,raty);
  }
}
