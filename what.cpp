#include<iostream>
#include<iterator>
using namespace std;
int P,i,x,A[10];
int main()
{
  cin >> P;
  for(i=0;i<P;i++)
    cin >> A[i];
  sort(A,A+P);
  do{
    for(int i=0;i<P-1;++i)
      cout<<P[i]<<'.';
    cout<<A[P-1]<<endl;
  } while(next_permutation(A,A+P)&&(++x<10000));
}
