#include<cstdio>
#include<cstdlib>
char t[]={ 13,11,21,19,15,6,4,10,23,9,18,16,14,22,1,5,8,12,24,2,17,25,3,7,20,0};

int main(){
  for(char *s=t;*s;s++)*s= 'a'+*s;
  puts(t);
  system("pause");
}
