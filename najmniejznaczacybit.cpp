#include<cstdio>
unsigned int x[9];
void solve(){
  unsigned int k=0;
  for(int i=0;i<9;i++){
    scanf("%x",x+i);
  }
  unsigned int w=0;
  for(int z=0;z<32;z++){
    unsigned int s=0;
    for(int i=0;i<8;i++){
      s^=x[i];
    }
    unsigned int b=(x[8]^s^w)&(1<<z);
    k^=b;
    for(int i=0;i<8;i++){
      x[i]^=b;
      w+=x[i]&(1<<z);
    }    
  }
  printf("%x\n",k);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
  return 0;
}
