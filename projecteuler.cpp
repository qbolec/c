#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=1000000;
char a[M+1];
char b[100];
int main(){
  for(int i=2;i<=M;i++){
    if(!a[i]){
      if(i<=M/i)
        for(int j=i*i;j<=M;j+=i)
          a[j]=true;
    }
  }
  int cnt=0;
  for(int i=2;i<=M;i++)
    if(!a[i]){
      sprintf(b,"%d",i);
      bool wrong=false;
      const int v=strlen(b);
      for(int j=v;j--;){
        int x;
        sscanf(b,"%d",&x);
        if(a[x]){
          wrong=true;
          break;
        }
        rotate(b,b+1,b+v);
      }
      if(!wrong){
        cout << i << endl;
        cnt++;
      }
    }
  cout << cnt << endl;
  system("PAUSE");
}
