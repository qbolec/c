#include<cstdio>
using namespace std;
int sc;
int n;
char t[300];
char c[256];
int z;
// X=Y     to   X^Y^1
// -X      to   X^1
void solve(){
  z=sc=0;
  scanf(" %s",t);
  for(int i='a';i<='z';i++)c[i]=0;
  for(int i='A';i<='Z';i++)c[i]=0;
  for(int i=0;t[i];i++){
    if(t[i]=='-'){
      if(sc<1){
        puts("incorrect");
        return;
      }
      z^=1;
    }else if(t[i]=='='){
      if(sc<2){
        puts("incorrect");
        return;
      }
      z^=1;
      sc--;
    }else{
      c[t[i]]^=1;
      sc++;
    }
  }
  if(sc!=1){
    puts("incorrect");
    return;
  }
  if(!z){
    puts("formula");
    return;
  }
  for(int i='a';i<='z';i++)
    if(c[i]){
      puts("formula");
      return;
    }
  for(int i='A';i<='Z';i++)
    if(c[i]){
      puts("formula");
      return;
    }
  puts("tautology");
}
int main(){
  scanf("%d",&n);
  while(n--)
    solve();
}
