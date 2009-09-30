#include<cstdio>
#include<cmath>
const int N=100;
double S[N][N];
double H[N];
const double eps=1e-9;
char s(double x){
  if(x<-eps)return '-';
  if(x>eps)return '+';
  return '0';
}
int main(){
  for(int n=1;n<N;n++)
    H[n]=H[n-1]+1.0/n;
  for(int m=0;m<N;m++)
    S[m][0]=m;
  for(int f=1;f<N;f++)
    for(int m=0;m<N-f;m++)
      if(m==0){
        S[m][f]= (1+S[m][f-1] + (f-1)*S[m+1][f-2])/f;
      }else{
        S[m][f]= ((m+1)*(1+S[m][f-1]) + (f-1)*S[m+1][f-2])/(m+f);
      }

//  const double a=1.0-1.0/exp(1.0);
//  printf("a=%lf\n",a*a);
  for(int m=0;m<30;m++){
    for(int f=1;f<30;f++){
//      printf("%c$%.3lf$ ",f?'&':' ',S[m+1][f-1]-S[m][f]);
      printf("%c",s(S[m][f]-S[m+1][f-1]));
    }
    puts("\\\\");
  }
  scanf("%d");
}
