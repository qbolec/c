#include<cstdio>
using namespace std;
int k,l;
char keys[100];
char letters[100];
int ppb[100];
long long best[100][100][100];
const long long INF=1LL<<30;
int test;
int naklawiszu[100];
void solve(){
  scanf("%d %d %s %s",&k,&l,keys,letters);
  for(int i=0;i<l;i++)
    scanf("%d",&ppb[i]);
  //A-1+B=<C
  //B>0
  //C>0
  for(int literki=1;literki<=l;literki++){
    for(int klawisze=1;klawisze<=literki;klawisze++){    
      best[klawisze][1][literki]=INF;
      for(int napoprzednim=0;napoprzednim<=literki-klawisze+1;napoprzednim++)
        best[klawisze][1][literki]<?= best[klawisze-1][napoprzednim][literki-1];      
      best[klawisze][1][literki]+=ppb[literki-1];
      //printf("B[%d][%d][%d]=%d\n",klawisze,1,literki,(int)best[klawisze][1][literki]);
      for(int naostatnim=2;naostatnim<=literki-klawisze+1;naostatnim++){
        best[klawisze][naostatnim][literki]=
          best[klawisze][naostatnim-1][literki-1]+ naostatnim*ppb[literki-1];        
      }
    }
  }
  
  printf("Keypad #%d:\n",++test);
  long long cost=INF;
  for(int naostatnim=1;naostatnim<=l-k+1;naostatnim++)
    cost <?= best[k][naostatnim][l];
//  printf("best %d  == %lld\n",(int)cost,cost);
  int literki=l;
  for(int klawisz=k;klawisz>0;klawisz--){
    for(naklawiszu[klawisz]=literki-klawisz+1;naklawiszu[klawisz]>0;naklawiszu[klawisz]--)
      if(best[klawisz][ naklawiszu[klawisz] ][literki]==cost){
        for(int i=naklawiszu[klawisz];i>0;i--){
          literki--;
          cost-= ppb[literki]*i;
        }
        //printf("na klawiszu %d powinno byc %d\n",klawisz,naklawiszu[klawisz]);
        break;
      }
  }
  int literka=0;
  for(int klawisz=1;klawisz<=k;klawisz++){
    printf("%c: ",keys[klawisz-1]);
    for(int i=0;i< naklawiszu[klawisz];i++)
      putchar(letters[literka++]);
    puts("");
  }
  puts("");
}
int main(){
  for(int i=0;i<100;i++)
    for(int j=0;j<100;j++)
      best[i][j][0]=best[i][0][j]=best[0][i][j]=INF;    
  best[0][0][0]=0;
  int n;
  scanf("%d",&n);
  while(n--)solve();
  return 0;
}
