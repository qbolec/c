#include<cstdio>
#include<cstdlib>
const int P=10;
const int N=1<<P;
int A[N][N];
int B[N][N];
int C[N][N];
int D[N][N];
int afr,afc,bfr,bfc,cfr,cfc,m,n,p;
void mul()
{
  if(n<32 && m<32 && p<32){
    for(int i=0;i<n;i++)    
    for(int k=0;k<n;k++)
    for(int j=0;j<p;j++)
      D[cfr+i][cfc+j]+=A[afr+i][afc+k]*B[bfr+k][bfc+j];
  }else if(m>=n && m>=p){
    int m_=m/2;
    m-=m_;
    mul();
    afr+=m_;
    cfr+=m_;
    mul();
    m+=m_;
    afr-=m_;
    cfr-=m_;
  }else if(n>=m && n>=p){
    int n_=n/2;
    n-=n_;
    mul();
    afc+=n_;
    bfr+=n_;
    mul();
    n+=n_;
    afc-=n_;
    bfr-=n_;
  }else{
    int p_=p/2;
    p-=p_;
    mul();
    bfc+=p_;
    cfc+=p_;
    mul();
    p+=p_;
    bfc-=p_;
    cfc-=p_;
  }
}

int main(){
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++){
      A[i][j]=rand();
      B[i][j]=rand();
    }
  while(1){
  puts("zaczyna zwykla");
  for(int i=0;i<N;i++){
    int *Ci = C[i];
    for(int k=0;k<N;k++){
      const int *Bk  = B[k];
      const int Aik=A[i][k];
      
      for(int j=0;j<N;j++)
        Ci[j]+=Aik*Bk[j];      
    }
  }
  puts("konczy zwykla zaczyna szybka");
  n=m=p=N;
  mul();
  puts("konczy szybka");
  for(int i=0;i<N;i++)
  for(int j=0;j<N;j++)
    if(D[i][j]!=C[i][j]){
      puts("dupa");
      return 0;
    }     
  }
}
