#include<iostream>
using namespace std;
int main(){
  for(int i=0;i<100;i++){
    int u=i/10;
    int l=i%10;
    int s=(u+l)%9;
    int d=(u-l)%11;
    cout << i << " " << 56*s - 55*d << endl;
  }
  int i;
  cin >> i;
}
