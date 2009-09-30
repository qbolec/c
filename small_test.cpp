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
S rainbow(int k){
  S r;
  for(int i=0;i<k;++i){
    L l;
    for(int j=0;j<(1<<k);++j){
      if(j&(1<<i)){
        l.push_back(K(j,j^((1<<(i+1))-1)));
      }
    }
    r.push_back(l);
  }
  return r;
}
L rainbow2(vector<vector<int> > & a,S & r){
  L l;
  for(size_t i=0;i<r.size();++i){
    for(size_t j=0;j<r[i].size();++j){
      l.push_back( K(a[ r[i][j].first ][i],a[ r[i][j].second ][i]) );
    }
  }
  return l;
}
S odeven(int k){
  S s(2,L());
  for(int j=0;j<2;j++){
    for(int i=j+1;i<k*(1<<k);i+=2){
      s[j].push_back(K(i-1,i));
    }
  }
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
lint go(L &l,lint v){
  for(size_t i=0;i<l.size();i++){
    v=go(l[i],v);
  }
  return v;
}
lint go(S &s,lint v){
  for(size_t i=0;i<s.size();i++){
    v=go(s[i],v);
  }
  return v;
}
int test(S &s,lint v){
  for(int t=0;t<100;t++){
    if(v&v+1){
      v=go(s,v);
    }else{
      return t;
    }
  }
}
const int V=3;
int test(S s){
  int max_iter=0;
  for(lint v=0;v<(1LL<<(V*(1<<V)));++v){
    int t=test(s,v);
    if(t>max_iter){
      max_iter=t;
    }
  }
  return max_iter;
}

S r=rainbow(V);
S o=odeven(V);
vector<vector<int> > a;
void show(L l){
  for(size_t i=0;i<l.size();i++){
    printf("%d : %d\n",l[i].first,l[i].second);
  }
}
void show(S s){
  for(size_t i=0;i<s.size();i++){
    printf("Layer %d:\n",i);
    show(s[i]);
  }
}
int min_iter = 1000;
int tests_done =0;
int start_time;
void test(int k){
  sort(a[k].begin(),a[k].end());
  do{
    if(k==0){
      S s=o;
      s.push_back(rainbow2(a,r));
      int iter=test(s);
      if(iter<min_iter){
        min_iter=iter;
        show(s);
        printf("Required only %d iterations\n",min_iter);
      }
      ++tests_done;
      if(time(0)-start_time > 60){
        printf("time up, done %d tests\n",tests_done);
        exit(0);
      }
    }else{
      test(k-1);
    }
  }while(next_permutation(a[k].begin(),a[k].end()));
}

int main(){
  start_time=time(0);
  for(int i=0;i<(1<<V);++i){
    vector<int> x;
    for(int j=0;j<V;++j){
      x.push_back(i*V+j);
    }
    a.push_back(x);
  }
  test(V);
  system("PAUSE");
}
