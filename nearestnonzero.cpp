#include<cstdio>
using namespace std;
int n;
int tab[202][202];
int dist[202][202];
int orgr[202][202];
int orgc[202][202];
const int S=1<<16;
int quer[S];
int quec[S];
int wp=0;
int rp=0;
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int main(){
  scanf("%d",&n);
  for(int r=0;r<n;r++)
    for(int c=0;c<n;c++){
      scanf("%d",&tab[r][c]);
      dist[r][c]= tab[r][c]? 0 : 666;      
    }
  for(int r=0;r<n;r++)
    for(int c=0;c<n;c++)
      if(!dist[r][c]){
        quer[wp]=r;
        quec[wp]=c;
        orgr[r][c]=r;
        orgc[r][c]=c;
        wp++;
      }
  while(rp!=wp){
    int r=quer[rp];
    int c=quec[rp];
    rp++;
//    if(!tab[r][c])
//      continue;
    for(int i=0;i<4;i++){
      int rr= r+dx[i];
      int cc= c+dy[i];
      if(rr>=0 && cc>=0 && rr<n && cc<n && dist[rr][cc]>=dist[r][c]+1){
        if(dist[rr][cc]==dist[r][c]+1){
          if(orgc[rr][cc]!=orgc[r][c] || orgr[rr][cc]!=orgr[r][c]){
            tab[rr][cc]=0;
//            dist[rr][cc]=-666;
            orgc[rr][cc]=-1;
            orgr[rr][cc]=-1;
          }
        }else{
          dist[rr][cc]=dist[r][c]+1;
          tab[rr][cc]=tab[r][c];          
          orgc[rr][cc]=orgc[r][c];
          orgr[rr][cc]=orgr[r][c];
          quer[wp]=rr;
          quec[wp]=cc;
          wp++;
        }
      }
    }    
  }
  for(int r=0;r<n;r++){
    for(int c=0;c<n;c++)
      printf("%d ",tab[r][c]);
    printf("\n");
  }
  return 0;
}
