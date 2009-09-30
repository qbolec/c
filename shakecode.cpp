#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char tab[200][200];
int n;
void cycle(vector<char *> & x){
  char l=*x.back();
  for(int i=x.size();--i;)
    *x[i]=*x[i-1];
  *x[0]=l;
}
void cycle2(vector<char *> & x){
  char l=*x.front();
  for(int i=0;i<x.size()-1;i++)
    *x[i]=*x[i+1];
  *x[x.size()-1]=l;
}
void R(){
  for(int r=0;r<n;r+=2){
    char l=tab[r][n-1];
    for(int i=n;--i;)
     tab[r][i]=tab[r][i-1];  
    tab[r][0]=l;
  }
  for(int r=1;r<n;r+=2){
    tab[r][n]=tab[r][0];
    for(int i=0;i<n;i++)
      tab[r][i]=tab[r][i+1];
  }
}
void S(){
  for(int c=1;c<n;c+=2){
    char l=tab[n-1][c];
    for(int i=n;--i;)
     tab[i][c]=tab[i-1][c];  
    tab[0][c]=l;
  }
  for(int c=0;c<n;c+=2){
    tab[n][c]=tab[0][c];
    for(int i=0;i<n;i++)
      tab[i][c]=tab[i+1][c];
  }
}
void L(){
  for(int i=0;(i+1)*2<=n;i++){
    vector<char *> z;
    int x=i;
    int y=i;
    do{
      x++;
      z.push_back(&tab[x][y]);
    }while(x+i<n-1);
    do{
      y++;
      z.push_back(&tab[x][y]);
    }while(y+i<n-1);
    do{
      x--;
      z.push_back(&tab[x][y]);
    }while(x>i);
    do{
      y--;
      z.push_back(&tab[x][y]);
    }while(y>i);
    if(i&1)
      cycle(z);
    else
      cycle2(z);
  }
}
int main(){
  char n1,n2;
  while(scanf(" %c%c",&n1,&n2)==2){
    n= (n1-'0')*10 + n2-'0';
    if(!n)n=100;
    char key[100];
    char text[20000];
    gets(key);
    gets(text);
    for(int i=strlen(text),j=0;i<n*n;i++,j++)
      text[i]='A' + j%('Z'-'A'+1);
    text[n*n]=0;
    for(int r=0;r<n;r++)
      for(int c=0;c<n;c++)
        tab[r][c]= ('a'<=text[r*n+c] && 'z'>=text[r*n+c])?text[r*n+c]+'A'-'a':text[r*n+c];
    for(int i=0;key[i];i++)
      switch(key[i]){
      case 'L':
        L();
        break;
      case 'R':
        R();
        break;
      case 'S':
        S();
        break;
      }
    for(int r=0;r<n;r++)
      for(int c=0;c<n;c++)
        printf("%c",tab[r][c]);
    printf("\n");
  }
}
