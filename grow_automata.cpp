#include<cstdlib>
#include<cmath>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;
#define oncea(n) if(!(rand()%n))
#define IT(x) typeof(x.begin())
struct Node:pair<bool,map<unsigned char,int> >{
  int next(unsigned char x){
    return (--second.upper_bound(x))->second;
  }
  void deleteRandomEdge(){
    int c=rand()%256;

    IT(second) it=--second.upper_bound(c);
    if(it==second.begin())++it;
    second.erase(it);
  }
  Node(int to=0){
    first=false;
    second[0]=to;
  }
};
struct Automata:vector<Node>{
  bool accept(const char * word,int state=0){
    if(!*word)return operator[](state).first;;
    return accept(word+1 ,operator[](state).next((unsigned char)*word) );
  }
  Automata():vector<Node>(1){}
  void addRandomState(){
    int s=rand()%size();
    int c=rand()%255;
    int t=rand()%(size()+1);
    operator[](s).second[c]=size();
    push_back(Node(t));
  }
  void addRandomEdge(){
    int s=rand()%size();
    int c=rand()%256;
    int t=rand()%size();
    operator[](s).second[c]=t;    
  }
  void deleteRandomEdge(){
    int s=rand()%size();
    int n=operator[](s).second.size();
    if(n>1){
      operator[](s).deleteRandomEdge();
    }
  }
  
  void swapRandomAccept(){
    int s=rand()%size();
    operator[](s).first^=1;
  }
  void swapRandomStates(){
    int s=rand()%size();
    int t=rand()%size();
    ::swap(operator[](s),operator[](t));
  }

  Automata copyRandom(){
    Automata mutant=*this;
    oncea(5)mutant.addRandomState();
    oncea(2)mutant.addRandomEdge();
    oncea(4)mutant.swapRandomAccept();
    oncea(10)mutant.swapRandomStates();
    oncea(3)mutant.deleteRandomEdge();
    return mutant;
  }
  int check(vector<string> &good,vector<string> &bad){
    int cnt=0;
    for(int i=good.size();i--;)
      if(accept(good[i].c_str()))cnt++;
    for(int i=bad.size();i--;)
      if(accept(bad[i].c_str()))cnt--;
    return cnt;
  }
  void present(){
    cout << "states:" << size() << endl;
    for(int i=0;i<size();i++){
      cout << i << " : " << (operator[](i).first?"GREEN":"RED")  <<endl;
      for(map<unsigned char,int>::iterator it=operator[](i).second.begin();it!=operator[](i).second.end();++it){
        cout << "For letter " << it->first << "(" << (int)it->first << ") ->" << it->second << endl;
      }
    }
  }
};
struct AutomataPlant:vector<Automata>{
  AutomataPlant():vector<Automata>(1){
  }
  void learn(vector<string> &good,vector<string> &bad){
    int iterations=0;
    while(++iterations){
      vector<pair<int,int> > r;
      for(int i=size();i--;)
        r.push_back(make_pair(operator[](i).check(good,bad),i));
      sort(r.begin(),r.end()); 
      if(r.back().first==good.size()){
        cout << "Best automata is:" << endl;
        operator[](r.back().second).present();
        
        break;
      }
      int g=   (size()*(size()+1)/2);
      for(int t=5;t--;){
        int b=r.size()-1-floor(sqrt(rand()%g));      
        push_back(operator[](r[b].second).copyRandom());
      }
      r.clear();
      for(int i=size();i--;)
        r.push_back(make_pair(operator[](i).check(good,bad),i));
      sort(r.begin(),r.end());    
      if(r.size()>1000){
        vector<int> ids;
        for(int i=0;i<r.size()-1000;i++)
          ids.push_back(r[i].second);
        sort(ids.begin(),ids.end());
        for(int i=ids.size();i--;)
          erase(begin()+ids[i]);
      }
    }
    cout << "Learned in :" << iterations << " steps:)" << endl;

  }
};

int main(){
  cout << "Type +/- word, to teach the system that the word should/shouldn't be in the language" << endl;
  vector<string> good;
  vector<string> bad;
  AutomataPlant ap;
  while(1){
    string s;
    char c;
    cin >> c >> s;
    switch(c){
    case '+':
      good.push_back(s);
      break;
    case '-':
      bad.push_back(s);
      break;
    default:
      cout << "You must specify + or - in front of the word. Word may not contain white characters." << endl;
      continue;    
    }
    ap.learn(good,bad);
  }
  return 0;
}
