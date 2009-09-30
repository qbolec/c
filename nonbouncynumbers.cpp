#include<iostream>
using namespace std;
long long p[200][200];
int main(){
  for(int n=1;n<=110;n++){
    p[n][0]=p[n][n]=1;
    for(int k=1;k<n;k++)
      p[n][k]=p[n-1][k]+p[n-1][k-1];
  }
  long long nb=9;
  for(int n=2;n<=100;n++){

    cout << n << " " <<p[n+8][8]<<"+" << p[n+9][9]-1<<endl;
    nb+=p[n+8][8]+p[n+9][9]-1-9;
  }
  cout << nb << endl;
  cin >> nb;
}
