#include <cstdio>

#define MAX_K 100
#define MAX 1000000
int p[MAX_K];
bool v[MAX];

int main() {
  int c,k,q,i,j;
  
  scanf("%d",&c);
  while (c--) {
    scanf("%d %d",&k,&q);
    for (i=0; i<k; i++) scanf("%d",&p[i]);
    v[0]=true;
    for (i=1; i<MAX; i++) v[i]=false;
    for (i=0; i<k; i++) for (j=p[i]; j<MAX; j++) v[j]|=v[j-p[i]];
    while (q--) {
      scanf("%d",&j);
      while (!v[j]) j++;
      printf("%d\n",j);
    }
  }
  
  return 0;
}
