#include<iostream>
#include<vector>
#include<fstream>
//#include"C:\\prg\\lpsolve\\lp_lib.h"
using namespace std;
/*
Mamy n przedmiotow, ostatni o wadze 1, pozostale sa zmiennymi
Genereujemy sobie drzewo gry
*/
int n;
typedef unsigned int mask;
void make_indent(int p){
  while(p-->0)
    cout << ' ';
}
struct game_node{
  vector<game_node*> children;
  mask available;//bitmask
  mask taken;//bitmask
  game_node * parent;
  void remove_singletons(){
    for(int i=children.size();i--;){
      children[i]->remove_singletons();
      if(children[i]->children.size()==1)
        children[i]=children[i]->children[0];
    }
  }
  virtual void sanity()=0;
  virtual char kind()=0;
  virtual void desc(int indent=0)=0;
  virtual long long options()=0;
  virtual int select(int option,double alpha,ostream & o)=0;
  game_node(mask a,mask t,game_node * p):available(a),taken(t),parent(p){}
};
struct end_node:game_node{
  vector<mask> possible;
  virtual char kind(){return 'E';}
  virtual void sanity(){}
/*
  bool tie(){
    return possible.size()==1 && possible[0]==taken;
  }
*/
  virtual int select(int option,double alpha,ostream & o){
    assert(option<possible.size());
    o << "0>=";
    for(int i=0;i<32;i++){
      if(possible[option]&(1<<i)){
        o << '-'<< alpha <<'n' << i;
      }
      if(taken&(1<<i)){
        o << "+n" << i ;
      }
    }
    o <<';'<< endl;
    return 0;
  }
  end_node(mask a,mask t,game_node * p):game_node(a,t,p){
    vector<mask> history;
    int all=(1<<n)-1;
    int always=available;
    int could= all^always;
    if(could){
      for(game_node * t=parent->parent;t;t=t->parent){
        history.push_back(t->available);
        t=t->parent;
        if(!t)break;
      }
      for(int v=could;v>0;v--)if((taken&(v|always))!=(v|always)){
        mask w=v;
        for(int i=possible.size();i--;)
          if((possible[i]&v)==v)
            goto skipv;
        for(int i=history.size();i--;)
          if(history[i]&w)
            w&=(w-1);
        if(!w){
          possible.push_back(v|always);
        }
        skipv:continue;
      }
    }else{
      if((taken&all)!=taken)
        possible.push_back(all);
    }
  }
  virtual long long options(){
    return possible.size();
  }
  virtual void desc(int indent=0){
    make_indent(indent);
    cout << "E[] (";//<<endl ;
    for(int i=0;i<32;i++)
      if(available&taken& (1<<i) )
        cout << i << ',';
    cout << ')' ;
    for(int j=possible.size();j--;){
      const int v=possible[j];
      cout << '<';
      for(int i=0;i<32;i++)
        if(v&(1<<i))
           cout << i << ',';
      cout << '>';
    }
    cout << '{';
    for(int i=0;i<32;i++)
      if(taken& (1<<i) )
        cout << i << ',';
    cout << '}';
    cout << endl;
  }
};
bool leq(mask a ,mask b){
  return (b&a)==a;
}
bool containsgeq(mask a,vector<mask> & bs){
  for(int i=bs.size();i--;)
    if(leq(a,bs[i]))
      return true;
  return false;
}
bool leq(end_node * a, end_node * b , bool true_on_equal){
  if(!leq(a->taken,b->taken))
    return false;
  for(int i=b->possible.size();i--;)
    if(!containsgeq(b->possible[i],a->possible))
      return false;
  return true_on_equal || a->taken!=b->taken || a->possible!=b->possible;
}
/*
bool tie(game_node * t){
  if(t->kind()=='E'){
    end_node * e =(end_node *)t;
    return e->tie();
  }
  return false;
}
*/
struct adversary_node:game_node{
  adversary_node(mask a,mask t,game_node * p);

  virtual char kind(){return 'A';}
  virtual void sanity(){
    for(int i=children.size();i--;)
      children[i]->sanity();
    vector<bool> dead(children.size(),false);
/*
    int killed=0;
    for(int i=children.size();i--;)if(tie(children[i])){
      cout << "adversary shouldn't tie using:" << endl;
      children[i]->desc();
      dead[i]=true;
      killed++;
    }
    if(killed==children.size()){
      dead[0]=false;
      killed--;
    }
*/
    for(int i=children.size();i--;)if(!dead[i] && children[i]->kind()=='E'){
      end_node * e= (end_node*)children[i];
      for(int j=children.size();j--;)if(i!=j && !dead[j] && children[j]->kind()=='E'){
         end_node * f = (end_node*)children[j];
         if(leq(f,e,j<i)){
            dead[i]=true;
            cout << "killed adversary child:" << endl;
            e->desc();
            cout << "by:" << endl;
            f->desc();
            break;
         }
      }
    }
    int i2=0;
    for(size_t i=0;i<children.size();i++)
      if(!dead[i])
        children[i2++]=children[i];
    children.resize(i2);
  }
  virtual long long options(){
    long long x=0;
    for(size_t i=0;i<children.size();i++)
      x+=children[i]->options();
    return x;
  }
  virtual int select(int option,double alpha,ostream & o){
    long long x=0;
    long long y=0;

    for(size_t i=0;i<children.size();i++){
      x+=children[i]->options();
      if(option>=y && option<x){
        return children[i]->select(option-y,alpha,o);
      }
      y=x;
    }
    assert(false);
  }

