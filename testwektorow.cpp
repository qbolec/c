#include<cstdio>
#include<vector>
using namespace std;
int main(){
  vector<int> a,b,c;
  a.push_back(1); a.push_back(2);
  b.push_back(1);
  c.push_back(2);
  printf("a<b %d\n",(int)(a<b));
  printf("b<a %d\n",(int)(b<a));
  printf("a<c %d\n",(int)(a<c));
  printf("c<a %d\n",(int)(c<a));
  scanf("%d");

}
