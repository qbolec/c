#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
template<typename T>
T Abs(const T & x){
  return x<0?-x:x;
}
template<typename T>
vector<vector<T> > invert_matrix(vector<vector<T> > A){
  assert(A.size());
  assert(A.size()==A[0].size());
  const int n=A.size();
  vector<vector<T> > I(n,vector<T>(n,0));
  for(int i=0;i<n;i++)
    I[i][i]=1;
  for(int i=0;i<n;i++){
    int k=i;
    for(int j=i+1;j<n;j++)
      if(Abs(A[j][i])>Abs(A[k][i]))
        k=j;
    assert(Abs(A[i][i])>0.000001);
    swap(A[i],A[k]);
    swap(I[i],I[k]);
    const T h=A[i][i];
    for(int j=i+1;j<n;j++)
      A[i][j]/=h;
    A[i][i]=1;
    for(int j=0;j<n;j++)
      I[i][j]/=h;
    for(int j=0;j<n;j++)if(i!=j){
      const T f= A[j][i];
      A[j][i]=0;
      for(int k=i+1;k<n;k++)
        A[j][k] -= f*A[i][k];
      for(int k=0;k<n;k++)
        I[j][k] -= f*I[i][k];
    }
  }
  return I;
}
int main(){
  int n;
  scanf("%d",&n);
  const int m=n*n;
  vector<vector<double> > A(m,vector<double>(m,0));
  for(int i=0;i<n;i++)
  for(int j=0;j<n;j++){
    const int r=i*n+j;
    for(int di=-1;di<=1;di++)
    for(int dj=-1;dj<=1;dj++)
    if(di || dj){
      int ii=i+di;
      int jj=j+dj;
      if(ii>=0 && jj>=0 && ii<n && jj<n){
        A[r][r]--;
        const int rr=ii*n+jj;
        A[r][rr]=1;
      }
    }
  }
  for(int i=0;i<m;i++)
    A[0][i]=0;
  A[0][0]=1;
  puts("A=");
  for(int i=0;i<m;i++){
    for(int j=0;j<m;j++)
      printf("%.1lf ",A[i][j]);
    puts("");
  }
  vector<vector<double> > I=invert_matrix(A);
  puts("I=");
  for(int i=0;i<m;i++){
    for(int j=0;j<m;j++)
      printf("%.1lf ",I[i][j]);
    puts("");
  }
  
  vector<vector<int> > T(m,vector<int>(n,0));
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      T[i][j]=rand()%32;
  vector<double> E(m,0);
  for(int x=0;x<m;x++){
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        E[x]+= T[i][j]*A[x][i*n+j];
  }
  vector<vector<double> > D(m,vector<double>(n,0));
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
      for(int x=0;x<m;x++){
        D[i][j]+= I[i*n+j][x]*E[x];
      }
    }
  puts("T=");
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      printf("%d ",T[i][j]);
    puts("");
  }
  puts("D=");
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      printf("%.1lf ",D[i][j]);
    puts("");
  }

  system("PAUSE");
}
