#include<string>
#include<iostream>
#include<vector>
using namespace std;
int main(){
  int S;
  string A,B;
  cin >> S >> A >> B;
  vector<int> najblizsze_takie_samo;
  najblizsze_takie_samo.resize(B.length());
  int najblizsze[256];
  for(int x=0;x<S;x++)
    najblizsze['a'+x]=B.length();
  vector<int> biezace(B.length()+2,1<<30);
  biezace[B.length()]=1;
  biezace[B.length()+1]=0;
  for(int i=B.length();i--;){    
    najblizsze_takie_samo[i]=najblizsze[B[i]];
    najblizsze[B[i]]=i;
    for(int x=0;x<S;x++)
      biezace[i]<?=1+biezace[najblizsze['a'+x]+1];    
  } 
  vector<int> dla_literki[256];
  for(int x=0;x<S;x++)
    dla_literki['a'+x]=biezace;
  for(int a=A.length();a--;){
    biezace.back()=biezace[B.length()];
    dla_literki[A[a]]=biezace;
    biezace[0]=1<<30;
    for(int x=0;x<S;x++)
      biezace[0]<?= dla_literki['a'+x][ najblizsze['a'+x] + 1] +1;
    for(int b=1;b<=B.length();b++)
      biezace[b]=  biezace[b-1] <? dla_literki[ B[b-1] ][ najblizsze_takie_samo[b-1] +1] +1;            
  }  
  cout<<biezace[0]<<endl;
  system("pause");
}
/*
2
ababab
bbaaaa
*/
