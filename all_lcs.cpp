#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
char a[100];
char b[100];
char na[100][32];
char nb[100][32];
int m[100][100];
int al,bl;
char t[100];
void go(int i,int j,int p){
  //if(i==al || j==bl)return;
  for(char x='a';x<='z';x++){
    int ii=na[i][x-'a'];
    int jj=nb[j][x-'a'];
    if(ii<al && jj< bl){
      t[p]=x;
      if(p+1+m[ii+1][jj+1]==m[0][0]){
        if(p+1==m[0][0]){
          t[p+1]=0;
          puts(t);
        }else
          go(ii+1,jj+1,p+1);
      }
    }
  }
}
void solve(){
  scanf("%s %s",a,b);
  al=strlen(a);
  bl=strlen(b);
  for(int i=0;i<32;i++){
    na[al][i]=al;
    nb[bl][i]=bl;
  }
  for(int i=al;i--;){
    for(int j=0;j<32;j++)
      na[i][j]=na[i+1][j];
    na[i][a[i]-'a']=i;
  }
  for(int i=bl;i--;){
    for(int j=0;j<32;j++)
      nb[i][j]=nb[i+1][j];
    nb[i][b[i]-'a']=i;
  }
  for(int i=0;i<=al;i++)
    m[i][bl]=0;
  for(int j=0;j<=bl;j++)
    m[al][j]=0;
  for(int i=al;i--;)
    for(int j=bl;j--;)
      m[i][j]= a[i]==b[j]? 1+ m[i+1][j+1] : (m[i+1][j]>?m[i][j+1] );
  go(0,0,0);
  puts("");
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
  return 0;
}
