#include<algorithm>
#include<vector>
#include<iostream>
#include<cstdlib>
//88  [V=5]
using namespace std;
typedef pair<int,int> C;
typedef vector<C> L;
typedef vector<L> S;
typedef unsigned long long int lint;
C K(int a,int b){
  return C((a<?b),(a>?b));
}
const unsigned int V=5;
const unsigned int N=V*(1<<V);
const int ITER = 20;
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
        const int here=i*k + first_left++;
        const int other_block = i^((1<<(j+1))-1);
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
bool sorted(vector<bool> & v){
  for(unsigned int i=1;i<v.size();++i){
    if(v[i]<v[i-1])
      return false;
  }
  return true;
}
void update(vector<vector<int> > & z, vector<vector<bool> > &vs,const int j,const unsigned int l,bool one){
//  printf("update(%u, %u, %d)\n",j,l,one);
  vs[l][j]=one;
  if(vs.size()==l+1){
    bool szybciej = (N<=j+1 || vs[l][j]<=vs[l][j+1])  && (j<1 || vs[l][j-1]<=vs[l][j]);
//    assert(sorted(vs[l]) == szybciej);
//    if(sorted(vs[l])){
    if(szybciej){
//      puts("done");
      return;
    }else{
      cout << l << "levels for:" << endl;
      lint g=0;
      lint x=1;
      for(int i=0;i<N;i++){
        cout << (vs[0][i]?'1':'0') ;
        if(vs[0][i])
          g|=x;
        x<<=1;
      }
      cout << endl << "= " << g << endl;

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
      vs.push_back(vs[l]);
      vs[l+1][j]=!one;
    }
  }
  const int i=z[l%LAYERS][j];
  if(i>=0){
    const unsigned int b=(i>?j);
    const unsigned int a=i+j-b;
    if(one){
      update(z,vs,vs[l+1][b]?a:b,l+1,one);
    }else{
      update(z,vs,vs[l+1][a]?a:b,l+1,one);
    }
  }else{
    update(z,vs,j,l+1,one);
  }
}
void update(vector<vector<int> > & z, vector<vector<bool> > &vs,const vector<bool> & v,unsigned int j){
//  for(unsigned int j=0;j<N;++j){
    if(v[j]!=vs[0][j]){
      update(z,vs,j,0,v[j]);
//      system("PAUSE");
    }
//  }
}
vector<vector<int> > precomp(S s){
  vector<vector<int> > z(s.size(),vector<int>(N,-1));
  for(unsigned int i=0;i<s.size();++i){
    for(unsigned int j=0;j<s[i].size();++j){
      z[i][s[i][j].first]=s[i][j].second;
      z[i][s[i][j].second]=s[i][j].first;
    }
  }
  return z;
}
void hill(vector<vector<int> > & z, vector<vector<bool> > &vs,vector<bool> & v){
  const int vs_original_size = vs.size();
  for(int p=0;p<N;++p){
    v[p]=!v[p];
    update(z,vs,v,p);
    if(vs.size()==vs_original_size){
      v[p]=!v[p];
      update(z,vs,v,p);
    }else{
      hill(z,vs,v);
      break;
    }
  }
}
void test(S s){
  vector<vector<int> > z = precomp(s);
  vector<vector<bool> > vs(1,vector<bool>(N,false));
  vector<bool> v(N,false);
  for(lint i=1;;++i){
    const int p=rand()%N;
    v[p]=!v[p];
    update(z,vs,v,p);
    hill(z,vs,v);
    if(0==i%100000){
      cout << "done: " << i  << "\r";
    }
  }
}
int main(){
  srand(time(0));
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
