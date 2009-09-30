#include<cstdio>
using namespace std;
const int LOG=10;
int L[LOG]={1<<LOG};
int main(){
	int t=0;
  while(L[LOG-1]!= 1<<LOG ){
  	t++;
    for(int i=LOG;--i;){
      L[i]=(L[i]+L[i-1]+1)/2;
    }
  }
  printf("%d\n",t);
}
