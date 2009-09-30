#include<iostream>
#include<time.h>
using namespace std;
int s[10]={1,1};
char a[100];
long long sum;
int dm[13]={0,31,0,31,30,31,30,31,31,30,31,30,31};
int daysof(int y,int m){
  return m!=2? dm[m]  : y&3? 28: y%100? 29 : y%400 ? 28:29;
}
enum {
  monday=1,
  sunday=7
};
int main(){
  int w=monday;
  for(int y=1900;y<=2000;y++){
    for(int m=1;m<=12;m++){
      for(int d=1;d<=daysof(y,m);d++){
        if(w==sunday && d==1 && y>=1901 && y<=2000)
          sum++;
        if(w==sunday)
          w=monday;
        else
          w++;
      }
    }
  }
  cout << "sum: " << sum << endl;
  system("PAUSE");
}
