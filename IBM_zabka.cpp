#include<cstdio>
#include<cstdlib>
#include<cmath>
//0.146897
//0.146896
const double t=0.146896;
const int N=100000000;
unsigned char plansza[N];
int ones[256];
int main(){
  double fi=(sqrt(5.0)-1.0)*0.5;
  double fith=1.0/fi;
  double noreturn=1.0-fi;
//  jumpedover*noreturn==t
  double jumpedover=t/noreturn;
  printf("jumped expectation=%lf\n",jumpedover);
  double expectation=(3.0-sqrt(5))*0.25;
  int pos=128;
  srand(3435);
  int jpd=0;
  while(pos<N*8){
    if(rand()&1){
      pos+=2;
      if(0==(plansza[(pos-1)/8]&(1<<(pos-1)%8)))
        jpd++;
    }else{
      pos--;
    }
    plansza[pos/8]|=1<<pos%8;
  }
  for(int i=1;i<256;i++)
    ones[i]=ones[i&(i-1)]+1;
  int visited=0;
  for(int i=0;i<N;i++){
    visited+=ones[plansza[i]];
  }
  double jpdp=(double)jpd/(N*8);
  printf("jmpd=%d czyli %lf\n",jpd,jpdp);
  double nvp=1.0-(double)visited/(N*8);
  printf("odwiedzono %d z %d pol\nczyli nieodwiedzono %lf, a oczekiwano %lf\n",visited,N*8,nvp,expectation);
  printf("czyli noreturn powinno byc %lf a nie %lf\n",nvp/jpdp,noreturn);
  system("PAUSE");
}
