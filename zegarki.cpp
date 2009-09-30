#include<cstdio>
#include<algorithm>
using namespace std;
int n;
int w[1024];
int main(){
  scanf("%d",&n);
  for(int i=n;i--;)
    scanf("%d",w+i);
  sort(w,w+n);
  n=unique(w,w+n)-w;
//  t*w[0]=t*w[1]+ m*60  
  double t=60.0/(w[1]-w[0]);
  for(int i=2;i<n;i++){
    double r=60.0/(w[i]-w[0]);
    t=lcm(t,r);  
  }
  printf("%lf\n",t);
}
