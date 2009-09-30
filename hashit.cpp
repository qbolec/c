#include<cstring>
#include<cstdio>
char tab[110][20];
int cnt=0;
int hash(const char * s){

  const unsigned char * t=(const unsigned char *)s;
  int h=0;
  for(int i=0;t[i];i++){
    h+= t[i]*(i+1);
    h%=101;
  }
  h=(h*19)%101;
  return h;
}
void add(const char * t){
  int j,h=hash(t);
  for(j=0;j<20;j++)
    if(!strcmp(tab[(h+j*j+j*23)%101],t))
      return; 
  
  for(j=0;j<20 && tab[(h+j*j+j*23)%101][0];j++){}
    
  if(j==20)return;
  strcpy(tab[(h+j*j+j*23)%101],t);
  cnt++;
}
void del(const char * t){
  int j,h=hash(t);  
  for(j=0;j<20 && strcmp(t, tab[(h+j*j+j*23)%101]);j++){}
  if(j==20)return;
  cnt--;
  tab[(h+j*j+j*23)%101][0]=0;
}
void solve(){
  int n;
  scanf("%d",&n);
  for(int i=101;i--;)tab[i][0]=0;

  cnt=0;
  for(int i=0;i<n;i++){
    char t[1024];
    scanf("%s",t);
    if(t[0]=='A')
      add(t+4);
    else
      del(t+4);
  }
  printf("%d\n",cnt);
  for(int i=0;i<101;i++)
    if(tab[i][0])
      printf("%d:%s\n",i,tab[i]);
    
  
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
}
