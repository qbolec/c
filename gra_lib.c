#include<stdio.h>
#include<stdlib.h>

static int questions,bound,n,x,lied;

#define MAX 201

int getN(int _bound) {
  bound=_bound;
  if (bound<0 || bound>5) exit(1);
  if (scanf("%d",&n)!=1 || n<1 || n>MAX) exit(1);
  srand(42+n);
  x=rand()%n+1;
  lied=questions=0;
  return n;
}

int isLess(int a) {
  questions++;
  if (lied)
    return x<a;
  if (rand()%5==0) {
    lied=1;
    return x>=a;
  }
  return x<a;
}

void answer(int _x) {
  if (x!=_x)
    puts("Niepoprawna odpowiedz.");
  else
    printf("OK, uzyto %d pytan.",questions);
}

