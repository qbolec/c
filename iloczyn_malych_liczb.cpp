#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int d[100001]={0,1};
int f[100001]={0,1};
int main(){
  priority_queue<int, vector<int> , greater<int> >  q;
  for(int i=2;i<100001;i++)
    if(!d[i])
      for(int j=i;j<100001;j+=i)
        d[j]=i;
  for(int i=2;i<100001;i++){
    int x=d[i];
    int t=x-1;
    int j=i/x;
    while(d[j]==x){
      j=j/x;
      t*=x;
    }
    f[i]=t*f[j];
    if(i<20)
    cout << "fi[" << i << "]=" << f[i] << endl;
  }
  int t;
  cin >> t;
  while(t--){
    int n;
    cin >> n;
    long long w= 2LL*n*n;
    for(int i=1;i<=n;i++){
      const int g=n/i;
      w-= (long long)f[i]* g*(g-1)/2;
    }
  }
}
