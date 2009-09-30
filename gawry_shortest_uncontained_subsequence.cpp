#include<cstdio>
#include<cstring>
#define MAX 20000
char A[MAX],B[MAX];
int current[MAX],previous[256][MAX];
int main() {
  int n,m,i,j,k;
  scanf("%s %s",A,B); 
  n=strlen(A); 
  m=strlen(B);
  current[0]=MAX; 
  for (i=1; i<=n; i++) 
    current[i]=1;
  for (j=0; j<m; j++) {
    for (i=0; i<=n; i++) 
      previous[B[j]][i]=current[i];
      k=MAX; 
      for (i=0; i<n; i++) 
        current[i+1]=1+(k<?=previous[A[i]][i]);
  }
  if (current[n]<MAX) printf("%d\n",current[n]); else printf("NIE\n");
  return 0;
}
