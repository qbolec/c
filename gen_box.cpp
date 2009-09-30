#include<cstdlib>
#include<cstdio>
#include<ctime>
int main(int argc,char * args[]){
  int seed;
  if(argc!=2){
    return -1;
  }
  sscanf(args[1],"%d",&seed);
  srand(seed);
  const int T=1000;
  const int N=100;
  printf("%d\n",T);
  for(int t=0;t<T;++t){
    printf("%d\n",N);
    int x[N];
    for(int i=0;i<N;++i){
      x[i]=0;
    }
    const int s=rand()%N+1;
    for(int i=0;i<s;++i){
      const int p=rand()%N;
      ++x[p];
    }
    for(int i=0;i<N;++i){
      printf("%d ",x[i]);
    }
    puts("");
  }
}
