#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
template<int FILLED=2,int ROWS=20000>
struct sparsematrix{
  int col[ROWS][FILLED];
  double data[ROWS][FILLED];  
  int rows,cols;
  sparsematrix(int rows,int cols):rows(rows),cols(cols){}
};
template<int FILLED,int ROWS>
vector<double> b_minus_A_x(vector<double> & b,sparsematrix<FILLED,ROWS> & A,vector<double> & x){
  if(A.cols!=x.size() || b.size()!=A.rows)throw "Size mismatch";
  vector<double> result=b;
  for(int r=result.size();r--;)
    for(int i=FILLED;i--;)
      result[r]-=A.data[r][i]*x[A.col[r][i]];
  return result;
}

template<int ROWS=100,int COLS=100>
struct matrix{
  int rows,cols;
  double data[ROWS][COLS];
  matrix(int rows,int cols):rows(rows),cols(cols){
    for(int r=rows;r--;)
      for(int c=cols;c--;)
        data[r][c]=0;
  }  
};
template<int FILLED,int ROWS,int COLS>
matrix<COLS,COLS> AtD_minus2_A(vector<double> &v,sparsematrix<FILLED,ROWS> &A){
  matrix<COLS,COLS> result(A.cols,A.cols);
/*
  for(int r=result.rows;r--;)
    for(int c=result.cols;c--;){
      result.data[r][c]=0;
      for(int i=A.rows;i--;)
        result.data[r][c]+= A[i][r]*A[i][c]/(v[i][0]*v[i][0]);
    }
*/
/*
  for(int i=A.rows;i--;){
    double factor=v[i]?1/(v[i]*v[i]):0;
    for(int ri=FILLED;ri--;)
      for(int ci=FILLED;ci--;){
        int r=A.col[i][ri];
        int c=A.col[i][ci];
        result.data[r][c]+= A[i][r]*A[i][c]*factor;
      }
  }    
*/ 
  for(int i=A.rows;i--;){
    double factor=v[i]?1/(v[i]*v[i]):0;
    for(int ri=FILLED;ri--;)
      for(int ci=FILLED;ci--;){
        int r=A.col[i][ri];
        int c=A.col[i][ci];
        result.data[r][c]+= factor;
      }
  } 
  return result;
}
template<int N>
matrix<N,N> invert(matrix<N,N> A){
  if(A.rows!=A.cols)throw "Must be square";
  int n=A.rows;
  matrix<N,N> result(n,n);  
  for(int i=n;i--;)
    result.data[i][i]=1;
  for(int c=n;c--;){
    int goodr=-1;
    for(int r=c;r--;)    
      if(A.data[r][c]){
        goodr=r;
        break;
      }
    if(goodr<0)throw "Irreversible";
    for(int i=n;i--;){
      swap(A.data[goodr][i],A.data[c][i]);
      swap(result.data[goodr][i],result.data[c][i]);
    }
    double factor=1/A.data[c][c];
    for(int i=n;i--;){
      A.data[c][i]*=factor;
      result.data[c][i]*=factor;
    }
    for(int r=n;r--;)if(r!=c){
      double factor=A.data[r][c];
      if(factor)
        for(int i=n;i--;){
          A.data[r][i]-=factor*A.data[c][i];
          result.data[r][i]-=factor*result.data[c][i];
        }      
    }

  }
}
template<int N>
vector<double> A_v(const matrix<N,N> & A,const vector<double> & v){
  if(v.size()!=A.cols)throw "Size mismatch";
  vector<double> result(A.rows,0);
  for(int r=result.size();r--;)
    for(int c=v.size();c--;)
      result[r]+=A.data[r][c]*v[c];
  return result;
}
template<int FILLED,int ROWS>
vector<double> A_v(const sparsematrix<FILLED,ROWS> & A,const vector<double> & v){
  if(v.size()!=A.cols)throw "Size mismatch";
  vector<double> result(A.rows,0);
  for(int r=result.size();r--;)
    for(int ci=FILLED;ci--;)
      result[r]+=A.data[r][ci]*v[A.col[r][ci]];
  return result;
}
void solve(){
  int n;
  scanf("%d",&n);
  sparsematrix<2,20000> A(n*(n-1)/2+n,n);
  int px[100];
  int py[100];
  double d[100][100];
  for(int i=0;i<n;i++)
    scanf("%d %d",px+i,py+i);
  for(int i=n;i--;)
  for(int j=n;j--;)
  d[i][j]=sqrt((double)((px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j])));
  int e=0;
  vector<double> b(n*(n-1)/2+n);
  for(int i=0;i<n;i++){
    A.col[e][0]=i;
    A.col[e][1]=(i+1)%n;
    A.data[e][0]=-1;
    A.data[e][1]=-1;
    b[e]=d[i][(i+1)%n];
    e++;
  }
  for(int i=n;i--;)
    for(int j=i;j--;){
      A.col[e][0]=i;
      A.col[e][1]=j;
      A.data[e][0]=1;
      A.data[e][1]=1;
      b[e]=d[i][j];
      e++;
    }
  vector<double> x(n,0);
  vector<double> c(n,1);
  const double gamma=0.6;
  while(true){
    vector<double> v=b_minus_A_x(b,A,x);
    vector<double> hx=A_v( invert(AtD_minus2_A<2,20000,100>(v,A)) , c );
    vector<double> hv=A_v( A, hx);
    for(int i=hv.size();i--;)
      hv[i]=-hv[i];
    bool ok=false;
    for(int i=hv.size();i--;)
      if(hv[i]<0){
        ok=true;
        break;  
      }
    if(!ok)throw "Unbounded";
    double alfa=1e100;
    for(int i=hv.size();i--;){
      double m=-v[i]/hv[i];
      if(m<=0)
        alfa<?=m*gamma;
    }
    for(int i=x.size();i--;)
      x[i]+=alfa*hx[i];   
      
    for(int i=x.size();i--;)
      printf("x[%d]=%lf\n",i,x[i]);
  }
}
int main(){
  try{
  int t;
  scanf("%d",&t);
  while(t--)solve();
  }catch(const char * c){
    puts(c);
  }
}
