typedef long long num;
num mul(num a,num b,num c){
  a=((a%c)+c)%c;
  b=((b%c)+c)%c;
  num r=0;
  num b2=b;
  for(int i=0;i<64;i++){
    if(a&(1LL<<i)){
      r=(r+b2)%c;
    }
    b2=(b2*2)%c;
  }
  return r;
}
