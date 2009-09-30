#include<cstdio>
using namespace std;
typedef long long num;
num det(num x11,num x12,num x21,num x22){
  return x11*x22-x12*x21;
}
num gcd(num a,num b){
  if(!b)return a;
  return gcd(b,a%b);
}
int n;
void say(num p, num q){
  if(q<0){
    q=-q;
    p=-p;
  }
  if(!q){
   printf("don't know\n");
  }else{
    num g=gcd(p>0?p:-p,q);  
    p/=g;
    q/=g;
    if(q!=1)
      printf("%d/%d\n",(int)p,(int)q);
    else
      printf("%d\n",(int)p);
//    printf("%lld/%lld\n",p,q);
  }
}
int main(){
  scanf(" %d ",&n);
  while(n--){
    num x[2]={0,0};
    num y[2]={0,0};
    num s[2]={0,0};
    int eq=0;
    int mull=1;
    int sig=1;
    bool rn=false;
    num val=0;
    while(eq<2){
      char c;
      scanf("%c",&c);
      switch(c){
        case '\n':
//          printf("slash n");
          if(rn){
            rn=false;
            s[eq]-= sig*mull*val;
          }          
          sig=1;
          mull=1;
          eq++;          
          break;
        case '=':
//          printf("rowna sie");
          if(rn){
            rn=false;
            s[eq]-= sig*mull*val;
          }          
          sig=1;
          mull=-1;
          break;
        case ' ':
        case '\t':
        case '+':
//          printf("white");
          if(rn){
            rn=false;
            s[eq]-= sig*mull*val;
          }
          sig=1;
          break;       
        case 'x':
  //        printf("iks");
          if(rn){
            rn=false;
            x[eq]+= sig*mull * val;
          }else{
            x[eq]+= sig*mull;
          }
          sig=1;
          break;
        case 'y':
    //      printf("igrek");
          if(rn){
            rn=false;            
            y[eq]+= sig*mull * val;                        
          }else{
            y[eq]+= sig*mull;
          }
          sig=1;
          break;
        case '-':
      //    printf("minus");
          sig= -1;
          break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        //  printf("cyfra");
          if(!rn){
            rn=true;
            val=0;
          }
          val*=10;
          val+= c-'0';
          break;
      }
    }
    printf("%d x + %d y = %d\n%d x + %d y = %d\n",x[0],y[0],s[0],x[1],y[1],s[1]);
    num d=det(x[0],y[0],x[1],y[1]);
    num dx=det(s[0],y[0],s[1],y[1]);
    num dy=det(x[0],s[0],x[1],s[1]);
    if(!d){
      if(x[0]&&!y[0]){
      }else if(x[1]&&!y[1]){
      }else if(y[0]&&!x[0]){
      }else if(y[1]&&!x[1]){
      }else{
        
      }
    }else{
      say(dx,d);
      say(dy,d);
    }
    printf("\n");
    char buf[1023];
    gets(buf);
  }
}
