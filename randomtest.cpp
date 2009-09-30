#include<cstdio>
#include<cstdlib>
#include<ctime>
int random(int from, int to){
  //from < to
  srand(time(0)+rand());
  unsigned int dist = to-from;
  unsigned int r;
  while(1){
    r=rand();
    unsigned int l=RAND_MAX;
    while(l< dist ){
      r = r*RAND_MAX + rand();
      l*=RAND_MAX;
    }
    l=l-l%dist;
    if(r >= l) continue;
    return from+r%dist;
  }  
}
int main(){
  srand(time(0));
  for(int i=0;i< 100;i++)
    printf("Losowa liczba z przedzialu [15,27) to %d\n",random(15,27));
  getchar();
  return 0;
}
