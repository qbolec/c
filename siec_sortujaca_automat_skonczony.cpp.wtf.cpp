/*
Automat  ma 161 warstw oraz 12834318 stanow i moc 6.02703e+033 =*0.854102
24      135 (75) 75/80
*/
#include<cassert>
#include<queue>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cstdlib>
#include<map>
using namespace std;
struct A{
  vector<vector<int> > levels;
  vector<short int> level;
  vector<int> delta[2];
  int width()const{
    return (int)levels.size();
  }
  int size()const{
    return (int)level.size();
  }
  double cardinality(){
    vector<double> c(size(),0);
    assert(levels.back().size()==1);
    c[levels.back()[0]]=1.0;

    for(int l=width()-2;0<=l;--l){
      for(int i=0;i<levels[l].size();++i){
        const int v=levels[l][i];
        assert(c[v]==0.0);
        for(int x=0;x<2;++x){
          if(0<=delta[x][v]){
            c[v]+=c[delta[x][v]];
          }
        }
      }
    }
    assert(levels[0].size()==1);
    return c[levels[0][0]];
  }
  void dump(const char * x = "", int f=0){
    static double last_c = 1.0;
    double c= cardinality();
    cout << "Automat " << x << " ma " << width() << " warstw oraz " << size() << " stanow i moc " << c << " =*" << c/last_c << endl;
    last_c = c;
    if(size()<26 || 0<f){
      for(int l=f;l<width();++l){
        for(int j=0;j<levels[l].size();++j){
          const int i=levels[l][j];
          cout << i << " (" << level[i] << ") -> [ " << delta[0][i] << " , " << delta[1][i] << "]" << endl;
        }
      }
    }
  }
};
typedef pair<int,int> C;
typedef vector<C> L;
typedef vector<L> S;
typedef unsigned long long int lint;
C K(int a,int b){
  return C(std::min(a,b),std::max(a,b));
}
int remap(int x,L map){
  for(size_t i=0;i<map.size();i++){
    if(map[i].first==x){
      return map[i].second;
    }
  }
  throw "brak wpisu";
}
L remap(L s,L map){
  L n;
  for(size_t i=0;i<s.size();i++){
    int a=s[i].first;
    int b=s[i].second;
    int an=remap(a,map);
    int bn=remap(b,map);
    n.push_back(K(an,bn));
  }
  return n;
}
L join(L a,L b){
  for(size_t i=0;i<b.size();i++){
    a.push_back(b[i]);
  }
  return a;
}
S join(S a,S b){  
  for(size_t i=0;i<a.size();i++){
    a[i]=join(a[i],b[i]);
  }
  return a;
}
S remap(S a,L map){
  for(size_t i=0;i<a.size();i++){
    a[i]=remap(a[i],map);
  }
  return a;
}
S deep_rainbow(unsigned int n){
  if(n==1)return S();
  S m=deep_rainbow(n/2);
  L r;
  for(int i=0;i<n/2;++i){
    r.push_back(K(i,i+n/2));
  }
  S u=remap(m,r);
  S all=join(m,u);
  L b;
  for(int i=0;i<n/2;i++){
    b.push_back(K(i,n-1-i));
  }
  all.push_back(b);
  return all;  
}
L rainbow(unsigned int k){
  if(!k)return L();
  L m=rainbow(k-1);
  L r;
  int f=0;
  for(int i=0;i<(1<<(k-1));i++){
    for(size_t j=0;j<(k-1);j++){
      r.push_back(K(i*(k-1)+j, f++));
    }
    f++;
  }
  L u=remap(m,r);
  L s;
  for(int i=0;i<f;i++){
    s.push_back(K(i,2*f-1-i));
  }
  L d=remap(u,s);
  L b;
  for(int i=0;i<(1<<(k-1));i++){
    b.push_back(K(f+i*k,f-1-i*k));
  }
  return join(b,join(u,d));
}
S whole_rainbow(int k){
  S s(4,L());

  for(int j=0;j<2;j++){
    for(int i=j+1;i<k*(1<<k);i+=2){
      s[j*2].push_back(K(i-1,i));
    }
  }
  s[1]=s[3]=rainbow(k);
  for(int j=0;j<s.size();++j){
    sort(s[j].begin(),s[j].end());
  }
  return s;
}
S three_rainbow(int k){
  S s(3,L());

  for(int j=0;j<2;j++){
    for(int i=j+1;i<k*(1<<k);i+=2){
      s[j].push_back(K(i-1,i));
    }
  }
  s[2]=rainbow(k);
  for(int j=0;j<s.size();++j){
    sort(s[j].begin(),s[j].end());
  }
  return s;
}

