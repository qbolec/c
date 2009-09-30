/*
dwu:
  jeden*jeden = 4 + 4*3/2 = 4 + 6 = 10
  to by bylo na tyle, czyli zostaje 6 nierozkladalnych
  
trzy:
  jeden*jeden*jeden = 4 + 4*3 + 4 = 20
  jeden*dwa = 4 * 6 = 24
  razem  = 44
  pozostaje 20 nierozkladalnych
  
cztery:
  jeden*jeden*jeden*jeden = 4 + 4*3 + 4*3/2 + 4 * 3 + 1 = 35
  jeden*jeden*dwa = 4*6 + 4*3/2*6 = 60
  jeden*trzy = 4 * 20 = 80
  dwa*dwa = 6 + 6*5/2 = 21
  to razem bylo-nie-bylo tylko 196, czyli zostaje 60 nierozkladalnych

np. 1xxxx+1xxx+1xx+0x+(1+ALFA)

1 1 1 0 1  vs.  1 a b

0 1+a 1+b 0 1
0 0 1+b+a+aa b+ab  1
0 0 0   b+ab+a+ab+aa+aaa  1+b+bb+ab+aab

{
  b+ab+a+ab+aa+aaa==0
  1+b+bb+ab+aab == 0
}

{
  b+a+aa+aaa==0
  1+b+bb+ab+aab == 0
}
{
  ab+aa+aaa+a==0
  b+a+aa+aaa==0
  1+b+bb+ab+aab == 0
}
{
  a+ab==0
  b+a+aa+aaa==0
  1+b+bb+ab+aab == 0
}
{
  b==1
  1+a+aa+aaa==0
  1+a+aa == 0
  a=0
}


*/
#include<cstdio>
#include<vector>
using namespace std;
const int ALFA=2;
struct F4{
  char x;
  F4 operator + (const F4 & other)const{
    return F4( x^other.x);
  }
  F4 operator * (const F4 & other)const{
    char result=0;
    if(other.x&1)result^=x;
    if(other.x&ALFA)result^= (x<<1);
    if(result& 4)result^=7;
    return F4(result);
  }
  void dump(){
    switch(x){
      case 0:printf("0");break;
      case 1:printf("1");break;
      case 2:printf("ALFA");break;    
      case 3:printf("(1+ALFA)");break;
    }
  }
  F4(char init){
    x=init;
  }
};
bool is_divisible(vector<F4> n,vector<F4> q){
  for(int i=n.size();i-->=q.size();){
    F4 m=n[i];
    for(int j=0;j<q.size();j++){
      n[i-j]= n[i-j]+ m*q[q.size()-1-j];
    }
  }
  for(int i=q.size();i--;)
    if(n[i].x)
      return false;
  return true;
}
void dump(vector<F4> n){
            for(int i=n.size();i--;){
              n[i].dump();
              for(int j=0;j<i;j++)
                printf("x");
              if(i)printf("+");
            }
  
}
F4 eval(vector<F4> n, F4 x){
  F4 result(0);
  for(int i=n.size();i--;){
    result= result*x;
    result= result + n[i];
  }
  return result;
}
int main(){
  vector<F4> n(5,1);
  vector<F4> q(3,1);
  for(n[0].x=0;n[0].x<4;n[0].x++)
    for(n[1].x=0;n[1].x<4;n[1].x++)
      for(n[2].x=0;n[2].x<4;n[2].x++)
        for(n[3].x=0;n[3].x<4;n[3].x++){
          bool isok=true;
          F4 x(0);
          for(x.x=0;x.x<4;x.x++)
            if(!eval(n,x).x){
              isok=false;
              break;
            }
          if(!isok)continue;
          for(q[0].x=0;q[0].x<4;q[0].x++)
            for(q[1].x=0;q[1].x<4;q[1].x++)
              if(is_divisible(n,q)){
                isok=false;
                break;
              }
          if(isok){
            dump(n);
            puts("");
          }
        }
}
