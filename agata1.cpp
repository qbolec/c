#include <stdio.h>
#include <stdlib.h>
#include<math.h>
float get_minimum(float x[],int len){
  return x[0];
}
int suma_dzielnikow (int n)
{
    int i,suma_dzielnikow=0;
    for(i=1;i*i<=n;i++)
      if(n%i==0){
        suma_dzielnikow+=i;
        if(i*i!=n)suma_dzielnikow+=n/i;    
      }
   return suma_dzielnikow-n;     
}

int main(int argc, char *argv[])
{
    int n,m;
    for(n=2; n<1000; n++)
    {
             if (n==suma_dzielnikow(n))
                printf("liczba %d jest liczba doskonala\n",n);
             else;
    }
    
    for(n=2; n<1000; n++)
    {
             m=2;
         while (m<1000)
         { 
             if ((n==suma_dzielnikow(m))&&(m==suma_dzielnikow(n)))
                printf("liczby %d i %d sa zaprzyjaznione\n",n, m);
                m++;
         }
    }
    
  system("PAUSE"); 
  return 0;
}
