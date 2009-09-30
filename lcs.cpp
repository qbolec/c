#include<cstdio>
#include<cstring>
const int ILOSC_SLOW=3;
const int MAX_ILOSC_ZNAKOW=50;
char * slownik[ILOSC_SLOW]={"ALA","DUPA","KRZESLO"/*....*/};
int LCS[MAX_ILOSC_ZNAKOW+1][MAX_ILOSC_ZNAKOW+1];
int lcs(char * a,char *b){
  int al=strlen(a);
  int bl=strlen(b);
  for(int i=al;i--;)
    LCS[i][bl]=0;
  for(int j=bl;j--;)
    LCS[al][j]=0;
  for(int i=al;i--;)
    for(int j=bl;j--;)
      LCS[i][j]=a[i]==b[j] ? 1+LCS[i+1][j+1] : LCS[i+1][j]>?LCS[i][j+1];
  return LCS[0][0];
}
char * bestmatch(char * text){
  int best_bledy=666;
  int best=-1;
  for(int i=0;i<ILOSC_SLOW;i++){
    int bledy= strlen(slownik[i]) + strlen(text) - lcs(text, slownik[i])*2;
    if(bledy< best_bledy){
      best_bledy=bledy;
      best=i;
    }
  }
  return slownik[best];
}
int main(){
  while(1){
    char text[MAX_ILOSC_ZNAKOW+1];
    scanf("%s",text);
    printf("%s\n",bestmatch(text));
  }
  return 0;
}
