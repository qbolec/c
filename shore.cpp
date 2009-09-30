#include<iostream>
#include<utility>
using namespace std;
typedef long long num;
typedef pair<num,num> p2;

p2 shore[5005];
num pole[5005];
num n,l;
num best=0;
int main(){
  cin >> n >> l;
  for(int i=0;i<n;i++){
    num x,y;
    cin >> x >> y;
    shore[i]=p2(x,y);
    pole[i]=i? pole[i-1]+ (x-shore[i-1].first)*(y+shore[i-1].second) :0;
    if(!i)
      continue;
    num bx=shore[i].first-shore[i-1].first;
    num by=shore[i-1].second-shore[i].second;
    for(int j=i-1; j>=0 && shore[i].first-shore[j].first<=l;j--){
      x=shore[i].first-shore[j].first;
      y=shore[j].second-shore[i].second;
      
      if(bx*y > by*x || (x*x+y*y)>l*l){
      }else{
        best >?=  pole[i]-pole[j] - (shore[i].second+shore[j].second)*(shore[i].first-shore[j].first);
        bx=x;
        by=y;
      }
    }
  }
  cout << best/2 ;
  if(best&1)
    cout << ".5";
  cout << endl;  
  return 0;
}
