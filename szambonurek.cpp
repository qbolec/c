#include<cstdio>
double x[100];
double y[100];
double eps=1e-9;
void solve(){
  int n;
  scanf("%d",&n);
  for(int i=0;i<n;i++)
    scanf("%lf %lf",x+i,y+i);
  double res=x[0];
  for(int g=0;g<n;g++)for(int d=0;d<n;d++)if(d!=g)for(int E=0;E<2;E++)for(int F=0;F<2;F++){
    double a= ((y[g]-E)-(y[d]-F))/(x[g]-x[d]);
    double b= (y[g]-E)-x[g]*a;
    int fb=n;
    for(int i=0;i<n;i++){
      double yi= x[i]*a+b;
      if(!(y[i]-1.0-eps<=yi && yi<=y[i]+eps)){
        fb=i;
        break;
      }
    }
    if(fb==n){
      puts("PRZESWIT");
      return;
    }
    if(fb==0)continue;
    double yi= x[fb]*a+b;
    double a2,b2;
    if(y[fb]<yi){
        a2= (y[fb]-y[fb-1])/(x[fb]-x[fb-1]);
        b2= y[fb]-x[fb]*a2;
    }else{
        a2= (y[fb]-y[fb-1])/(x[fb]-x[fb-1]);
        b2= y[fb]-1.0-x[fb]*a2;
    }
    //x2*a2+b2=x2*a+b
    double x2=(b-b2)/(a2-a);
    res>?=x2;
  }
  printf("%.2lf\n",res);
}
int main(){
  int d;
  scanf("%d",&d);
  while(d--)
    solve();
}
