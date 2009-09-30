#include<cstdio>
const int p=3;
double m[p*p][p*p];
bool u[p*p+1];
int main(){
  for(int i=p*p;i--;)
  for(int j=p*p;j--;)
  m[i][j]=0;  
  for(int a=0;a<p;a++)
    for(int b=0;b<p;b++)
      for(int x=0;x<p;x++)
        m[a*p+b][ x*p + (a*x+b)%p ] =1;


  
      
  for(int c=0;c<p*p;c++){
      
    
    int br=666;
    for(br=0;br<p*p;br++)
      if(!u[br] && m[br][c])
        break;
    printf("redu: %d\n",br);
    u[br]=true;
    for(int r=0;r<p*p;r++)
      if(r!=br){
        double f=m[r][c]/m[br][c];
        for(int i=0;i<p*p;i++)
          m[r][i]-=f*m[br][i];
      }
      
    for(int i=p*p;i--;){
      for(int j=p*p;j--;)
        printf("%.2lf ",m[i][j]);
      puts("");
    }          
  }
  for(int r=0;r<p*p;r++){
    printf("%.3lf ",m[r][r]);
    puts("");
  }
  scanf("%d",&p);
  return 0;
}
