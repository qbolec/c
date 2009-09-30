#include<cstdio>
//jako funkcje hashujaca wezmiemy sobie
int N,n;
const int MAX_N=128;
char T[MAX_N][MAX_N];
char t[MAX_N][MAX_N];
char tab[MAX_N][MAX_N];
int hor[MAX_N][MAX_N];
int hor2[MAX_N][MAX_N];

int main(){
  while(1){
    scanf(" %d %d ",&N,&n);
    if(!n && !N)
      return 0;
    for(int i=0;i<N;i++)
      gets(T[i]);
    for(int i=0;i<n;i++)
      gets(t[i]);
   int hash=0;
    for(int i=n;i--;)
      for(int j=n;j--;)
        hash+=t[i][j];
    for(int z=4;z--;){
      int ok=0;
      int hash2=0;
      int hash3=0;
      for(int i=n;i--;)
        for(int j=n;j--;){
          hash3+=t[i][j]*j;
          hash2+=t[i][j]*j*i;
        }
      if(z==3){
        for(int i=0;i<N;i++){
          hor[i][0]=0;
          hor2[i][0]=0;
          for(int j=n;j--;){
            hor[i][0]+=T[i][j];
            hor2[i][0]+=T[i][j]*j;
          }
          for(int j=n;j<N;j++){
            hor[i][j-n+1]=hor[i][j-n]-T[i][j-n]+T[i][j];
            hor2[i][j-n+1]=hor2[i][j-n]-hor[i][j-n+1]+T[i][j]*n;
          }
        }
      }
      for(int j=0;j+n<=N;j++){
        int h=0;
        int h2=0;
        int h3=0;
        for(int i=n;i--;){
          h+=hor[i][j];
          h3+=hor2[i][j];
          h2+=hor2[i][j]*i;
        }
        if(h==hash && h2==hash2 && h3==hash3)
          ok++;//test(0,j);
        for(int i=n;i<N;i++){
          h=h-hor[i-n][j]+hor[i][j];
          h3=h3-hor2[i-n][j]+hor2[i][j];
          h2=h2-h3+ hor2[i][j]*n;
          if(h==hash && h2==hash2 && h3==hash3)
            ok++;//test(i-n+1,j);
        }
      } 
      if(z){   
        for(int r=0;r<n;r++)
          for(int c=0;c<n;c++)
            tab[r][c]=t[n-c-1][r];
        for(int r=0;r<n;r++)
          for(int c=0;c<n;c++)
            t[r][c]=tab[r][c];
      }
      printf("%d ",ok);      
    }
    printf("\n");
  }
}
