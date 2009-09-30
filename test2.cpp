#include<string>
#include<sstream>
#include<vector>
#include<iostream>
using namespace std;
int main(){
  string s="34 234 234 235 ";
  vector<int> vs;
  istringstream ss(s);
  for(int x;ss>>x;vs.push_back(x));
  
  for(int i=vs.size();i--;)
    cout << vs[i] << endl;
}
