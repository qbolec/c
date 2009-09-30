#include<cstdio>
int main(){
  printf("Y%sX\n","dupa");
  printf("Y%.3sX\n","dupa");
  printf("Y%.13sX\n","dupa");
  printf("Y%-3sX\n","dupa");
  printf("Y%-13sX\n","dupa");
  printf("Y%3sX\n","dupa");
  printf("Y%13sX\n","dupa");
  printf("Y%*sX\n",20,"dupa");
  printf("X%*s%sX", (9-4) * 2,"", "dupa");
  scanf("%d");
}
