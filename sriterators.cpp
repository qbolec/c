#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <numeric>
using namespace std;

int main(int argc, char* argv[])
{
   string str = "+hello+world++this+is+fun+";
   string out;

   remove_copy_if(str.begin(), str.end(), back_inserter(out),
                  bind1st(equal_to<char>(), '+'));
  vector<int> dupa(10);
  generate(dupa.begin(),dupa.end(),rand);
  copy(dupa.begin(),dupa.end(),ostream_iterator<int>(cout," "));
  partial_sum(dupa.begin(),dupa.end(),dupa.begin());
  cout << endl;
  copy(dupa.begin(),dupa.end(),ostream_iterator<int>(cout," "));
  dupa.erase(remove_if(dupa.begin(),dupa.end(),bind1st(greater<int>() ,1000 )),dupa.end());
  cout << endl;
  copy(dupa.begin(),dupa.end(),ostream_iterator<int>(cout," "));

//  copy(istream_iterator<int>(cin),,back_inserter(dupa));
  cin >> out;
   return 0;
}
