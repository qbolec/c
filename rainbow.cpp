#include<algorithm>
#include<vector>
#include<iostream>
#include<cstdlib>
using namespace std;
typedef pair<int,int> C;
typedef vector<C> L;
typedef vector<L> S;
typedef unsigned long long int lint;
C K(int a,int b){
  return C((a<?b),(a>?b));
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
  S s(3,L());
  
  for(int j=0;j<2;j++){
    for(int i=j+1;i<k*(1<<k);i+=2){
      s[j].push_back(K(i-1,i));
    }
  }
  s[2]=rainbow(k);
  return s;
}
lint go(C c,lint v){
  int a=c.first;
  int b=c.second;
  int A=!!((v>>a)&1);
  int B=!!((v>>b)&1);
  //assert(a<b);
  if(A!=B){
    v=(v|(1LL<<a))&(~(1LL<<b));
    //assert(v&1LL<<a);
//    assert(!(v&1LL<<b));
  }
  return v;
}
lint go(L l,lint v){
  for(size_t i=0;i<l.size();i++){
    v=go(l[i],v);
  }
  return v;
}
lint go(S s,lint v){
  for(size_t i=0;i<s.size();i++){
    v=go(s[i],v);
  }
  return v;
}
int max_iter=0;
lint e;
bool test(S s,lint v){
  lint w=v;
  for(int t=0;t<100;t++){
    if(v&v+1){
      v=go(s,v);
    }else{
      if(e!=v){
        cout << "unexpected result " << v << " instead of " << e << " for " << w << endl;
        return false;
      }
      if(t>max_iter){
        max_iter=t;
        cout << w << " required " << t << " iterations." << endl;
      }
      return true;
    }
  }
  return false;
}
const int V=4;
bool test(S s){
  lint v=0;
  for(int i=0;;i++){
    /*
    v=0;
    for(int j=0;j<64;j+=16){
      v^=rand()<<j;
    }*/
    v++;
    
    v&=(1LL<<(V*(1<<V)))-1;
    lint vr=6359535;
    v=0;
    for(int j=0;j<64;j++){
      if(vr>>j&1){
        v|=1ULL<<(63-j);
      }
    }

    e=0;
    for(int j=0;j<64;j++){
      if(v>>j&1){
        e=e*2+1;
      }
    }
    if(!test(s,v)){
      cout << "bad for " <<  v << endl;
      return false;
    }
    if(0==i%10000){
      cout << "done: " << i  << "\r";
    }
  }
}
int main(){
  S r=whole_rainbow(V);
  for(size_t l=0;l<r.size();l++){
    cout << "Layer " << l << endl;    
    for(size_t i=0;i<r[l].size();i++){
      cout << r[l][i].first << '\t' << r[l][i].second << endl;
    }
  }
  test(r);
  system("PAUSE");
}
