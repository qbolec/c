#define FLAT

#ifdef FLAT
  const int V=5;
  const int N=(V*(1<<V));
#else
  const int N=16;
#endif

#include<cassert>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<list>
#include<map>
using namespace std;
void dump(const vector<bool> & x){
  assert(N==x.size());
  for(int i=0;i<N;++i){
    cout << x[i]?'1':'0';
  }
  cout << endl;
}
template<int SIZE,typename T>
class DiskSlab{
  string filename;  
  T data[SIZE];
public:
  DiskSlab(string filename):filename(filename){
    FILE * f=fopen(filename.c_str(),"rb");
    if(NULL!=f){
      if(fread(data,sizeof(T),SIZE,f)!=SIZE){
        cerr << "failed to read slab from disk" << endl;
        exit(-1);
      }    
      fclose(f);
    }
  }
  void dump(){
    FILE * f=fopen(filename.c_str(),"wb");
    if(NULL==f || fwrite(data,sizeof(T),SIZE,f)!=SIZE){
      cerr << "failed to write slab from disk" << endl;
      exit(-1);
    }        
    fclose(f);
  }
  T & operator [](int index){
    return data[index];
  }
  const T & operator [](int index)const{
    assert(0<=index && index<SIZE);
    return data[index];
  }
};
template<typename T>
class DiskVector{
  static const int SIZE=1<<20;
  static const int MAX_LRU_SIZE=5;
  typedef DiskSlab<SIZE,T> Slab;
  typedef list<pair<Slab *,long long> > List;
  char basename[30];
  static int free_base_number;
  List lru;
  int lru_size;
  long long my_size;  
public:
  int cache_miss;
  DiskVector():lru_size(0),my_size(0),cache_miss(0){    
    sprintf(basename,"c:\\automaty\\wektor.%d",free_base_number);
    ++free_base_number;
  }
  
  long long size()const{
    return my_size;
  }  
  T & get_ref(long long index){
    assert(0<= index && index<my_size);
    const long long base=index/SIZE;
    for(List::iterator it = lru.begin();it!=lru.end();++it){
      if(it->second==base){
        Slab * s =it->first;
        if(it!=lru.begin()){
          lru.erase(it);
          lru.push_front(make_pair(s,base));
        }
        return (*s)[(int)(index%SIZE)];
      }
    }
    char filename[1024];
    sprintf(filename,"%s.%d",basename,base);
    Slab * new_slab = new Slab(filename);
    lru.push_front(make_pair(new_slab,base));
    ++lru_size;
    if(MAX_LRU_SIZE<lru_size){
      lru.back().first->dump();
      delete lru.back().first;
      lru.pop_back();
      --lru_size;
      ++cache_miss;
    }
    return (*new_slab)[(int)(index%SIZE)];
  }
  T & operator [](long long index){
    return get_ref(index);
  }
  const T & operator[](long long index)const{
    return ((DiskVector<T>*)this)->get_ref(index);
  }
  void push_back(T x){
    ++my_size;
    (*this)[my_size-1]=x;
  }
  void delete_files(){
    for(List::iterator it = lru.begin();it!=lru.end();++it){
      delete it->first;
    }
    lru.clear();
    lru_size=0;
    char filename[1024];
    for(long long base=0;base*SIZE<my_size;++base){
      sprintf(filename,"%s.%d",basename,base);
      remove(filename);
    }
  }
  void operator =(const DiskVector<T> & other){    
    delete_files();
    for(long long i=0;i<other.size();++i){
      push_back(other[i]);
    }
  }
  void resize(long long new_size){
    assert(my_size<=new_size);
    my_size=new_size;
  }
  ~DiskVector(){
    delete_files();
  }
};
template<typename T>
T DiskVector<T>::free_base_number=0;

typedef DiskVector<int> Vector;

