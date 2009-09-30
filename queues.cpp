#include<deque>
#include<set>
#include<iostream>
#include<iterator>
using namespace std;
  int k[2];
  int p[2];
int main(){
  deque<int> a[2];
  set<int>as[2];
  cout << "Podaj k1 < k2 :" << endl;
  cin >> k[0] >> k[1];
  while(1){
    int x;
    cin >> x;
    for(int i=0;i<2;i++){
    if( as[i].find(x)==as[i].end()){
      p[i]++;

      if(as[i].size()==k[i]){
        cout << "Kolejka " << i << " musi zapomniec o:" << a[i].front() << endl;
        as[i].erase(a[i].front());
        a[i].pop_front();
      }
      a[i].push_back(x);
      as[i].insert(x);
    }
    cout << "Koszt calkowity kolejki " << i << " wynosi:" << p[i] << endl;
    cout << "Zawartosc kolejki " << i << ":" ;
    copy(a[i].begin(),a[i].end(),ostream_iterator<int>(cout," "));
    cout << endl;
  }
  }
}
