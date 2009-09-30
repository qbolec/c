#include
#include
#include
#include
using namespace std;
int b[1000000];
const int INF=0x7FFFFFFF;
int n;
int waga(int p,int t){
  return abs(t-p) 0 ? f:t-1;
  }
  int operator () (int x)const{
    return a*x+b;
  }
  foo(int f,int t,int a,int b):f(f),t(t),a(a),b(b){}
  foo(int x,int y1,int y2):f(x),t(x+1),a(y2-y1),b(y1-(y2-y1)*x){}
  foo rotate(int len)const{
    return foo(f-len,t-len,a,b+a*len);
  }
};
struct complex_foo{
  vector foos;
  int len;
  complex_foo * next;
  complex_foo * prev;
  int find_range(int x)const{
//    assert(0<=x);
//    assert(x<=x && x get_min()const{
    int best_v=INF;
    int best_x=0;
    for(unsigned int i=0;i<= (*this)(x) );
//    }
//    assert((*this)(best_x) == best_v);
    return make_pair(best_x,best_v);
  }
  bool ok_prev(){
    int p_min = prev->get_min().first;
    int my_min = get_min().first;
//    printf("p_min = %d my_min = %d p_len = %d my_len =%d\n",p_min,my_min,prev->len,len);
//    return (prev->len<=(my_min-p_min+n)%n ) && (len<= (p_min-my_min+n)%n);
    return (prev->len<=(my_min-p_min+n)%n );
  }
  void print()const{
    for(unsigned int i=0;iprint();
//  printf("by %d is{\n",len);
  complex_foo * g=new complex_foo();
  g->len=f->len;
  g->prev=f->prev;
  g->next=f->next;

  int start=f->find_range(len);
  g->foos.push_back(f->foos[start].rotate(len));
  g->foos.back().f=0;
  for(unsigned int i=start+1;ifoos.size();++i){
    g->foos.push_back(f->foos[i].rotate(len));
  }
  for(int i=0;ifoos.push_back(f->foos[i].rotate(len-n));
  }
  if(f->foos[start].ffoos.push_back(f->foos[start].rotate(len-n));
    g->foos.back().t=n;
  }
//  g->print();
//  for(int i=0;inext==g && g->prev==f);
//  printf("mergin f={\n");
//  f->print();
//  printf("} with g={\n");
//  g->print();
//  printf("} results with h={\n");
  complex_foo * h=new complex_foo();
  h->len=f->len+g->len;
  h->prev=f->prev;
  h->next=g->next;
  h->prev->next=h;
  h->next->prev=h;
  int fi=0;
  int gi=0;
  int last=0;
  while(lastfoos[fi].t<=last){
      ++fi;
    }
    while(g->foos[gi].t<=last){
      ++gi;
    }
    h->foos.push_back(foo(
      last,
      f->foos[fi].tfoos[gi].t,
      f->foos[fi].a+g->foos[gi].a,
      f->foos[fi].b+g->foos[gi].b
    ));
    last=h->foos.back().t;
  }
//  h->print();
//  printf("}\n");
//  for(int x=0;xfoos.size();++i){
//    assert(h->foos[i].f==h->foos[i-1].t);
//  }
//  assert(h->foos[0].f==0);
//  assert(h->foos.back().t==n);
  return h;
}
complex_foo * usual_foo(int origin,int len){
//  printf("ususal_foo origin %d len %d :\n",origin,len);
  int tmp[n+1];
  tmp[0]=waga(len,origin,0);
  for(int i=1;ilen=len;
  h->foos.push_back(foo(0,tmp[0],tmp[1]));
  for(int i=1;ifoos.back()(i)==tmp[i]){
      h->foos.back().t=i+1;
    }else{
      h->foos.push_back(foo(i,tmp[i],tmp[i+1]));
    }
  }
//  h->print();
  return h;
}

void solve(){
  scanf("%d",&n);
  if(!n){
    puts("0");
    return;
  }
  for(int i=0;i s;
  for(int i=0;inext=s[(i+1)%s.size()];
    s[(i+1)%s.size()]->prev=s[i];
  }
  int cnt = s.size();
  complex_foo * p = s[0];
  int ok=0;
  while(cnt>1 && okprev!=p && p->next!=p);
    complex_foo * f=p->prev;
    if(!p->ok_prev()){
      complex_foo * g=rotate(p,f->len);
      complex_foo * h=merge(f,g);
      delete f;
      delete p;
      delete g;
      --cnt;
      ok=0;
      p=h;
    }else{
      ++ok;
      p=p->next;
    }
  }
  int r=0;
  for(int i=0;i m=p->get_min();
    r+= m.second;
//    printf("blok od %d o dlugosci %d o koszcie %d\n",m.first,p->len,m.second);
  }
  printf("%d\n",r);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
}
