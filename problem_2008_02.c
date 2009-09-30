long long invert(long long a,long long b,long long x,long long y){
  if(!a){
    if(b!=1){
      return 0;
    }
    return y;
  }
  return invert(b%a,a,y-b/a*x ,x);
}
long gcd(long a,long b){
  if(!a)return b;
  return gcd(b%a,a);
}
long long lcm(long a, long b){
  return (long long)a/gcd(a,b)*b;
}
long long prob_2008_02(long p,long q,long long e,long long d[],long dsize){
  long long fi=(long long)(p-1)*(p==q?p:q-1);
  long long m=p==q?fi:lcm(p-1,q-1);
  long i;
  e%=m;
  if(e<0)e+=m;
  long long b=invert(e,m,1,0);
  if(b<0)b+=m;
  long long ans=fi/m;
  if(dsize&&ans){
    d[0]=b;
    for(i=1;i<dsize && i<ans;i++)
      d[i]=d[i-1]+m;
  }
  return ans;
}
