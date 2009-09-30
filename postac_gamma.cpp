#include<iostream>
#include<cstdlib>
using namespace std;
int main(){
  for(int r=0;r<4;r++){
    for(int c=0;c<4;c++){
      cout << "$";
      cout << "\\gamma " ;
      if(r<=c){
        cout << "\\lambda ^ " << r ;
      }else{
        cout << "(\\lambda ^ " << r << " - \\lambda ^ " << r-c-1 << " )";
      }
      cout << "$ &";
    }
    cout << "$\\lambda ^ " << r << "$ &  $0$ \\\\" << endl;
  }
  system("PAUSE");
}
