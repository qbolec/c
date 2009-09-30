#include<cstdio>
#include<cassert>
using namespace std;
int k,l;
char keys[100];
char letters[100];
int ppb[100];
int best[100][100];
int choose[100][100];
const int INF=1LL<<29;
int test;
int naklawiszu[100];
int S[128][128];
int C[128][128];
inline void find(const int klawisze,const int literki,const int lb,const int ub){
  best[klawisze][literki]=INF;
  for(int naostatnim=lb;naostatnim <= ub;naostatnim++){
    const int op=best[klawisze-1][literki-naostatnim]+C[literki][naostatnim]; //cst;
    if(op<=best[klawisze][literki]){
      best[klawisze][literki]=op;
      choose[klawisze][literki]=naostatnim;
    }
  }
//  printf("find(%d,%d,%d,%d)=%d,%d\n",klawisze,literki,lb,ub,choose[klawisze][literki],best[klawisze][literki]);
}
void run(const int klawisze,int literki_from,const int literki_to,int left,const int right){
  while(literki_from<=literki_to){
    const int literki=(literki_from+literki_to)>>1;
    const int ub= ((left+literki-literki_from) <? (literki-klawisze+1));
    const int lb= ((right-(literki_to-literki)) >? 1);
    find(klawisze,literki,lb,ub);
    run(klawisze,literki_from,literki-1,left,choose[klawisze][literki]-1);
//  run(klawisze,literki+1,literki_to,choose[klawisze][literki]+1,right);
//  tail recursion:
    left=choose[klawisze][literki]+1;
    literki_from=literki+1;
  }
}
void solve(){
  scanf("%d %d %s %s",&k,&l,keys,letters);
  for(int i=0;i<l;i++)
    scanf("%d",&ppb[i]);
  choose[1][0]=0;
  for(int literki=1;literki<=l;literki++){
    for(int naostatnim=1;naostatnim<=literki;naostatnim++){
      S[literki][naostatnim]=S[literki][naostatnim-1]+ppb[literki-naostatnim];
      C[literki][naostatnim]=C[literki][naostatnim-1]+S[literki][naostatnim];
    }
  }
  for(int klawisze=1;klawisze<=k;klawisze++){
    find(klawisze,l,1,l-klawisze+1);
    run(klawisze,klawisze,l-1,1,choose[klawisze][l]-1);
  }

  printf("Keypad #%d:\n",++test);
  int literki=l;
  for(int klawisz=k;klawisz>0;klawisz--){
    naklawiszu[klawisz]= choose[klawisz][literki];
    literki-=naklawiszu[klawisz];
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
    for(int j=0;j<i;j++)
      best[0][i]=best[i][j]=INF;
  best[0][0]=0;
  int n;
  scanf("%d",&n);
  while(n--)solve();
  return 0;
}
