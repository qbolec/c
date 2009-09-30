#include<cstdio>
#include<cstdlib>
char t[80][80];
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};
void draw(int x,int y,int d,int k){
  if(!k)return;
  for(int i=0;i<k;i++){
    t[x+dx[d]*i][y+dy[d]*i]=1;
  }
  draw(x+dx[d]*k,y+dy[d]*k,d,k/2);
  draw(x+dx[d]*k,y+dy[d]*k,d-1&3,k/2);
  draw(x+dx[d]*k,y+dy[d]*k,d+1&3,k/2);
}
int main(){
  draw(0,32,2,32);
  for(int r=0;r<70;r++){
    for(int c=0;c<70;c++){
      putchar(t[r][c]?'*':' ');
    }
    puts("");
  }
  system("PAUSE");
}
