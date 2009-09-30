/*piekna ilustracja ze to nie dziala
128 vs. 128
127 vs. 123
128 vs. 121
129 vs. 120
129 vs. 118
130 vs. 117
131 vs. 117
130 vs. 116
129 vs. 116
130 vs. 119
129 vs. 121
130 vs. 126
129 vs. 129
*/
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
const int N=13;
unsigned char tab[N];
int rep[N];
int pre[N];
unsigned char rem[N];
double entropy(const unsigned char * data,int n){
  int s[256];
  for(int i=0;i<256;i++)s[i]=0;
  for(int i=n;i--;)
    s[data[i]]++;
  //for(int i=0;i<10;i++)
    //printf("stat of %d is %d\n",i,s[i]);
//  printf("total length %d\n",n);
  double P=0.0;
  for(int i=0;i<256;i++){
    if(s[i])
      P-=log2(s[i])*s[i];
  }
  P/=n;
  P+=log2(n);
  return P;
}
int main(){
  srand(15);
  tab[0]=128;
  for(int i=1;i<N;i++)
    tab[i]=tab[i-1]+rand()%3-1;
//  for(int i=0;i<N;i++)
//    printf("%d ",(int)tab[i]);
  
  printf("entropy: %.3lf\n",entropy(tab,N));
    
  pre[0]=tab[0];
  pre[1]=tab[1];
  for(int i=2;i<N;i++)
    pre[i]=  (int)tab[i]-((int)tab[i-2]*2-tab[i-1]);
//  for(int i=0;i<N;i++)
//    printf("%d ",(int)pre[i]);
    
  printf("entropy: %.3lf\n",entropy((unsigned char*)pre,N));
    
  
    
  rep[0]=tab[0];
  rep[(N-1)]=tab[(N-1)];
  for(int i=1;i+1<N;i++)
    rep[i]=  (int)tab[i]-((int)tab[i-1]+tab[i+1])/2;
//  for(int i=0;i<N;i++)
//    printf("%d ",(int)rep[i]);
  
  printf("entropy: %.3lf\n",entropy((unsigned char*)rep,N));

  bool need=true;
  rem[0]=rep[0];
  rem[N-1]=rep[N-1];
  int loops=0;
  while(need){
    loops++;
    need=false;
    for(int i=1;i+1<N;i++){
      char p= (int)rem[i]-((int)rem[i-1]+rem[i+1])/2;
      if(p!=rep[i]){
        need=true;
        rem[i]+=rep[i]-p;
      }
    }
  }
  if(memcmp(rem,tab,N)){
    for(int i=0;i<N;i++)
      printf("%d vs. %d\n",(int)tab[i],(int)rem[i]);    
  }
  printf("loops=%d re=%d\n",loops,memcmp(rem,tab,N));
  
        
  scanf("%d",&tab[0]);
}
