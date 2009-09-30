#include<cstdio>
#define CLEAR(c) {long long * Z=(long long*) c; Z[0]=Z[1]=Z[2]=Z[3]=0; }
using namespace std;
char f[32][32];
char fc[32];
char d[32][32];
char * r;
int n,m,q;

char buff[1000000];
char *bp=buff;
char buff2[1000000];
char *bp2=buff2;
#define rid(x) {while(*bp<=32)bp++;x=*bp++-'0';while(*bp>32)x=x*10+*bp++-'0'; }
void wrajt(int x){
  if(x>9)
    wrajt(x/10);
  *bp2++= (x%10)+'0';
}
void solve(){
  rid(n);
  rid(m);
  CLEAR(fc);
  for(int i=32*4;i--;)
    ((long long*)d)[i]=-1;
  
  for(int i=m;i--;){    
    int x,y;
    rid(x);
    rid(y);
    f[x][fc[x]++]=y;
    f[y][fc[y]++]=x;
  }
  q=n;
  char s[32];
  for(int v=n;v--;){
    char * w=s, *r=s;
    *w++=v;
    d[v][v]=0;
    while(r<w){
      int i=*r++;
      for(int j=fc[i];j--;){
        int z=f[i][j];
        if(d[v][z]<0){
          d[v][z]=d[v][i]+1;
          *w++=z;
        }
      }
    }
  } 
  for(int a=n;a--;){
    int w=0;
    for(int b=n;b--;)
      w>?=d[a][b];
    q<?=2*w;
    for(int z=fc[a];z--;){
      int b=f[a][z];
      if(a<b){
        int w=0;
        for(int c=n;c--;)
          w>?= d[a][c] <? d[b][c];
        q<?=2*w+1;          
      }      
    }
  }
}
int main(){
  int d;
  fread(buff,1,999999,stdin);
  rid(d);
  for(int t=1;t<=d;t++){
    solve();
    bp2[0]='C';
    bp2[1]='a';
    bp2[2]='s';
    bp2[3]='e';
    bp2[4]=' ';
    bp2[5]='#';
    bp2+=6;
    wrajt(t);
    bp2[0]=':';
    bp2[1]='\n';
    bp2+=2;
    wrajt(q);
    bp2[0]='\n';
    bp2[1]='\n';
    bp2+=2;
  }  
  fwrite(buff2,1,bp2-buff2,stdout);
}
