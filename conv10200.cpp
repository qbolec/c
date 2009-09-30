#include <iostream.h>
int main()
{
int a;
  long int t=0;
cin >> a;
int inl=0;
while(!cin.eof())
{
  t+=a;
  cout << t << ",";
  inl++;
  if(inl==10)
  {
    cout << endl;
    inl=0;
  }
  cin >> a;

}


}
