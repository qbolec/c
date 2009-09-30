#include<set>
#include<algorithm>
#include<vector>
using namespace std;
double y[3023],z1[3023],z2[3023],x[3023];

void solve(){
  int n1,n2;
  set<double> s;
  scanf("%d",&n1);
  
  for(int i=0;i<n1;i++){
    scanf("%lf %lf",x+i,z1+i);
    s.insert(z1[i]);
  }
  scanf("%d",&n2);
  for(int i=0;i<n2;i++){
    scanf("%lf %lf",y+i,z2+i);
    s.insert(z2[i]);
  }
  int l1=0;
  for(int i=1;i<n1;i++)
    if(z1[i]>z1[l1])
      l1=i;

  int l2=0;
  for(int i=1;i<n2;i++)
    if(z2[i]>z2[l2])
      l2=i;
  for(int i=0;i<n1;i++){
    z1[i+n1]=z1[i+n1*2]=z1[i];
    x[i+n1]=x[i+n1*2]=x[i];
  }
  for(int i=0;i<n2;i++){
    z2[i+n2]=z2[i+n2*2]=z2[i];
    y[i+n2]=y[i+n2*2]=y[i];
  }
  l1+=n1;
  l2+=n2;
  int r1=l1;
  int r2=l2;
  double v=0;
  vector<double> zs(s.begin(),s.end());
  for(int i=zs.size();i--;){
    double now=zs[i];
//    printf("now=%lf\n",now);
    if(!i)break;
    double then=zs[i-1];
//    printf("then=%lf\n",then);
    while(z1[l1]>=now)l1--;
    while(z2[l2]>=now)l2--;
    while(z1[r1]>=now)r1++;
    while(z2[r2]>=now)r2++;
//    printf("%d %d %d %d\n",l1,r1,l2,r2);
    double xlT,xrT,ylT,yrT,xlB,xrB,ylB,yrB;
    xlT= x[l1+1]+ (x[l1]-x[l1+1])*(now-z1[l1+1])/(z1[l1]-z1[l1+1]);
    xlB= x[l1+1]+ (x[l1]-x[l1+1])*(then-z1[l1+1])/(z1[l1]-z1[l1+1]);
    xrT= x[r1-1]+ (x[r1]-x[r1-1])*(now-z1[r1-1])/(z1[r1]-z1[r1-1]);
    xrB= x[r1-1]+ (x[r1]-x[r1-1])*(then-z1[r1-1])/(z1[r1]-z1[r1-1]);

    ylT= y[l2+1]+ (y[l2]-y[l2+1])*(now-z2[l2+1])/(z2[l2]-z2[l2+1]);
    ylB= y[l2+1]+ (y[l2]-y[l2+1])*(then-z2[l2+1])/(z2[l2]-z2[l2+1]);
    yrT= y[r2-1]+ (y[r2]-y[r2-1])*(now-z2[r2-1])/(z2[r2]-z2[r2-1]);
    yrB= y[r2-1]+ (y[r2]-y[r2-1])*(then-z2[r2-1])/(z2[r2]-z2[r2-1]);

    double A=xrB-xlB;
    double B=yrB-ylB;
    double C=xrT-xlT;
    double D=yrT-ylT;
    
    double h=then-now;
    v+=((C-A)*(D-B)/3.0 + (B*C-2*D*C+A*D)/2.0 + C*D)*h;
    
  }
  printf("%lf\n",-v);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
}
