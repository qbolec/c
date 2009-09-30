#include<algorithm>
#include<vector>
#include<iostream>
#include<cstdlib>
//58 levels for 11567223771161000471
//64 levels for 275139247314960228
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
L rainbow(unsigned int k){
  L r;
  for(int i=0;i<(1<<k);++i){
    int ones=0;
    for(unsigned int j=0;j<k;++j){
      if(i&1<<j){
        ++ones;
      }
    }
    //kazda taka jedynka oznacza krawedz wychodzaca w lewo
    int first_left=0;
    for(unsigned int j=0;j<k;++j){
      if(i&1<<j){//jestem prawym koncem krawedzi typu i
        int here=i*k + first_left++;
        int other_block = i^((1<<(j+1))-1);
        int there = other_block*k+k;
        for(unsigned int z=0;z<=j;++z){
          if(!(other_block&(1<<z))){
            --there;
          }
        }
        r.push_back(K(there,here));
      }
    }
  }
  return r;
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
      cout << l << " levels for " << vs[0] << endl;
//      printf("%d levels for %llu\n",l,vs[0]);
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
  srand(time(0));
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
    v^=1ULL<<rand()%64;
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
