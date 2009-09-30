#include<cstdio>
#include<cassert>
using namespace std;
const int MAX_LEN=1000000;
const int MAX_M=100000;
unsigned char X[MAX_LEN];
unsigned char Y[MAX_LEN];
unsigned char Z[MAX_LEN];
int S[MAX_LEN];// -1=*  0=Known -2=contradict >1=voices
int C[MAX_LEN];
int Cc=0;
int G[MAX_M];//good n's
char U[MAX_M];
int L[MAX_M];
int R[MAX_M];
int Lc=0;
int Gc=0;
void solve(){
  int m;
  scanf("%d %s %s",&m,X,Y);
  int len;
  Cc=0;
  for(len=0;X[len];len++){
    if(Y[len]=='*')
      S[len]=-2;
    else if(X[len]=='*')
      S[len]=-1;
    else{
      Z[len]= (X[len]+26-Y[len])%26;
      S[len]=0;
      C[Cc++]=len;
    }
  }
  Gc=0;
  for(int n=1+m/2;n<=m;n++){
    bool bad=false;
    //
    Lc=0;
    for(int c=0;c<Cc;c++){
      int i=C[c];
      int z=Z[i];      
      i%=n;
      if(U[i]==0){
        L[Lc++]=i;
        U[i]=1;
        R[i]=z;
      }else
        continue;            
      for(int p=i;p<len;p+=n){
        if(!S[p] && Z[p]!=z){
          bad=true;
          break;
        }
      }
      if(bad)
        break;
    }    
/*    
    while(c<Cc && C[c]<n)
      c++;
    for(;c<Cc;c++){
      int p=C[c]-n;
      while(p>=0 && S[p])
        p-=n;
      if(p>=0 && Z[p]!=Z[C[c]] ){
        bad=true;
        break;
      }
    }
*/
    if(!bad){
      G[Gc++]=n;     
      while(Lc--){
        int i=L[Lc];
        int z=R[i];
        for(int p=i;p<len;p+=n){
          if(S[p]>0){
            if(Z[p]==z)
              S[p]++;
            else
              S[p]=-2;
          }else if(S[p]==-1){
            Z[p]=z;
            S[p]=1;
          }
        }
        U[L[Lc]]=0;
      }       
    }else
      while(Lc--)
        U[L[Lc]]=0;    
  }
/*  
  for(int g=0;g<Gc;g++){  
    int n=G[g];
    Lc=0;
    for(int c=0;c<Cc;c++){
      int i=C[c];
      int z=Z[i];      
      i%=n;
      if(U[i]==0){
        L[Lc++]=i;
        U[i]=1;
      }else
        continue;            
      for(int p=i;p<len;p+=n){
        if(S[p]>0){
          if(Z[p]==z)
            S[p]++;
          else
            S[p]=-2;
        }else if(S[p]==-1){
          Z[p]=z;
          S[p]=1;
        }
      }
    }    
    while(Lc--)
      U[L[Lc]]=0;
  }
*/  
  for(int i=0;i<len;i++)
    if(X[i]=='*'  && S[i]==Gc)
      X[i]='A'+(Y[i]-'A'+Z[i])%26 ;
  printf("%s\n",(const char *)X);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
  return 0;
}