const int V=4;
const int N=(V*(1<<V));
A all_words(int l){
  A a;
  a.level.resize(l+1,0);
  for(int x=0;x<2;++x){
    a.delta[x].resize(l+1,-1);
  }
  for(int f=0;f<=l;++f){
    a.levels.push_back(vector<int>());
    a.levels[f].push_back(f);
    a.level[f]=f;
    if(f<l){
      for(int x=0;x<2;++x){
        a.delta[x][f]=f+1;
      }
    }else{
      for(int x=0;x<2;++x){
        a.delta[x][f]=-1;
      }
    }
  }
  return a;
}

A alternative(A &a,A &b){
  const int w=a.width();
  assert(w==(int)b.levels.size());
  map<pair<int,int>, int >  pairing;
  A z;
  z.levels.resize(w);
  
  queue<pair<int,pair<int,int> > > s;
  int f=0;
  z.levels[0].push_back(f);
  z.level.push_back(0);
  for(int i=0;i<2;++i){
    z.delta[i].push_back(-1);
  }
  s.push(make_pair(f,make_pair(0,0)));
  ++f;
  int last_level=-1;
  while(!s.empty()){
    const int g=s.front().first;
    const int l=z.level[g];
    if(l!=last_level){
      last_level=l;
      if(last_level){
        cout << pairing.size() << endl;
        pairing.clear();
        swap(a.levels[last_level-1],vector<int>());
        swap(b.levels[last_level-1],vector<int>());        
      }
    }
    //cout << "Visiting " << g << endl;
    const pair<int,int> p = s.front().second;
    //cout << "That is " << p.first << " + " << p.second << endl;
    const int ia=p.first;
    const int ib=p.second;
    s.pop();
    for(int d=0;d<2;++d){
      const int ja=( (0<=ia) ? (a.delta[d][ia]) : (-1) );
      const int jb=( (0<=ib) ? (b.delta[d][ib]) : (-1) );
      if((ja<0) && (jb<0)){
        assert(z.delta[d][g] == -1);
      }else{
        pair<int,int> p2(ja,jb);
        if(pairing.find(p2)==pairing.end()){
          pairing[p2] = f;
          z.level.push_back(z.level[g]+1);
          z.levels[z.level[f]].push_back(f);
          for(int i=0;i<2;++i){
            z.delta[i].push_back(-1);
          }
          s.push(make_pair(f,p2));
          ++f;
        }
        z.delta[d][g] = pairing[p2];
      }
    }
  }
  
  assert(f == z.level.size());
  assert(z.delta[0].size() == z.delta[1].size() && z.delta[0].size()==z.level.size());
  return z;
}

