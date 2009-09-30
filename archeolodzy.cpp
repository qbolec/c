#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n;
double Ax,Ay,Bx,By,Cx,Cy,Ex,Ey,Fx,Fy,Sx,Sy;
double gcd(double a,double b){
  if(b<6.0/200.0)
    return a;
  return gcd(b, fmod(a,b));
}
double det(double x11,double x12,double x21,double x22){
  return x11*x22-x12*x21;
}
int main(){
  scanf("%d",&n);
  while(n--){
  scanf("%lf %lf %lf %lf %lf %lf",&Ax,&Ay,&Bx,&By,&Cx,&Cy);
  Ex=(Ax+Bx)*0.5;
  Ey=(Ay+By)*0.5;
  Fx=(Cx+Bx)*0.5;
  Fy=(Cy+By)*0.5;
  // Ey - t* Bx-Ex  = Fy - u * Bx-Fx
  // Ex + t* By-Ey  = Fx + u * By-Fy

  //   t* Ex-Bx + u * Bx-Fx = Fy-Ey
  //   t* By-Ey + u * Fy-By = Fx-Ex
  double d= det(Ex-Bx, Bx-Fx, By-Ey, Fy-By);
  double dt=det(Fy-Ey, Bx-Fx, Fx-Ex, Fy-By);
  double t=dt/d;
  Sx=Ex + t* (By-Ey);
  Sy=Ey - t* (Bx-Ex);
  Ax-=Sx;
  Bx-=Sx;
  Cx-=Sx;
  Ay-=Sy;
  By-=Sy;
  Cy-=Sy;
  double a[3];
  a[0]=atan2(Ay,Ax)+10.0;
  a[1]=atan2(By,Bx)+10.0;
  a[2]=atan2(Cy,Cx)+10.0;
  sort(a,a+3);
  double f=a[2]-a[1];
  double g=a[1]-a[0];
  double h=acos(0)*4.0-(f+g);
  double z=gcd(gcd(f,g),h);  
  int Z=(int)floor((acos(0)*4.0 /z)+0.5);
  z<?=200;
  printf("%d\n",Z);
  
  }
  return 0;
}
