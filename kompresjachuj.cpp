#include<cstdio>
using namespace std;
char text[2][256];
int len[2];
int cur;
int cnt;
int main(){
  int n;
  scanf("%d ",&n);  
  while(n--){    
    scanf("%s%n ",text[cur],len+cur);
    int j=len[0]<?len[1];
    cnt+=len[cur]+1;
    for(int i=0;i<j && text[0][i]==text[1][i];i++)cnt--;
    cur=1-cur;
  }
  printf("%d\n",cnt-1);
  return 0;
}
