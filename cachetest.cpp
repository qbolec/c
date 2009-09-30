#include<cstdio>
#include<ctime>
//cache line 64 bajty [6 ostatnich bitów]
//cache size 64kb= 2^16 bajtow 
//ilosc linii 2^10 

char t1[100][(1<<16)+64];
char t2[100][1<<16];
int main(){
  int s1=time(0);
  for(int z=1000000;z--;)
    for(int r=0;r<99;r++)
      for(int c=0;c<64;c++)
        t1[r][c]=t1[r+1][c];//adres ma inna reszte modulo 1<<16
  printf("duza tablica : %d sekund\n",time(0)-s1);
  
  int s2=time(0);
  for(int z=1000000;z--;)
    for(int r=0;r<99;r++)
      for(int c=0;c<64;c++)
        t2[r][c]=t2[r+1][c];//adres ma te sama reszte modulo 1<<16
  printf("mala tablica: %d sekund\n",time(0)-s2);
  
}
