#include<cstdio>
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

void solve(){
  scanf("%d %d %s %s",&k,&l,keys,letters);
  for(int i=0;i<l;i++)
    scanf("%d",&ppb[i]);  
  for(int literki=1;literki<=l;literki++){
    for(int klawisze=1;klawisze<=literki && klawisze<=k;klawisze++){    
      best[klawisze][literki]=INF;    
      int sum=0;  
      int cst=0;
      for(int naostatnim=1;naostatnim<=literki-klawisze+1;naostatnim++){
        sum+=ppb[literki-naostatnim];
        cst+=sum;
        
        int op=best[klawisze-1][literki-naostatnim]+ cst; 
        if(op<=best[klawisze][literki]){
          best[klawisze][literki]=op;
          choose[klawisze][literki]=naostatnim;
        }
      }     
    }
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
