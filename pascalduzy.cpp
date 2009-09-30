#include<iostream>
using namespace std;
unsigned long long p[21][21];
int main(){
  for(int n=0;n<=20;n++){
    p[n][0]=p[n][n]=1;
    for(int k=1;k<n;k++){
      p[n][k]=p[n-1][k]+p[n-1][k-1];
    }
  }
  unsigned long long res=0;
  unsigned long long silnia=1;
  for(int i=0;i<=20;i++,silnia*=i)
    res+=p[20][i]*p[20][i]*silnia;  
  cout << res << endl;
}
