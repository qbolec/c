#include<algorithm>
#include<vector>
#include<iostream>
#include<cstdlib>
//56 levels for 1128688
using namespace std;
typedef pair<int,int> C;
typedef vector<C> L;
typedef vector<L> S;
typedef unsigned long long int lint;
C K(int a,int b){
  return C((a<?b),(a>?b));
}
const int V=4;

const int LAYERS = 4;
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
  S s(LAYERS,L());

  for(int j=0;j<2;j++){
    for(int i=j+1;i<k*(1<<k);i+=2){
      s[j*2].push_back(K(i-1,i));
    }
  }
  s[1]=s[3]=rainbow(k);
  return s;
}
void update(vector<vector<int> > & z, vector<lint> &vs,const int j,const unsigned int l,bool one){
//  printf("update(%u, %u, %d)\n",j,l,one);
  vs[l]^=1LL<<j;
  if(vs.size()==l+1){
    if((vs[l]-1|vs[l]) == ~0ULL){
//      puts("done");
      return;
    }else{
      printf("%d levels for %llu\n",l,vs[0]);
/*      for(int i=0;i<l;++i){
        for(int k=0;k<64;++k){
          int f=z[i%LAYERS][k];
          if(f>=0){
            int a=(i<?f);
            int b=(f>?i);
            int A=vs[i]>>a&1;
            int B=vs[i]>>b&1;
            assert(a<=b);
          }
        }
      }
      system("PAUSE");*/
      vs.push_back(vs[l]^(1LL<<j));
    }
  }
  const int i=z[l%LAYERS][j];
  if(i>=0){
    const unsigned int b=(i>?j);
    const unsigned int a=i+j-b;
    if(one){
      update(z,vs,(vs[l+1]>>b &1)?a:b,l+1,one);
    }else{
      update(z,vs,(vs[l+1]>>a &1)?a:b,l+1,one);
    }
  }else{
    update(z,vs,j,l+1,one);
  }
}
void update(vector<vector<int> > & z, vector<lint> &vs,const lint v){
  const lint d=v^vs[0];
  for(unsigned int j=0;j<64;++j){
    if(d>>j&1){
      update(z,vs,j,0,v>>j & 1);
//      system("PAUSE");
    }
  }
}
void test(S s){
  vector<vector<int> > z(s.size(),vector<int>(64,-1));
  for(unsigned int i=0;i<s.size();++i){
    for(unsigned int j=0;j<s[i].size();++j){
      z[i][s[i][j].first]=s[i][j].second;
      z[i][s[i][j].second]=s[i][j].first;
    }
  }
  vector<lint> vs(1,0);
  lint v=0;
  for(lint i=1;;++i){
    v^=1ULL<<rand()%32;
    update(z,vs,v);
    if(0==i%100000){
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
