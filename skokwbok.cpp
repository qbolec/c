#include<cstdio>
#include<cstdlib>
int t[100000];
int main(){
  int p=50000;
  t[p]=1;
  for(int i=1;i<20;i++)
    t[p]*=3;
  printf("start = %d\n",t[p]);
  int s=0;
  while(p<100000){
    if(t[p]>2){
      s++;
      int r=t[p]/3;
      t[p]-=r*3;
      t[p-2]+=r;
      t[p+2]+=r;
      if(t[p-2]>2)
        p-=2;
      else
        p++;
    }else
      p++;
  }
  printf("%d\n",s);
  system("pause");

}
