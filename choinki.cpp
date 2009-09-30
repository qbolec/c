#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main() {
  int n; //wysokosc choinki
  int i;   int j;
  printf("podaj wysokosc choinki\n");
  scanf("%d", &n);
  for(i=0; i<n; i++)   {
    for(j=0; j<i;j++)
      printf(" ");
    for(j=2*n-1-2*i; j>0; j--)
      printf("*");
    printf("\n");
  }
  system("PAUSE");
  return 0;
}
