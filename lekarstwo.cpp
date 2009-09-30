#include<cstdio>
int gcd(int a,int b){
  if(!b)return a;
  return gcd(b,a%b);
}
int gcdex(int a,int b,int Awa,int Awb){
  if(!b)return Awa;
  int c=a/b;
  return gcdex(b,a%b,Awb,Awa-Awb*c);
}
int abs(int x){
  return x<0?-x:x;
}
int main(){
  int a,b,d;
  while(1){
    scanf("%d %d %d",&a,&b,&d);
    if(!a && !b && !d)return 0;
    int g=gcd(a,b);
    if(d%g!=0){
      puts("BRAK");
      continue;
    }
    int a2=a/g;
    int b2=b/g;
    // x*a2 + y*b2 = 1
    int x=gcdex(a2,b2,1,0);
    int y=(1-x*a2)/b2;
    int d2=d/g;
    //  a2 * x  % b2  ==  d % b2 
    //  a2 * x*d2  + b2*y*d2 = d2

    int l1=(b2+(d2*x)%b2)%b2;
    int r1=(l1*a  -  d)/b ;
    
    int r2=(a2+(d2*y)%a2)%a2;
    int l2= (r2* b  -  d)/a ;

    
    l1=abs(l1);
    r1=abs(r1);
    l2=abs(l2);
    r2=abs(r2);    
    if(l1 + r1 < l2+r2 || (l1+r1 == l2+r2 && l1*a + r1*b < l2*a + r2*b) ){
      printf("%d %d\n",l1,r1);
    }else
      printf("%d %d\n",l2,r2);    
    
  }
}
