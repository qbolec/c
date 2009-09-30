#include<cstdio>
#include<iostream>
using namespace std;
int main(){
  char text[1024];
  
  long double dupa=9E300;
  cout << dupa << endl;

  
  scanf("%s",text);
  
  
  sscanf(text,"%LE",&dupa);
 
  printf("wpisales liczbe: %LE\n",dupa); 
  return 0;
}
