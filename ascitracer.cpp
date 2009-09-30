#include<cstdio>
using namespace std;
int n,m;
char image[300][300];
int h[50][50];
char * block[6]={
"..+---+",
"./   /|",      
"+---+ |",      
"|   | +", 
"|   |/.",
"+---+.."
};
void draw_block(int c,int r){
  for(int i=0;i<6;i++)
    for(int j=0;j<7;j++)
      if(block[i][j]!='.')
        image[r-i][c+j]=block[i][j];
}
int main(){
  scanf("%d%d",&n,&m);
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      scanf("%d",&h[i][j]);
  int wi=4*m+2*n+1;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      for(int k=0;k<h[i][j];k++){
        draw_block((n-1-i)*2+j*4,5+2*(n-i-1)+3*k);
      }
    }
  }
  int hi=300;
  while(hi--){
    bool found=false;
    for(int i=0;i<wi;i++)
      if(image[hi][i]){
        found=true;
        break;            
      }    
    if(found)
      break;
  }
  for(int i=hi;i>=0;i--){
    for(int j=0;j<wi;j++)
      printf("%c", image[i][j]?image[i][j]:'.');
    printf("\n");
  }
}
