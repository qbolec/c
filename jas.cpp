#include<cstdio>
typedef long long n;
n a,b,c,d;
n inv(n v,n u,n x,n y){
  if(!u)return x/v;
  return inv(u,v%u,y,((x-v/u*y)%b+b)%b);
}
int main(){
  scanf("%lld%lld%lld",&a,&b,&c);
  if(a>b)a^=b^=a^=b;
  d=inv(a,b,c%b,0);
  printf("%lld\n",d>=0&&d*a<=c&&!((c-d*a)%b)?d+(c-d*a)/b:-1LL);
}
