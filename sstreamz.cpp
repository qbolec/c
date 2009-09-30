#include<iostream>
#include<sstream>
#include<cstdlib>
using namespace std;
#define lockedlog(x) {stringstream tmpbuff;tmpbuff << x;cout << tmpbuff.str();}
int main(){
  lockedlog(0.12 << "aaa" << 1 << endl);
  system("PAUSE");
}
