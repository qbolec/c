#include<cmath>
#include<cstdio>
int x[200];
int y[200];
int main(){
  while(1){
    int n;
    scanf("%d",&n);
    if(!n)return 0;
    for(int i=0;i<n;i++)
      scanf("%d %d",x+i,y+i);        
    double a=0;
    if(n==1){
      printf("%.12lf\n%.12lf\n%.12lf\n%.12lf\n\n",0.0,0.0,(double)x[0],(double)y[0]);
      continue;
    }
    for(int i=1;i<n;i++)
      a+=atan2(y[i]-y[i-1],x[i]-x[i-1]);      
    a=fmod(a+M_PI*2.0,M_PI*2.0);
    double b=(M_PI*2.0-a)/(n-1);
    printf("%.12lf\n%.12lf\n",0.0,b);
    double xwy=sin(b);
    double ywy=cos(b);
    double xwx=cos(b);
    double ywx=-sin(b);
    for(int i=0;i<n;i++)
      printf("%.12lf %.12lf\n",xwx*x[i]+ywx*y[i],xwy*x[i]+ywy*y[i]);
    puts("");
  }
}