A force(A a,const int p,const int d){
  assert(0<=p && p<a.width());
  assert(0<=d && d<=1);
  A r=a;
  for(int i=0;i<(int)r.levels[p].size();++i){
    const int v=r.levels[p][i];
    r.delta[1-d][v]=-1;
  }
  return r;
}
A flip(A a,const int p){
  assert(0<=p && p<a.width());
  A r=a;
  for(int i=0;i<(int)r.levels[p].size();++i){
    const int v=r.levels[p][i];
    swap(r.delta[0][v],r.delta[1][v]);
  }
  return r;
}
A cleanup(const A &a){
  assert(a.size()>0);
  assert(a.width()>0);

  vector<bool> endable(a.size(),false);

  for(int i=0;i<(int)a.levels.back().size();++i){
    endable[a.levels.back()[i]]=true;
  }
  for(int i=(int)a.levels.size()-1;0<=i;--i){
    for(size_t j=0;j<a.levels[i].size();++j){
      const int v=a.levels[i][j];
      for(int d=0;d<2;++d){
        if(0<=a.delta[d][v] && endable[a.delta[d][v]]){
          endable[v] = true;
          break;
        }
      }
    }
  }


  vector<int> alias(a.size(),-1);
  vector<int> s;
  s.push_back(0);
  alias[0]=0;
  int f=1;
  while(!s.empty()){
    const int v=s.back();
    s.pop_back();
    for(int i=0;i<2;++i){
      const int u=a.delta[i][v];
      if(0<=u && endable[u]){
        if(alias[u]<0){
          alias[u]=f++;
          s.push_back(u);
        }
      }
    }
  }
  A r=a;
  r.level.resize(f);
  for(int i=0;i<2;++i){
    r.delta[i].resize(f);
  }
  for(int i=0;i<r.width();++i){
    int k=0;
    for(int j=0;j<(int)r.levels[i].size();++j){
      const int v=r.levels[i][j];
      const int u=alias[v];
      if(0<=u){
        r.levels[i][k++]=u;
        r.level[u]=i;
      }
    }
    r.levels[i].resize(k);
  }

  for(int v=0;v<a.size();++v){
    const int u=alias[v];
    if(0<=u){
      for(int i=0;i<2;++i){
        r.delta[i][u]=( (0<=a.delta[i][v]) ? (alias[a.delta[i][v]]) : (-1) );
      }
    }
  }
  return r;
}
A minimize(const A &a){
  assert(0<a.size());
  assert(0<a.width());
  assert(a.levels[0].size()==1);
  //map<int,int> renaming;
  vector<int> renaming(a.size(),-1);

  A r;
  r.levels.resize(a.width());
  r.level.push_back(0);
  r.levels[0].push_back(0);
  r.delta[0].push_back(-1);//tmp
  r.delta[1].push_back(-1);//tmp


  int f=0;
  for(int i=a.width()-1;0<i;--i){
    vector<pair<pair<int,int>, int> > taken;
    for(int j=0;j<(int)a.levels[i].size();++j){
      const int v=a.levels[i][j];
      int x[2];
      for(int d=0;d<2;++d){
        x[d]= 0<=a.delta[d][v]? renaming[a.delta[d][v]] : -1;
      }
      taken.push_back(make_pair(make_pair(x[0],x[1]),v));
    }
    //renaming.clear();
    sort(taken.begin(),taken.end());
    pair<int,int> last_taken(-2,-2);
    for(int j=0;j<taken.size();++j){
      if(taken[j].first!=last_taken){
        ++f;
        last_taken=taken[j].first;
        r.levels[i].push_back(f);
        r.level.push_back(i);
        int x[2]={last_taken.first,last_taken.second};
        for(int d=0;d<2;++d){
          r.delta[d].push_back(x[d]);
        }        
      }
      renaming[taken[j].second]=f;
    }      
  }
  for(int d=0;d<2;++d){
    r.delta[d][0]= 0<=a.delta[d][0]? renaming[a.delta[d][0]] : -1;
  }
  return r;
}
A compare(int x,int y,const A & a){
  assert(x<y);
  
  return minimize((alternative(
    minimize(cleanup(force(force(a,x,1),y,1))),
    minimize((alternative(
      flip(flip(minimize(cleanup(force(force(a,x,1),y,0))),x),y),
      minimize(cleanup(force(a,x,0)))
    )))
  )));
//  return minimize(alternative(c,minimize(alternative(b,d))));
}
bool sorted(const A &a){
  if(a.size()!=a.width()*2-2){
    cout << "zla ilosc stanow" << endl;
    return false;
  }
  if(a.levels[0].size()!=1 || a.levels.back().size()!=1){
    cout << "zle konce" << endl;
    return false;
  }
  for(int i=1;i<a.levels.size()-1;++i){
    if(a.levels[i].size()!=2){
      cout << "zla wielkosc warstwy " << i << " jest " << a.levels[i].size() << endl;
      return false;
    }
  }
  if(a.delta[0][0]<0 || a.delta[1][0]<0){
    cout << "zly start" << endl;
    return false;
  }
  int x=a.delta[0][0];
  int y=a.delta[1][0];
  for(int i=1;i<a.levels.size()-1;++i){
    if(a.level[x]!=i){
      cout << "zly poziom x" << endl;
      return false;
    }
    if(a.level[y]!=i){
      cout << "zly poziom y" << endl;
      return false;
    }
    if(0<=a.delta[0][y]){
      cout << "da sie zerem" << endl;
      return false;
    }
    if(a.delta[1][y]<0){
      cout << "nie da sie jedynka" << endl;
      return false;
    }
    y=a.delta[1][y];
    if(a.delta[0][x]<0){
      cout << "z zera zerem sie nie da" << endl;
      return false;
    }
    if(a.delta[1][x]!=y){
      cout << "z zera jedynka idzie sie nie do y" << endl;
      return false;

    }
    x=a.delta[0][x];
  }
  return true;
}
void interactive(){
  int n;
  cout << "Ile bitów?" << endl;
  cin >> n;
  A a=all_words(n);  
  while(1){
    a.dump();
    int x,y;
    cin >> x >> y;
    if(x<0 || y<0 || n<=x || n<=y || y<=x){
      exit(-1);
    }
    a=compare(x,y,a);
  }
}
S odd_even(int n){
  S r;
  for(int i=0;i<2;++i){
    L w;
    for(int j=i;j+1<n;j+=2){
      w.push_back(K(j,j+1));
    }
    r.push_back(w);
  }
  return r;
}
void dump(S r){
  for(size_t l=0;l<r.size();l++){
    cout << "Layer " << (unsigned int)l << endl;
    for(size_t i=0;i<r[l].size();i++){
      cout << r[l][i].first << '\t' << r[l][i].second << endl;
    }
  }
}
void level_by_level(S r,A a){
  int max_size=0;
  int when=-1;
  for(int t=1;!sorted(a);++t){
    cout << "Runda " << t << endl;
    for(size_t l=0;l<r.size();l++){
      cout << "Layer " << l << endl;
      vector<bool> done(r[l].size(),false);
      vector<pair<int,pair<int,int> > > todo;
      for(size_t c=0;c<r[l].size();c++){
        todo.push_back(make_pair(r[l][c].second-r[l][c].first ,r[l][c]));
      }
      sort(todo.begin(),todo.end());
      for(size_t c=0;c<r[l].size();c++){
        r[l][c]=todo[c].second;
      }
      for(size_t c=0;c<r[l].size();c++){
        const int best=c;
        cout << r[l][best].first << '\t' << r[l][best].second << " (" << best << ") " << c << "/" << r[l].size() << endl;
        a=compare(r[l][best].first,r[l][best].second,a);
        done[best]=true;
        a.dump();
      }
      if(a.size()>max_size){
        max_size=a.size();
        when = t*r.size()+l+1;
      }
      if(sorted(a)){
        cout << "Sukces w rundzie " << t << " po " << l+1 << "-ej warstwie" << endl;
        break;
      }
      if(l==2){
        cout << "Koniec testu wydajnosciowego" << endl;
        return;
      }
    }
  }
  cout << "Posortowano :) " << endl << "Najwiêkszy automat by³ po " << when << " warstwach i mial rozmiar " << max_size << endl;
}
typedef pair<pair<int,int>,pair<int,int> > T;
typedef priority_queue<T, vector<T>, greater<T> > Q;
T t(C c,int l){
  return T(make_pair(l>>2,c.second-c.first),c);
}
void make_ready(const int x,S r,vector<int > &ready,Q &todo){
  while(1){
    ++ready[x];
    const int l=ready[x]%r.size();
    for(int j=0;j<r[l].size();++j){
      if(r[l][j].first == x || r[l][j].second == x){
        int other=r[l][j].second+r[l][j].first -x ;
        if(ready[x]<=ready[other]){
          assert(ready[x]==ready[other]);
          todo.push(t(r[l][j],ready[x]));          
        }
        return;
      }
    }
  }
}
void priority_unfold(S r,A a){
  vector<int> ready(a.width()-1,0);
  Q todo;
  for(int i=0;i<r[0].size();++i){
    todo.push((t(r[0][i],0)));
  }
  for(int t=1;!sorted(a);++t){
    int done=ready[0];
    for(int i=1;i<ready.size();++i){
      done=min(done,ready[i]);
    }
    cout << "Runda " << t << " ukonczonych warstw:" << done <<endl;
    C c =todo.top().second;
    cout << "Compare " << c.first << " vs. " << c.second << " of level " << todo.top().first.first << endl;
    todo.pop();
    a=compare(c.first,c.second,a);
    a.dump();
    make_ready(c.first,r,ready,todo);
    make_ready(c.second,r,ready,todo);
    
  }
  cout << "Posortowano :) " << endl;
}
void dump(const vector<bool> & x){
  assert(N==x.size());
  for(int i=0;i<N;++i){
    cout << x[i]?'1':'0';
  }
  cout << endl;
}
void run(const L &l,vector<bool> & x){
  assert(N==x.size());
  for(int i=0;i<l.size();++i){
    int a=l[i].first;
    int b=l[i].second;
    if(x[l[i].second]<x[l[i].first]){
      const int c=x[l[i].second];
      const int d=x[l[i].first];
      x[l[i].first]=c;
      x[l[i].second]=d;      
    }
  }
}
bool sorted(vector<bool> & x){
  for(int i=1;i<N;++i){
    if(x[i]<x[i-1]){
      return false;
    }
  }
  return true;
}
void run(const S &r,vector<bool> & x){
  dump(x);
  if(sorted(x)){    
    cout << "done" << endl;
  }else{
    for(int i=0;i<r.size();++i){
      run(r[i],x);
    }
    run(r,x);
  }
}
void test_by_example(const S &r){
  vector<bool> x(N,false);
  for(int i=0;i<N;++i){
    char z;
    cin >> z;
    x[i]=z-'0';
  }
  run(r,x);
}
int main(){
  //interactive();
  //S r = odd_even(N);
  S r=whole_rainbow(V);  
  //S r=deep_rainbow(N);
  //reverse(r.begin(),r.end());
  A a=all_words(N);
  //priority_unfold(r,a);  
  level_by_level(r,a); 
  //test_by_example(r);
  return 0;
}



