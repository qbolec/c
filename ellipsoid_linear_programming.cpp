#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cassert>
using namespace std;
double B[100][100];
double px[102];
double py[102];
double d[102][102];
double aTB[102];
double Ba[102];
double y[102];
const double e=0.000002;
void solve(){
  int m;
  scanf("%d",&m);
  for(int i=0;i<m;i++)
    scanf("%lf %lf",px+i,py+i);
  px[m]=px[0];
  py[m]=py[0];
  for(int i=m+1;i--;)
  for(int j=m+1;j--;)
  d[i][j]=sqrt((double)((px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j])));
  for(int i=m;i--;)
    y[m]=1000;
  for(int i=m;i--;)
    for(int j=m;j--;)
      B[i][j]=0;

  for(int i=m;i--;)
    B[i][i]=1000*1000*110;
  double tau=1.0/(double)(m+1);
  double delta=(double)(m*m)/(double)(m*m-1);
  double sigma=2.0*tau;
  int loops=3600;
  loop:
    if(!--loops)goto end;
    for(int i=m;i--;)
      if(y[i]<0){//-1*y[i]<=0
        int id1=i;
        double ajTBaj=      
          B[id1][id1];
        double factor=tau/sqrt(ajTBaj);
        for(int id=m;id--;)
          y[id]+= factor*(B[id][id1]);
        for(int id=m;id--;)
          aTB[id]=(B[id1][id]);
        for(int id=m;id--;)
          Ba[id]=(B[id][id1]);
        factor=sigma/ajTBaj;
        for(int r=m;r--;)
          for(int c=m;c--;)
            B[r][c]=delta*(B[r][c]-factor*Ba[r]*aTB[c]);    
        
        goto loop;      
        
      }
    for(int i=m;i--;)
      if(y[i]>5000){//1*y[i]<=5000
        int id1=i;
        double ajTBaj=      
          B[id1][id1];
        double factor=tau/sqrt(ajTBaj);
        for(int id=m;id--;)
          y[id]-= factor*(B[id][id1]);
        
        for(int id=m;id--;)
          aTB[id]=(B[id1][id]);
        for(int id=m;id--;)
          Ba[id]=(B[id][id1]);
     
        factor=sigma/ajTBaj;
        for(int r=m;r--;)
          for(int c=m;c--;)
            B[r][c]=delta*(B[r][c]-factor*Ba[r]*aTB[c]);    
        
        goto loop;      
        
      } 
    for(int i=m;i--;)
      if(y[i]+y[(i+1)%m]<d[i][i+1]-e){
        //violation of ... you know what   
        int id1=i;
        int id2=(i+1)%m;
        double ajTBaj=      
          B[id1][id1]+B[id1][id2]+B[id2][id2]+B[id2][id1];
        double factor=tau/sqrt(ajTBaj);
        for(int id=m;id--;)
          y[id]+= factor*(B[id][id1]+B[id][id2]);
        for(int id=m;id--;)
          aTB[id]=(B[id1][id]+B[id2][id]);
        for(int id=m;id--;)
          Ba[id]=(B[id][id1]+B[id][id2]);
        
        factor=sigma/ajTBaj;
        for(int r=m;r--;)
          for(int c=m;c--;)
            B[r][c]=delta*(B[r][c]-factor*Ba[r]*aTB[c]);    
          
          
        goto loop;
      }
    for(int id1=m;id1--;)
      for(int id2=id1-1;id2-->0;){
        if(y[id1]+y[id2]>d[id1][id2]+e && id1-id2!=m-1){
          double ajTBaj=      
            B[id1][id1]+B[id1][id2]+B[id2][id2]+B[id2][id1];
          double factor=tau/sqrt(ajTBaj);
          for(int id=m;id--;)
            y[id]-= factor*(B[id][id1]+B[id][id2]);
          for(int id=m;id--;)
            aTB[id]=(B[id1][id]+B[id2][id]);
          for(int id=m;id--;)
            Ba[id]=(B[id][id1]+B[id][id2]);
        
          factor=sigma/ajTBaj;
          for(int r=m;r--;)
            for(int c=m;c--;)
              B[r][c]=delta*(B[r][c]-factor*Ba[r]*aTB[c]);    
          goto loop;
        }
      }
  end:      
  for(int i=0;i<m;i++){
    assert(y[i]>=0);
    assert(y[i]<10000);
    printf("%.20lf\n",y[i]); 
  }
  
      
}

int main(){
  int t;
  scanf("%d",&t);
  while(t--)solve();
}
