#include<cstdio>
#include<cstdlib>
int main(){
  
  const int tests=100000000;
  const int m=100;
  long long ys=0;
  long long yn=0;
  long long yc=0;
  for(int t=0;t<tests;t++){
    if((t&1023)==0)
      printf("\r%d  of %d done.",t,tests);
    int suma=0;
    while(1){
      int y=rand()%6+1;
      suma+=y;
      ys+=y;
      yc++;
      if(suma>=m){
        yn+=y;
        break;
      }        
    }
  }
  printf("\n\navg.y =%lf\navg.yn = %lf\n",(double)ys/(double)yc,(double)yn/(double)tests);
}
