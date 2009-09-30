#include<cstdio>
const int t[37]={0,0,1,26,2,23,27,0,3,16,24,30,28,11,0,13,4,7,17,2,25,22,31,15,
29,10,12,6,0,21,14,9,5,20,8,19,18};
const unsigned int r=(1LL<<32)/37;

int main(){
  for(int i=0;i<32;i++){
    unsigned int x = 1U<<i;
    printf("%u\n",t[x-37*(((unsigned long long)r*x)>>32)]);
  }
  scanf("%d");
}
