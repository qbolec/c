#include<cstdio>
double m[22][22];
bool u[22];
int main(){
  for(int r=0;r<21;r++)
    for(int c=0;c<21;c++)
      scanf("%lf",&m[r][c]);
      
  for(int c=0;c<21;c++){
    int br;
    for(br=0;br<21;br++)
      if(!u[br] && m[br][c])
        break;
    printf("redu: %d\n",br);
    u[br]=true;
    for(int r=0;r<21;r++)
      if(r!=br){
        double f=m[r][c]/m[br][c];
        for(int i=0;i<21;i++)
          m[r][i]-=f*m[br][i];
      }
  }
  for(int r=0;r<21;r++){
    printf("%.3lf ",m[r][r]);
    puts("");
  }
  
  return 0;
}
