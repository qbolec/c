#include<cstdio>
#include<string>
using namespace std;
int main(){
  string w="";
  for(int i=0;i<10000000;i++)
    w+=i;
  printf("%d\n",w.length());
  scanf("%d");
}
