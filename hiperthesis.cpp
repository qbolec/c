#include<cstdio>
#include<cmath>
using namespace std;
double t[100]={2};
double r[100]={0};
double c[100]={5};
int main(){
  double f=1;
  for(int i=0;i<40;i++){
    printf("%d %lf\n",i,f);
    f=f*(i+2)/(i+1)+1.0;
  }
  for(int i=0;i<90;i++){
    r[i+1]=(1+r[i])/t[i];
    t[i+1]=2- 1/t[i];
    //c[i+1]=(1.0+1.0/(t[i]-1))*5*pow(c[i]*(t[i]-1)/5.0,1.0/t[i]);
    //c[i+1]=5*pow(c[i]*(t[i]-1)/5,1/t[i])+c[i]*pow(5/(c[i]*(t[i]-1)),1-1/t[i]);
    
    c[i+1] = (  6*pow(c[i]*(t[i]-1)/6.0,1.0/t[i])*(1.0+1.0/(t[i]-1)) +6.0);
    printf("i=%d r=%lf t=%lf c=%lf\n",i,r[i],t[i],c[i]);
  }
  scanf("%d",t);
  return 0;
}
