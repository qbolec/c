#include<cstdio>
using namespace std;
char p[100][100];//[row][col]#.@ 
int main(){
  int w,h;
  scanf("%d %d",&w,&h);
  for(int i=0;i<h;i++)
    scanf(" %s",p[i]);
  int r=0,c=0;
  for(int i=0;i<h;i++)
      for(int j=0;j<w;j++)
        if(p[i][j]=='@'){
          r=i;
          c=j;
        }    
  const int dr[4]={-1,0,1, 0};
  const int dc[4]={ 0,1,0,-1};
  
  int d=0;//stan
  while(r!=0 && r!=(h-1) && c!=0 && c!=(w-1)){
    printf("Row %d column %d STATE %d\n",r,c,d);
    if(d && p[ r+dr[(d-1)&3] ] [ c+dc[(d-1)&3] ]!='#' ){
        d--;
        r+=dr[d&3];
        c+=dc[d&3];
    }else{    
      if( p[ r+dr[d&3] ] [ c+dc[d&3] ]!='#' ){
        r+=dr[d&3];
        c+=dc[d&3];
      }else{
        d++;
      }      
    }    
  }
  return 0;
}
