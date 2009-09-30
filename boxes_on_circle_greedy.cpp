#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=0x7FFFFFFF;
int n;
int waga(int p,int t){
  assert(0<=t && t<2*n);
  const int x=t-p;
  assert(-n<x);
  assert(x < n);
  return min(abs(x) ,min( abs(x-n) , abs(x+n)));
}
int waga(int w,int p,int t){//O(1)
  int r=0;
  for(int i=0;i<w;++i){
    r+=waga(p,(t+i)%n);
  }
  return r;
}
struct foo{
  int f;
  int t;
  int a;
  int b;
  int get_min()const{
    return a<0 ? t-1:f;
  }
  int operator () (int x)const{
    return a*x+b;
  }
  foo(int f,int t,int a,int b):f(f),t(t),a(a),b(b){
    assert(0<t);
    assert(f<n);
    assert(f<t);
  }
  foo(int x,int y1,int y2):f(x),t(x+1),a(y2-y1),b(y1-(y2-y1)*x){}
  foo rotate(int len)const{
    return foo(f-len,t-len,a,b+a*len);
  }
};
struct complex_foo{
  vector<foo> foos;
  int len;
  complex_foo * next;
  complex_foo * prev;
  int find_range(int x)const{
    assert(0<=x);
    assert(x<n);
    int a=0;
    int b=(int)foos.size();
    while(a+1<b){
      int c=((a+b)>>1);
      if(foos[c].f<=x){
        if(x<foos[c].t){
          return c;
        }else{
          a=c+1;
        }
      }else{
        b=c;
      }
    }
    assert(foos[a].f<=x && x<foos[a].t);
    return a;
  }
  int operator ()(int x)const{
    return foos[find_range(x)](x);
  }
  pair<int,int> get_min()const{
    int best_v=INF;
    int best_x=-1;
    assert(!foos.empty());
    for(unsigned int i=0;i<foos.size();++i){
      const int x=foos[i].get_min();
      const int v=foos[i](x);
      if(v<best_v){
        best_v=v;
        best_x=x;
      }
    }
    assert(0<=best_x);
    assert(0<=best_v);
//    printf("minimum of f= {\n");
//    print();
//    printf("} is %d equal %d\n",best_x,best_v);
    for(int x=0;x<n;++x){
      assert(best_v <= (*this)(x) );
      assert(best_v < (*this)(x) || best_x<=x );
    }
    assert((*this)(best_x) == best_v);
    for(int x=0;x<n;++x){
      if(x!=best_x){
        int a=(*this)((x-1+n)%n);
        int b=(*this)(x);
        int c=(*this)((x+1)%n);
        assert( !(b<a && b<c)); //nie ma innych minimów lokalnych
      }
    }
    return make_pair(best_x,best_v);
  }
  bool ok(complex_foo * prev)const{
    assert(prev!=this);
    const int p_min = prev->get_min().first;
    const int my_min = get_min().first;
    return (prev->len<=(my_min-p_min+n)%n)&&(len<=(p_min+prev->len-my_min+n)%n );
  }
  void print()const{
    for(unsigned int i=0;i<foos.size();++i){
//      printf("%dx+%d  [%d,%d)\n",foos[i].a,foos[i].b,foos[i].f,foos[i].t);
    }
    pair<int,int> m=get_min();
    printf("minimum at %d equal %d\n",m.first,m.second);
  }
};
complex_foo * rotate(const complex_foo * const f,int len){
//  printf("rotate f={\n");
//  f->print();
//  printf("by %d is{\n",len);
  assert(0<=len);
  assert(len<n);
  complex_foo * g=new complex_foo();
  g->len=f->len;
  g->prev=f->prev;
  g->next=f->next;
  assert(f->foos.size());
  int start=f->find_range(len);
  g->foos.push_back(f->foos[start].rotate(len));
  g->foos.back().f=0;
  for(unsigned int i=start+1;i<f->foos.size();++i){
    assert(len<=f->foos[i].f);
    g->foos.push_back(f->foos[i].rotate(len));
  }
  for(int i=0;i<start;++i){
    assert(len-n<=f->foos[i].f);
    g->foos.push_back(f->foos[i].rotate(len-n));
  }
  if(f->foos[start].f<len){
    assert(len-n<=f->foos[start].f);
    g->foos.push_back(f->foos[start].rotate(len-n));
    g->foos.back().t=n;
  }else{
    assert(g->foos.back().t==n);
  }
//  g->print();
  for(int i=0;i<n;++i){
    assert((*g)(i) == (*f)((i+len+n)%n));
  }
//  printf("}\n");
  return g;
}
complex_foo * merge (const complex_foo * const f, const complex_foo * const g){
//  assert(f->next==g && g->prev==f);
//  printf("mergin f={\n");
//  f->print();
//  printf("} with g={\n");
//  g->print();
//  printf("} results with h={\n");
  assert(f->foos.size());
  assert(g->foos.size());
  complex_foo * h=new complex_foo();
  h->len=f->len+g->len;
  assert(h->len <= n);
  h->prev=f->prev;
  h->next=g->next;
  int fi=0;
  int gi=0;
  int last=0;
  while(last<n){
    while(f->foos[fi].t<=last){
      ++fi;
    }
    while(g->foos[gi].t<=last){
      ++gi;
    }
    h->foos.push_back(foo(
      last,
      std::min(f->foos[fi].t,g->foos[gi].t),
      f->foos[fi].a+g->foos[gi].a,
      f->foos[fi].b+g->foos[gi].b
    ));
    last=h->foos.back().t;
  }
//  h->print();
//  printf("}\n");
  for(int x=0;x<n;++x){
    assert( (*h)(x) == (*f)(x)+(*g)(x));
  }
  for(unsigned int i=1;i<h->foos.size();++i){
    assert(h->foos[i].f==h->foos[i-1].t);
  }
  assert(h->foos[0].f==0);
  assert(h->foos.back().t==n);
  return h;
}
complex_foo * usual_foo(int origin,int len){
//  printf("ususal_foo origin %d len %d :\n",origin,len);
  vector<int> tmp(n+1,0);  
  tmp[0]=waga(len,origin,0);
  for(int i=1;i<n;++i){
    tmp[i]=tmp[i-1]-waga(origin,i-1)+waga(origin,(i+len-1)%n);
    assert(tmp[i]==waga(len,origin,i));
  }
  tmp[n]=tmp[n-1];
  complex_foo * h=new complex_foo();
  h->len=len;
  h->foos.push_back(foo(0,tmp[0],tmp[1]));
  for(int i=1;i<n;++i){
    if(h->foos.back()(i)==tmp[i]){
      h->foos.back().t=i+1;
    }else{
      h->foos.push_back(foo(i,tmp[i],tmp[i+1]));
    }
  }
  for(int x=0;x<n;++x){
    assert(tmp[x]==(*h)(x));
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
  vector<complex_foo*> s;
  int bs=0;
  for(int i=0;i<n;++i){
    int b;
    scanf("%d",&b);
    bs+=b;
    if(b){
      s.push_back(usual_foo(i,b));
    }
  }
  assert(bs<=n);
  for(unsigned int i=0;i<s.size();++i){
    s[i]->next=s[(i+1)%s.size()];
    s[(i+1)%s.size()]->prev=s[i];
  }
  int cnt = (int)s.size();
  if(!cnt){
    puts("0");
    return;
  }
  complex_foo * p = s[0];
  int ok=0;
  while(ok<cnt&& cnt>1){
//    printf("cnt=%d ok=%d\n",cnt,ok);
    assert(p->prev!=p && p->next!=p);
    assert(p->next->prev == p);
    assert(p->prev->next == p);
    complex_foo * f=p->prev;
    assert(p->foos.size());
    assert(p->prev->foos.size());
    complex_foo * a=f->prev;
    complex_foo * b=p->next;
    if(!p->ok(p->prev)){
      complex_foo * g=rotate(p,f->len);
      complex_foo * h=merge(f,g);
      delete g;

      if(!p->prev->ok(p)){
        complex_foo * g2=rotate(f,p->len);
        complex_foo * h2=merge(p,g2);
        delete g2;
        assert(cnt==2 || h2->get_min().second != h->get_min().second);
        if(h2->get_min().second < h->get_min().second){
          delete h;
          h=h2;
        }else{
          delete h2;
        }
      }
      --cnt;
      ok=0;
      delete p;
      p=h;
      if(cnt>1){
        p->next=b;
        p->prev=a;
        b->prev=p;
        a->next=p;
      }
      delete f;
    }else{
      ++ok;
      p=p->next;
    }
  }
//  assert(cnt>1 || p==p->next && p==p->prev);
  int r=0;
  for(int i=0;i<cnt;++i){
    assert(p->foos.size());
    pair<int,int> m=p->get_min();
    r+= m.second;
    complex_foo * p2=p;
    //printf("blok od %d o dlugosci %d o koszcie %d\n",m.first,p->len,m.second);
    p=p->next;
    delete p2;
  }
  printf("%d\n",r);
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
}