  virtual void desc(int indent=0){
    make_indent(indent);
    cout << "A[";
    for(int i=0;i<32;i++)
      if((available&~taken)&(1<<i))
        cout << i << ',';
    cout << "](";//<<endl ;
    for(int i=0;i<32;i++)
      if(available&taken& (1<<i) )
        cout << i << ',';
    cout << ')' << endl;
    for(size_t i=0;i<children.size();i++)
      children[i]->desc(indent+1);
  }
};

struct algorithm_node:game_node{
  virtual char kind(){return 'U';}
  virtual void sanity(){
    for(int i=children.size();i--;)
      children[i]->sanity();

    vector<bool> dead(children.size(),false);
/*
    for(int i=children.size();i--;)if(tie(children[i])){
      cout << "algo can tie with move:" << endl;
      children[i]->desc();
      swap(children[i],children[0]);
      children.resize(1);
      return;
    }
*/
    for(int i=children.size();i--;)if(children[i]->kind()=='E'){
      end_node * e= (end_node*)children[i];
      for(int j=children.size();j--;)if(i!=j && !dead[j] && children[j]->kind()=='E'){
         end_node * f = (end_node*)children[j];
         if(leq(e,f,j<i)){
            dead[i]=true;
            cout << "killed user (algo) child:" << endl;
            e->desc();
            cout << "by:" << endl;
            f->desc();
            break;
         }
      }
    }
    int i2=0;
    for(size_t i=0;i<children.size();i++)
      if(!dead[i])
        children[i2++]=children[i];
    children.resize(i2);
  }
  algorithm_node(mask a,mask t,game_node * p):game_node(a,t,p){
    for(int i=0;i<32;i++)
      if((a&~t)&(1<<i))
        if(a&~(t^(1<<i)))
          children.push_back(new adversary_node(a,t^(1<<i),this));
        else
          children.push_back(new end_node(a,t^(1<<i),this));
  }
  virtual long long options(){
    long long x=1;
    for(size_t i=0;i<children.size();i++)
      x*=children[i]->options();
    return x;
  }
  virtual int select(int option,double alpha,ostream & o){
    for(size_t i=0;i<children.size();i++){
      long long x=children[i]->options();
      children[i]->select(option%x,alpha,o);
      option/=x;
    }
    return 0;
  }

  virtual void desc(int indent=0){
    make_indent(indent);
    cout << "U[";
    for(int i=0;i<32;i++)
      if((available&~taken)&(1<<i))
        cout << i << ',';
    cout << "](";//<<endl ;
    for(int i=0;i<32;i++)
      if(available&taken& (1<<i) )
        cout << i << ',';
    cout << ')' << endl;
    for(size_t i=0;i<children.size();i++)
      children[i]->desc(indent+1);
  }
};
//#define DELETE_ALWAYS_SOMETHING
adversary_node::  adversary_node(mask a,mask t,game_node * p):game_node(a,t,p){
    int last=0;
    for(;;){
#ifdef DELETE_ALWAYS_SOMETHING
      a&=a-1;
#endif
      if(a&~t){
        if((a&~t)!=last){
          children.push_back(new algorithm_node(a,t,this));
          last=(a&~t);
        }
      }else{
        children.push_back(new end_node(a,t,this));
        break;
      }
      if(!a)
        break;
#ifndef DELETE_ALWAYS_SOMETHING
      a&=a-1;
#endif
    }
  }

algorithm_node * root;
void select_option(int option,double alpha,ostream & o){
  o << "min: z;" << endl;
  for(int i=0;i<n;i++)
    o << 'n' << i << " >=1;" << endl;
  root->select(option,1.0/alpha,o);
}
bool check_option(int option,double alpha){
    ofstream p("tmp.lp");
    select_option(option,alpha,p);
    p.close();
    system("c:\\prg\\lpsolve\\lp_solve tmp.lp > res.txt");
    ifstream r("res.txt");
    char c;
    r >> c;
    r.close();
    if(c=='T'){
      return false;
    }else if(c=='V'){
      return true;
    }else{
      puts("Shit...");
      system("PAUSE");
      return false;
    }
}
double bs(int option,double f, double t){
  if(!check_option(option,f)){
    cout << "Option " << option << " doesn't even give alpha=" << f << endl;
    return f;
  }
  while(f+0.0001<t){
    double a=(f+t)/2;
    if(check_option(option,a)){
      cout << "Option " << option << " with alpha=" << a << " succeded." << endl;
      f=a;
    }else{
      cout << "Option " << option << " with alpha=" << a << " failed." << endl;
      t=a;
    }
  }
  cout << "Option " << option << " gives alpha=" << f << endl;
  return f;
}
int main(){
  cout << "Number of items:" << endl;
  cin >> n;
  root= new algorithm_node((1<<n)-1,0,0);
  
  for(int c=3;c;){
    root->desc();
    root->remove_singletons();
    long long ops=root->options();
    cout<< "options: " << ops << endl;
    root->sanity();
    long long ops2=root->options();
    puts("---");
    if(ops2==ops)
      c--;
  }
  system("PAUSE");
  long long ops=root->options();
  double f=1.5;
  int best_option=0;
  for(int i=0;i<ops;i++){
    double f2=bs(i,f,2.0);
    if(f2>f){
      f=f2;
      best_option=i;
    }
    cout << "Best option so far " << best_option << " gave " << f << endl;
  }
  system("PAUSE");
  return 0;
}
