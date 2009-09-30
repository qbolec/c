#include<cstdio>
using namespace std;
const int S=50;
int tab[S][S];
int gcd(int a,int b){
  if(!b)
    return a;
  return gcd(b,a%b);
}
int main(){
  printf("<html><body><table>\n");
  tab[1][0]=1;
  for(int x=1;x<S;x++){
    printf("<tr>\n");
    for(int y=1;y<S;y++){      
      if(x==1){
        int i=x;
        int j=y-1;
        int d=gcd(i,j);
        i/=d;
        j/=d;
        tab[x][y]= !tab[i][j];  
      }else if(y==1){
        int i=x-1;
        int j=y;
        int d=gcd(i,j);
        i/=d;
        j/=d;
        tab[x][y]= !tab[i][j];  
      }else{
        int i=x;
        int j=y-1;
        int d=gcd(i,j);
        i/=d;
        j/=d;
        tab[x][y]= !tab[i][j];  
        
        i=x-1;
        j=y;
        d=gcd(i,j);
        i/=d;
        j/=d;
        tab[x][y]|= !tab[i][j];  
      }
      
      if(tab[x][y]){
        printf("<td><font color=green>1</font></td>");      
      }else{
        printf("<td><font color=red>0</font></td>");      
      }
    }
    printf("</tr>\n");
  }
  return 0;
}
