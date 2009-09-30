#include<iostream>
using namespace std;
int k,x,m;
long long n;
int ile[2][1001][1001];//level total last
int sum[1001];
int pas[1001];
int main(){
  cin >> n >> m >> k >> x;
  int prev=0;
  int curr=1;
  for(long long range=1;;range*=x){
    const long long field= ((range>n)?n:range)-range/x;
    for(int last=0;last<=k;last++){
      //pas[j] =  choose(regeneracja-j, last)
      pas[0]=1;
      for(int i=0;i<last;i++)
        pas[0]=pas[0]*(field-i)/(i+1);
      for(int j=1;j<=k-last;j++)
        pas[j]=pas[j-1]?pas[j-1]*(field-j-(last-1))/(field-(j-1)):0;
      for(int total=0;total<last;total++)
        ile[curr][total][last]=0;
      for(int total=last;total<=k;total++){
        ile[curr][total][last]=0;
        for(int j=0;j<=total-last;j++)
          ile[curr][total][last]+=ile[prev][total-last][j]*pas[j];
      }
    }
    curr=prev;
    prev=1-curr;
    if(range>=n)break;
  }
  int wynik=0;
  for(int last=0;last<=k;last++)
    wynik+=ile[prev][k][last];
  cout << wynik << endl;
}
