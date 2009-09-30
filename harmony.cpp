#include<cstdio>
#include<cmath>
using namespace std;
int main(){
  double H=0;
  for(int i=1;i<100;i++){
   H+=1.0/i;
   double L=log(i)/log(2);
   printf("%d %lf %lf\n",i,H,L);
  }
  scanf("%d");
}