class A{
private: 
  vector<pair<int,int> > ranges;  
public:
  DiskVector<int> delta[2];  
  int width()const{
    return (int)ranges.size();
  //  return (int)levels.size();
  }
  void set_width(int w){
    ranges.resize(w,pair<int,int>(-1,-1));
    //levels.resize(w,vector<int>());
  }
  bool contains(const vector<bool> & w)const{
    for(int i=0,s=0;i<w.size();++i){
      if(-1==delta[w[i]][s]){
        return false;
      }
      s=delta[w[i]][s];
    }
    return true;
  }
  void add_to_level(int l,int x){
    /*for(int i=0;i<width();++i){
      if(i!=l){
        assert(ranges[i].second<=x || x<ranges[i].first);
      }
    }*/
    if(-1==ranges[l].first){
      ranges[l].first=x;
      ranges[l].second=x+1;
    }else{
      if(x<ranges[l].first){
        ranges[l].first=x;
      }else if(ranges[l].second<=x){
        ranges[l].second=x+1;
      }      
    }        
    //levels[l].push_back(x);
  }
  int level_size(int l)const{
    return ranges[l].second-ranges[l].first;
    //return (int)levels[l].size();
  }
  int level_element(int l,int p)const{
    return ranges[l].first+p;
    //return levels[l][p];
  }
  int size()const{
    return (int)delta[0].size();
  }
  double cardinality(){
    vector<double> c(size(),0);
    assert(level_size(width()-1)==1);
    c[level_element(width()-1,0)]=1.0;

    for(int l=width()-2;0<=l;--l){
      for(int i=0;i<level_size(l);++i){
        const int v=level_element(l,i);
        assert(c[v]==0.0);
        for(int x=0;x<2;++x){
          if(0<=delta[x][v]){
            c[v]+=c[delta[x][v]];
          }
        }
      }
    }
    assert(level_size(0)==1);
    return c[level_element(0,0)];
  }
  void dump(const char * x = "", int f=0){
    static double last_c = 1.0;
    double c= cardinality();
    cout << "Automat " << x << " ma " << width() << " warstw oraz " << size() << " stanow i moc " << c << " =*" << c/last_c << endl;
    last_c = c;
    if(size()<26 || 0<f){
      for(int l=f;l<width();++l){
        for(int j=0;j<level_size(l);++j){
          const int i=level_element(l,j);
          cout << i << " (" << l << ") -> [ " << delta[0][i] << " , " << delta[1][i] << "]" << endl;
        }
      }
    }
  }
  int cm(){
    return delta[0].cache_miss+delta[1].cache_miss;
  }
  A * cleanup(){
    int start=cm();
    assert(size()>0);
    assert(width()>0);

    vector<bool> endable(size(),false);

    for(int i=(int)level_size(width()-1);i--;){
      endable[level_element(width()-1,i)]=true;
    }
    for(int i=(int)width()-1;0<=i;--i){
      for(int j=0;j<level_size(i);++j){
        const int v=level_element(i,j);
        for(int d=0;d<2;++d){
          if(0<=delta[d][v] && endable[delta[d][v]]){
            endable[v] = true;
            break;
          }
        }
      }
    }

    assert(size()>0);
    vector<int> alias(size(),-1);
    queue<int> s;
    s.push(0);
    alias[0]=0;
    int f=1;
    while(!s.empty()){
      const int v=s.front();
      s.pop();
      for(int i=0;i<2;++i){
        const int u=delta[i][v];
        if(0<=u && endable[u]){
          if(alias[u]<0){
            alias[u]=f++;
            s.push(u);
          }
        }
      }
    }
    A * _r = new A();
    A &r = *_r;
    for(int i=0;i<2;++i){
      r.delta[i].resize(f);
    }
    r.set_width(width());
    for(int i=0;i<width();++i){
      int k=0;
      for(int j=0;j<(int)level_size(i);++j){
        const int v=level_element(i,j);
        const int u=alias[v];
        if(0<=u){
          r.add_to_level(i,u);
          //r.levels[i][k++]=u;        
        }
      }
      //r.levels[i].resize(k);
    }
    assert(size()==alias.size());
    for(size_t v=0;v<alias.size();++v){
      const int u=alias[v];
      if(0<=u){
        for(int i=0;i<2;++i){
          r.delta[i][u]=( (0<=delta[i][v]) ? (alias[delta[i][v]]) : (-1) );
        }
      }
    }    
    //cout << "cu: " << cm()-start << " oraz " << _r->cm() << endl;
    return _r;
  }

