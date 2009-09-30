#include<cstdio>
#include<cstring>
char text[256];
/*
Set          ::= "{" Elementlist "}"
Elementlist  ::= <empty> | List
List         ::= Element | Element "," List
Element      ::= Atom | Set
Atom         ::= "{" | "}" | ","

*/
bool isset[256][256];
bool islist[256][256];
void solve(){  
  scanf(" %s",text);
  int n=strlen(text);
  for(int i=0;i<=n;i++)
  for(int j=0;j<=n;j++)
    islist[i][j]=isset[i][j]=false;
  for(int i=0;i<=n;i++)
    islist[i][i]=islist[i][i+1]=true;
  for(int k=1;k<=n;k++){
    for(int i=0;i+k<=n;i++){
      isset[i][i+k]|= text[i]=='{' && text[i+k-1]=='}' && islist[i+1][i+k-1];
      for(int j=1;j+1<k;j++)
        islist[i][i+k]|= islist[i][i+j] && text[i+j]==',' && islist[i+j+1][i+k];
      islist[i][i+k]|=isset[i][i+k];
    }
  } 

  if(isset[0][n])
    puts("Set");
  else
    puts("No Set");
}
int main(){
  int d;
  scanf("%d",&d);
  for(int i=1;i<=d;i++){
    printf("Word #%d: ",i);
    solve();
  }
  return 0;
}
