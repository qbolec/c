#include<cstdio>
#include<vector>
using namespace std;
const int MX=1000010;
const int P=1000003;
#define CLAMP(x) ((x)<P?(x):(x)-P)
int two2k[MX]={1,2,4};
int factor[MX];
int factorexp[MX];
int factor2exp[MX];
int fi[MX]={0,1,1};
int gcd(int a,int b){
  if(!b)return a;
  return gcd(b,a%b);
}
int gcdex(int a,int b,int ax,int bx){
  if(!b)return ax;
  int r=a/b;
  return gcdex(b,a%b,bx,ax-bx*r);
}
int invert(int x){//modulo P
  int result=(gcdex(x,P,1,0)+P);
  return CLAMP(result);
}
void solve(){
  int a,b;
  scanf("%d %d",&a,&b);
  if(!a || !b){
    puts("0");
    return;
  }
  int r=gcd(a,b);
  int g=(a+b)/r;
  vector<int> divisor;
  vector<int> divisorexp;
  vector<int> divisor2exp;
  int gcopy=g;
  while(gcopy!=1){
    divisor.push_back(factor[gcopy]);
    divisorexp.push_back(factorexp[gcopy]);
    divisor2exp.push_back(factor2exp[gcopy]);
    gcopy/=factor2exp[gcopy];
  }
  int divisors=divisor.size();
  vector<int> exponent(divisors,0);
  int product=1;
  int fixed_points=0;
  while(1){
    fixed_points+= ((long long)two2k[product*r]*(long long)fi[g/product])%P;
    fixed_points=CLAMP(fixed_points);
    int pos=0;
    while(pos<divisors){
      exponent[pos]++;
      if(exponent[pos]>divisorexp[pos]){
        product/=divisor2exp[pos];
        exponent[pos]=0;
        pos++;
      }else{
        product*=divisor[pos];
        break;
      }
    }
    if(pos==divisors)
      break;    
  }
  int cycles=((long long)fixed_points * (long long)invert(g))%P;
  int result= (two2k[a+b]+P-cycles)%P;
  printf("%d\n",result);
}

int main(){
  for(int i=2;i<MX;i++){
    if(!factor[i]){
      factor[i]=i;
      factorexp[i]=1;
      factor2exp[i]=i;
      if(i<MX/i)
        for(int j=i*i;j<MX;j+=i){
          if(!factor[j]){
            factor[j]=i;
            int x=j;
            factor2exp[j]=1;
            while(x%i==0){
              x/=i;
              factorexp[j]++;
              factor2exp[j]*=i;              
            }
          }
        }
    }
  }
  for(int i=2;i<MX;i++){
    int x=i/factor2exp[i];
    fi[i]=fi[x]*(factor2exp[i]-factor2exp[i]/factor[i]);
  }
  for(int i=2;i<MX;i++){
    two2k[i]=CLAMP(two2k[i-1]*2);
  }
  int c;
  scanf("%d",&c);
  while(c--)
    solve();
}
