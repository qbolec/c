#include<cstdio>
#include<cmath>
int main(){
  while(1){
    char m[100];
    char t[100];
    puts("total:");
    gets(t);
    puts("megatotal:");
    gets(m);
    int j=0;
    for(int i=0;m[i];i++)
      if(m[i]>='0' && m[i]<='9')
        m[j++]=m[i];
    m[j]=0;
    j=0;
    for(int i=0;t[i];i++)
      if(t[i]>='0' && t[i]<='9')
        t[j++]=t[i];
    t[j]=0;
    int M,T;
    sscanf(m,"%d",&M);
    sscanf(t,"%d",&T);
    printf("M: %d T: %d \n1gr daje %.2lf groszy\n",M,T,0.5*(log(M)-log(T)));
  }
}
