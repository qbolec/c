#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
double Ax,Ay,Bx,By,Cx,Cy,Ex,Ey,Fx,Fy,Sx,Sy;
double det(double x11,double x12,double x21,double x22){
  return x11*x22-x12*x21;
}
int main(){
  int AAx,AAy,CCx,CCy;
  scanf("%d %d %d %d %lf %lf",&AAx,&AAy,&CCx,&CCy,&Bx,&By);
  int minx=AAx<?CCx;
  int miny=AAy<?CCy;
  int maxx=AAx>?CCx;
  int maxy=AAy>?CCy;
  Ax=AAx;
  Ay=AAy;
  Cx=CCx;
  Cy=CCy;
  Ex=(Ax+Bx)*0.5;
  Ey=(Ay+By)*0.5;
  Fx=(Cx+Bx)*0.5;
  Fy=(Cy+By)*0.5;
  // Sx* Bx-Ax + Sy * By-Ay = Ex* (Bx-Ax) + Ey * (By-Ay)
  // Sx* Bx-Cx + Sy * By-Cy = Fx* (Bx-Cx) + Fy * (By-Cy)
    
  double d=  det(Bx-Ax,By-Ay,Bx-Cx,By-Cy);
  double dSx=det(Ex* (Bx-Ax) + Ey * (By-Ay),By-Ay,Fx* (Bx-Cx) + Fy * (By-Cy),By-Cy);
  double dSy=det(Bx-Ax,Ex* (Bx-Ax) + Ey * (By-Ay),Bx-Cx,Fx* (Bx-Cx) + Fy * (By-Cy));
  Sx=dSx/d;
  Sy=dSy/d;
  
  Ax-=Sx;
  Bx-=Sx;
  Cx-=Sx;
  Ay-=Sy;
  By-=Sy;
  Cy-=Sy;
  double a=atan2(Ay,Ax);
  double c=atan2(Cy,Cx);
  const double Q=acos(0);
  const double F=Q*4.0;
  double b=atan2(By,Bx)+F;
  double r=sqrt(Ax*Ax+Ay*Ay);
  while(a<b)
    a+=F;
  while(c<b)
    c+=F;
  if(a>c){
    a-=F;
  }else{
    c-=F;
    double t=a;
    a=c;
    c=t;
  }
  for(int i=0;i<4;i++){
    double x=Q*i;
    while(x<a)
      x+=F;
    if(a<x && x<c){
      switch(i){
        case 0:
          maxx=ceil(Sx+r);
        break;
        case 1:
          maxy=ceil(Sy+r);
        break;
        case 2:
          minx=floor(Sx-r);
        break;
        case 3:
          miny=floor(Sy-r);
        break;        
      }
    }
  }
  printf("%d\n", (maxx-minx)*(maxy-miny));
  return 0;
}
