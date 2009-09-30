#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
double x[100];
double y[100];
const double a=1.4;//sqrt(2);
int main(){
  x[0]=y[0]=0;
  x[1]=-a*a;
  y[1]=a;
  for(int k=2;k<50;k++){
    switch(k%4){
      case 0:
        x[k]=-pow(a,k-2);
        y[k]= pow(a,k+1);
        break;
      case 1:
        x[k]=-pow(a,k+1);
        y[k]=-pow(a,k-2);
        break;
      case 2:
        x[k]= pow(a,k-2);
        y[k]=-pow(a,k+1);
        break;
      case 3:
        x[k]= pow(a,k+1);
        y[k]= pow(a,k-2);
        break;
    }
  }
  double alg=0;
  for(int k=1;k<50;k++){
    alg+= sqrt((x[k]-x[k-1])*(x[k]-x[k-1])+(y[k]-y[k-1])*(y[k]-y[k-1]));
    double opt=fabs(x[k])<?fabs(y[k]);
    printf("x:%3.2lf\ty:%3.2lf\talg:%3.2lf\topt:%3.2lf\tcomp:%3.2lf \n",x[k],y[k],alg,opt,alg/opt);
  }
  system("pause");

}
