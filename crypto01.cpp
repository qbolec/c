//#include<cstdio>
#include<iostream>
#include<ctime>
using namespace std;
typedef unsigned long long num;
const num P=4000000007LL  ;
const num D=P-1;  //2*17*211*233*2393;
const num G=5; //generator
const num H=(D/2-1)/2;
num pw(num x,num k){
  if(!k)
    return 1;
  num h=pw(x,k/2);
  if(k&1)return (((h*x)%P)*h)%P;
  return (h*h)%P;
}
num gcdex(num x,num y,num a,num b){
  if(!x)return b;
  num r=y/x;
  return gcdex(y%x,x,(P+b-(r*a)%P)%P,a);
}
num invert(num x){
  return (P+gcdex(x,P,1,0))%P;
}
int main(){

  num x;
  cin>> x;
  num y=pw(x,D/2);
  //if(y==pw(G,D/2))puts("HUJ A NIE ZADANIE");
  //if(y*y%P!=y)puts("Glupim");
  //y jest pierwiastkiem z y :)
  num z=y;
  //z*z = y = x ^ D/2
  //z*z = y = x*  x ^ (D/2-1)
  //z*z =    x*  (x^h)*(x^h)
  num w= pw(x,H);
  //z*z = x*w*w
  //z/w = sqrt(x)
  num s= (z* invert(w))%P;
  num s2= P-s;
  if(s*s%P!=x)while(1);
  if(s2*s2%P!=x)while(1);
  tm * t=gmtime((const time_t *)&s);
  if(!t || t->tm_year < 70 || t->tm_year>130)t=gmtime((const time_t *)&s2);  
  char *c = asctime(t);
  
  puts(c);

}
