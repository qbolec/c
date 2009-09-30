#include<cstdio>
int n,i,r,s;
char t[200];
int main(){
  scanf("%d",&n);
  while(n--){
    scanf(" %s",t);
    for(s=i=0;t[i];i++)s+=!!(35684898&(1<<t[i]));                        
    if(s!=i&&2*s>i)r++;
  }
  printf("%d\n",r);
}
