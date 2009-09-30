#include<cstdio>
#include<cmath>
#include<cstdlib>
int main(){
  
  int M=100000;
  for(int Y=200;Y<M-200;Y++){
    printf("y=%d\r",Y);
    for(int X=1;X<100;X++){
      int t=Y+X;
      double w=0.0;
      while(t<M){
        int p=(rand()%100+1);
        p<?=M-t;
        w+= (double)(p * X) / t;
        t+=p;
      }
      double expected=X*(log(M)-log(X+Y));
      if(expected>w || expected*1.1<w)
        printf("%lf expected %lf\n",w,expected);
    }
  }
  system("pause");
}