  A * minimize(){
    int start=cm();
    assert(0<size());
    assert(0<width());
    assert(level_size(0)==1);
    //map<int,int> renaming;
    vector<int> renaming(size(),-1);

    A * _r=new A();
    A & r =*_r;
    r.set_width(width());
    r.add_to_level(0,0);
    r.delta[0].push_back(-1);//tmp
    r.delta[1].push_back(-1);//tmp


    int f=0;
    for(int i=width()-1;0<i;--i){
      vector<pair<pair<int,int>, int> > taken;
      for(int j=0;j<(int)level_size(i);++j){
        const int v=level_element(i,j);
        int x[2];
        for(int d=0;d<2;++d){
          x[d]= 0<=delta[d][v]? renaming[delta[d][v]] : -1;
        }
        taken.push_back(make_pair(make_pair(x[0],x[1]),v));
      }
      //renaming.clear();
      sort(taken.begin(),taken.end());
      pair<int,int> last_taken(-2,-2);
      for(size_t j=0;j<taken.size();++j){
        if(taken[j].first!=last_taken){
          ++f;
          last_taken=taken[j].first;
          r.add_to_level(i,f);
          int x[2]={last_taken.first,last_taken.second};
          for(int d=0;d<2;++d){
            r.delta[d].push_back(x[d]);
          }        
        }
        renaming[taken[j].second]=f;
      }      
    }
    for(int d=0;d<2;++d){
      r.delta[d][0]= 0<=delta[d][0]? renaming[delta[d][0]] : -1;
    }  
    //cout << "min: " << cm()-start << " oraz " << _r->cm() << endl;
    return _r;    
  }  
  bool sorted()const{
    if(size()!=width()*2-2){
      //cout << "zla ilosc stanow" << endl;
      return false;
    }
    if(level_size(0)!=1 || level_size(width()-1)!=1){
      //cout << "zle konce" << endl;
      return false;
    }
    for(int i=1;i<width()-1;++i){
      if(level_size(i)!=2){
        //cout << "zla wielkosc warstwy " << i << " jest " << a.level_size(i) << endl;
        return false;
      }
    }
    if(delta[0][0]<0 || delta[1][0]<0){
      //cout << "zly start" << endl;
      return false;
    }
    int x=delta[0][0];
    int y=delta[1][0];
    for(int i=1;i<width()-1;++i){    
      if(0<=delta[0][y]){
        //cout << "da sie zerem" << endl;
        return false;
      }
      if(delta[1][y]<0){
        //cout << "nie da sie jedynka" << endl;
        return false;
      }
      y=delta[1][y];
      if(delta[0][x]<0){
        //cout << "z zera zerem sie nie da" << endl;
        return false;
      }
      if(delta[1][x]!=y){
        //cout << "z zera jedynka idzie sie nie do y" << endl;
        return false;

      }
      x=delta[0][x];
    }
    return true;
  }
  A * force(const int p,const int d)const{
    assert(0<=p && p<width());
    assert(0<=d && d<=1);
    A * r = new A();
    *r=*this;
    for(int i=0;i<level_size(p);++i){
      const int v=level_element(p,i);
      r->delta[1-d][v]=-1;
    }
    return r;
  }
  A * flip(const int p)const{
    assert(0<=p && p<width());
    A * r = new A();
    *r=*this;
    for(int i=0;i<level_size(p);++i){
      const int v=level_element(p,i);
      swap(r->delta[0][v],r->delta[1][v]);
    }
    return r;
  }
  friend ostream & operator << (ostream & o,const A & a);
  friend istream & operator >> (istream & f,A & a);
};
ostream & operator << (ostream & o,const A & a){
  o << a.ranges.size() << endl;  
  for(int i=0;i<a.ranges.size();++i){
    o << a.ranges[i].first << ' ' << a.ranges[i].second << endl;
  }  
  for(int d=0;d<2;++d){
    o << a.delta[d].size() << endl;
    for(int i=0;i<a.delta[d].size();++i){
      o << a.delta[d][i] << endl;
    }
  }
  return o;
}
istream & operator >> (istream & f,A & a){
  int rs;
  f>>rs;
  a=A();
  for(int i=0;i<rs;++i){
    int x,y;
    f >> x >> y;
    a.ranges.push_back(make_pair(x,y));
  }  
  for(int d=0;d<2;++d){
    int ds;
    f >> ds;     
    for(int i=0;i<ds;++i){
      int x;
      f >> x;
      a.delta[d].push_back(x);      
    }
  }
  return f;
}
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
  for(unsigned int i=0;i<n/2;++i){
    r.push_back(K(i,i+n/2));
  }
  S u=remap(m,r);
  S all=join(m,u);
  L b;
  for(unsigned int i=0;i<n/2;i++){
    b.push_back(K(i,n-1-i));
  }
  all.push_back(b);
  return all;  
}
L rainbow(unsigned int k){
  S d=deep_rainbow(k);
  L r;
  vector<vector<int> > m(1<<k,vector<int>(k,-1));
  int f=0;
  for(int i=0;i<(1<<k);++i){
    for(int j=0;j<k;++j){
      if( (i & (1<<j))!=0 ){//jesli jest prawym koncem
        m[i][j]=f++;
      }
    }
    for(int j=k;j--;){
      if( (i & (1<<j))==0 ){//jesli jest lewym koncem
        m[i][j]=f++;
      }
    }
  }
  for(int i=0;i<(1<<k);++i){
    for(int j=k;j--;){
      if( (i & (1<<j))!=0 ){//jesli jest prawym koncem
        const int other = i^((1<<(j+1))-1);
        r.push_back(K(m[i][j],m[other][j]));        
      }
    }
  }
  return r;
}
L rainbow_(unsigned int k){
  if(!k)return L();
  L m=rainbow(k-1);
  L r;
  int f=0;
  for(int i=0;i<(1<<(k-1));i++){
    for(size_t j=0;j<(k-1);j++){
      r.push_back(C(i*(k-1)+j, f++));
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
      //s[j*2].push_back(K(i-1,i));
      s[j*2+1].push_back(K(i-1,i));
    }
  }
  //s[1]=s[3]=rainbow(k);
  s[0]=s[2]=rainbow(k);
  for(unsigned int j=0;j<s.size();++j){
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
  for(unsigned int j=0;j<s.size();++j){
    sort(s[j].begin(),s[j].end());
  }
  return s;
}

A * all_words(int l){
  A * a=new A();
  a->set_width(l+1);
  for(int f=0;f<=l;++f){
    a->add_to_level(f,f);
    if(f<l){
      for(int x=0;x<2;++x){
        a->delta[x].push_back(f+1);
      }
    }else{
      for(int x=0;x<2;++x){
        a->delta[x].push_back(-1);
      }
    }
  }
  return a;
}

A * alternative(A *_a,A *_b){
  A &a=*_a;
  A &b=*_b;
  const int w=a.width();
  assert(w==(int)b.width());
  map<pair<int,int>, int >  pairing;
  A * _z = new A();
  A &z = *_z;
  z.set_width(w);
  
  vector<pair<int,pair<int,int> > > s,next_s;
  int f=0;
  z.add_to_level(0,f);
  for(int i=0;i<2;++i){
    z.delta[i].push_back(-1);
  }
  s.push_back(make_pair(f,make_pair(0,0)));
  ++f;
  int last_level=0;
  while(!s.empty() || !next_s.empty()){    
    //const int l=z.level[g];
    if(s.empty()){
      swap(s,next_s);
      pairing.clear();
      ++last_level;
      cout << "done:" << last_level << "   \r";
    }
    assert(!s.empty());
    const int g=s.back().first;
    //cout << "Visiting " << g << endl;
    const pair<int,int> p = s.back().second;
    //cout << "That is " << p.first << " + " << p.second << endl;
    const int ia=p.first;
    const int ib=p.second;
    s.pop_back();
    for(int d=0;d<2;++d){
      const int ja=( (0<=ia) ? (a.delta[d][ia]) : (-1) );
      const int jb=( (0<=ib) ? (b.delta[d][ib]) : (-1) );
      if((ja<0) && (jb<0)){
        assert(z.delta[d][g] == -1);
      }else{
        pair<int,int> p2(ja,jb);
        if(pairing.find(p2)==pairing.end()){
          pairing[p2] = f;
          z.add_to_level(last_level+1,f);
          for(int i=0;i<2;++i){
            z.delta[i].push_back(-1);
          }
          next_s.push_back(make_pair(f,p2));
          ++f;          
        }
        z.delta[d][g] = pairing[p2];
      }
    }
  }
  assert(z.delta[0].size() == z.delta[1].size());
  return _z;
}
A * one_one(int x,int y,const A * a){
  A * b = a->force(x,1);
  A * c = b->force(y,1);
  delete b;
  A * d = c->cleanup();
  delete c;
  A * e = d->minimize();  
  delete d;
  return e;
}
A * old_zero(int x,const A * a){
  A * b = a->force(x,0);
  A * c = b->cleanup();
  delete b;
  A * d = c->minimize();
  delete c;
  return d;
}
A * new_zero(int x,int y,const A * a){
  A * b = a->force(x,1);
  A * c = b->force(y,0);
  delete b;
  A * d = c->cleanup();
  delete c;
  A * e = d->minimize();
  delete d;
  A * f = e->flip(x);
  delete e;
  A * g = f->flip(y);
  delete f;
  return g;  
}
A * zero_whatever(int x,int y,const A * a){
  A * b = new_zero(x,y,a);
  A * c = old_zero(x,a);
  A * d = alternative(b,c);
  delete b;
  delete c;
  A * e = d->minimize();
  delete d;
  return e;  
}
A * compare(int x,int y,A * a){
  assert(x<y);
  A * b = one_one(x,y,a);
  A * c = zero_whatever(x,y,a);
  delete a;
  A * d = alternative(b,c);
  delete b;
  delete c;
  A * e = d->minimize();
  delete d;
  return e;  
}
void interactive(){
  int n;
  cout << "Ile bitów?" << endl;
  cin >> n;
  A * a=all_words(n);  
  while(1){
    a->dump();
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

vector<bool> unsorted_word(const A &a){
  int s=0;
  vector<bool> w;
  for(int i=0;i<a.width();++i){
    for(int j=1;j+i<a.width();++j){      
      w.push_back(true);
      w.push_back(false);
      if(a.contains(w)){
        while(w.size()+1<a.width()){
          w.push_back(false);
          if(!a.contains(w)){
            w.pop_back();
            w.push_back(true);
            assert(a.contains(w));
          }
        }
        return w;
      }else{
        w.pop_back();
      }
    }
    w.resize(i,false);
    w.push_back(false);  
  }
  cerr << "nie ma nieposortowanego slowa" << endl;
  exit(-1);
}
void run(const L &l,vector<bool> & x){
  assert(N==x.size());
  for(size_t i=0;i<l.size();++i){
    int a=l[i].first;
    int b=l[i].second;
    if(x[l[i].second]<x[l[i].first]){
      const bool c=x[l[i].second];
      const bool d=x[l[i].first];
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
  while(!sorted(x)){
    for(size_t i=0;i<r.size();++i){      
      run(r[i],x);
      dump(x);
      if(sorted(x)){
        break;
      }
    }        
    cout << endl;
  }  
  cout << "done" << endl;
}
void backtrace(S r,char * fn,int dumped){
  --dumped;
  char file_name[256];
  sprintf(file_name,"%s%d.txt",fn,dumped);
  ifstream f(file_name);  
  int x,y;
  A a;  
  f>>a;
  f>>x>>y;    
  f.close();
  vector<bool> w=unsorted_word(a);  
  cout << "Przyklad trudnego slowa to" << endl;
  while(0<dumped--){
    assert(w[x]<=w[y]);
    A b;
    sprintf(file_name,"%s%d.txt",fn,dumped);
    ifstream g(file_name);  
    g>>b;
    if(!b.contains(w)){
      bool c=w[x];
      bool d=w[y];
      w[x]=d;
      w[y]=c;
      assert(b.contains(w));
    }
    g>>x>>y;    
  }
  run(r,w);
}
void level_by_level(S r,A * a,char * fn){
  int max_size=0;
  size_t when=-1;
  int dumped=0;
  for(int t=1;!a->sorted();++t){
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
        cout << r[l][c].first << '\t' << r[l][c].second << " " << c << "/" << r[l].size() << endl;
        a=compare(r[l][c].first,r[l][c].second,a);        
        done[c]=true;
        a->dump();
#ifdef backtrace
        if(!a->sorted()){
          char file_name[256];
          sprintf(file_name,"%s%d.txt",fn,dumped++);
          ofstream f(file_name);  
          f << a << endl;
          f << r[l][c].first << '\t' << r[l][c].second <<  endl;  
          f.close();
        }
#endif
      }
      if(a->size()>max_size){
        max_size=a->size();
        when = t*r.size()+l+1;
      }
      if(a->sorted()){
        cout << "Sukces w rundzie " << t << " po " << l+1 << "-ej warstwie" << endl;
        break;        
      }
    }
  }
#ifdef backtrace
  backtrace(r,fn,dumped);        
#endif
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
    const int l=ready[x]%(int)r.size();
    for(size_t j=0;j<r[l].size();++j){
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
void priority_unfold(S r,A * a){
  vector<int> ready(a->width()-1,0);
  Q todo;
  for(size_t i=0;i<r[0].size();++i){
    todo.push((t(r[0][i],0)));
  }
  for(int t=1;!a->sorted();++t){
    int done=ready[0];
    for(size_t i=1;i<ready.size();++i){
      done=min(done,ready[i]);
    }
    cout << "Runda " << t << " ukonczonych warstw:" << done <<endl;
    C c =todo.top().second;
    cout << "Compare " << c.first << " vs. " << c.second << " of level " << todo.top().first.first << endl;
    todo.pop();
    a=compare(c.first,c.second,a);
    a->dump();
    make_ready(c.first,r,ready,todo);
    make_ready(c.second,r,ready,todo);
    
  }
  cout << "Posortowano :) " << endl;
}

void test_by_example(const S &r){
  vector<bool> x(N,false);
  for(int i=0;i<N;++i){
    char z;
    cin >> z;
    x[i]=(z=='1');
  }
  run(r,x);
}
int main(int argc,char * args[]){  
#ifdef backtrace
  assert(argc==2);
#endif
  //interactive();
  //S r = odd_even(N); 
#ifdef FLAT
  S r=whole_rainbow(V);  
#else
  S r=deep_rainbow(N);
  reverse(r.begin(),r.end());
#endif
  dump(r);
  A * a=all_words(N);
  //priority_unfold(r,a);  
  level_by_level(r,a,args[1]); 
  //test_by_example(r);
  return 0;
}



