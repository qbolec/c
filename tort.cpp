#include<iostream>
using namespace std;
int main(){
long long n;
cin >> n;
long long from=0,to=n;
while(from+1<to){
  long long middle=(from+to+1)/2;
  if(middle*(middle+1)/2 + 1 < n ) from=middle;
  else to=middle;
}
cout << to << endl;
}
