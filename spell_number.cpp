#include<iostream>
#include<cstring>
using namespace std;
int s[10]={1,1};
char a[100];
long long sum;
int small[20]={
  0,
  strlen("one"),
  strlen("two"),
  strlen("three"),
  strlen("four"),
  strlen("five"),
  strlen("six"),
  strlen("seven"),
  strlen("eight"),
  strlen("nine"),
  strlen("ten"),
  strlen("eleven"),
  strlen("twelve"),
  strlen("thirteen"),
  strlen("fourteen"),
  strlen("fifteen"),
  strlen("sixteen"),
  strlen("seventeen"),
  strlen("eighteen"),
  strlen("nineteen")
};
int big[10]={
  0,
  0,
  strlen("twenty"),
  strlen("thirty"),
  strlen("forty"),
  strlen("fifty"),
  strlen("sixty"),
  strlen("seventy"),
  strlen("eighty"),
  strlen("ninety")
};
int spell(int x){
  if(x==1000)
    return strlen("onethousand");
  if(x>=100)
    return spell(x/100)+strlen("hundred")+spell(x%100)+ (x%100?strlen("and"):0);
  if(x<20)
    return small[x];
  return big[x/10]+small[x%10];
}
int main(){
  for(int i=1;i<=1000;i++)
    sum+=spell(i);
  cout << "sum: " << sum << endl;
  system("PAUSE");
}
