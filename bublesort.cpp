#include<iostream>
#include<algorithm>
using namespace std;
const int n=3;
int t[n];
int main(){
  for(int i=0;i<n;++i)
    t[i]=i;

  do{
    int p[n];
    for(int i=0;i<n;i++)
      p[i]=t[i];
    for(int i=n-1;i>=0;--i)
      for(int j=i;j>=1;--j)
        if(p[j-1]>p[j])
          swap(p[j-1],p[j]);
//        else
//          break;
    bool bad=false;
    for(int i=0;i<n;i++)
      bad|= (p[i]!=i);
    if(bad){
      cout << "BAD " << endl;
      for(int i=0;i<n;i++)
        cout << t[i] << ' ';
      cout << endl;
      for(int i=0;i<n;i++)
        cout << p[i] << ' ';
      cout << endl;
      break;
    }
  }while(next_permutation(t,t+n));
  cout << "OK" << endl;
  cin >> t[0];
}
