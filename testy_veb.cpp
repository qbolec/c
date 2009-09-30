#include<cassert>
#include<set>
#include<ctime>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
using namespace std;
int * tab=0;
int N;
int T;
int seed;
int myrand(){
  return (rand()<<16)^(rand()<<8)^(rand());
}
void prepare(){
  srand(seed);
  tab=new int[N];
  for(int i=0;i<N;++i){
    tab[i]=myrand();
  }
  sort(tab,tab+N);
}
#ifdef prec
timeval start_t,end_t;
void start(){
  gettimeofday(&start_t,0);
}
void end(char * text){
  gettimeofday(&end_t,0);
  printf("%s %d microsec\n",text,(end_t.tv_sec-start_t.tv_sec)*1000000+(end_t.tv_usec-start_t.tv_usec));
}
#else
time_t start_t,end_t;
void start(){
  time(&start_t);
}
void end(char * text){
  time(&end_t);
  printf("%s %d sec\n",text,end_t-start_t);
}
#endif
template<typename T>
struct veb{
  T * my;
#ifdef ROOTLEVEL
  int root_level[32];
#endif
#ifdef VERIFY
  int * bfs;
#endif
  int big_end[32];
  int big_start[32];
  int k;
  int real_n;
  int n;//1<<k
  void build_level_desc(int f,int t,int l){
    if(f==t)
      return;
    if(f+1<t){
      int m=(f+t)>>1;
      build_level_desc(f,m,l+1);
      build_level_desc(m,t,l+1);
	}
#ifdef ROOTLEVEL
	root_level[f]=t-1;
#endif
	big_start[t-1]=t-f;
    big_end[f]=t-f;
  }
  int path[32];
  void fill_in(T* begin,T*end,int id,int level,int fake){
#ifdef VERIFY
	assert(begin<end);
	assert(end-begin == (1<<(level+1))-1 );
	bfs[id]=fake;	
#endif
    T* mid=begin+(end-begin)/2;
	my[id]=*mid;
	path[level]=id;
	if(level){
	  const int old_height=big_end[level];
	  const int old_size=(1<<old_height)-1;
	  const int new_height=big_start[level-1];
#ifdef ROOTLEVEL
	  const int old_root= path[ root_level[level] ];
#else
	  const int old_root= path[ level+old_height-1];
#endif
	  

	  const int fake1=fake<<1;
	  const int which_child1= fake1 & old_size;
	  const int child_offset1= (which_child1 <<new_height)-which_child1;
	  const int id1= old_root + old_size + child_offset1;


	  fill_in(begin,mid,id1,level-1,fake1);
      const int id2=id1 + (1<<new_height)-1;
	  fill_in(mid+1,end,id2,level-1,fake1+1);
	}
  }
  veb(T* begin,T* end){
    real_n=(int)(end-begin);
    for(k=1;(1<<k)<real_n;k++){}
    n=1<<k;
	assert(n==real_n+1);
    my=new T[n];
#ifdef VERIFY
	bfs=new int[n];
#endif
#ifdef ROOTLEVEL
    memset(&root_level,0,sizeof(root_level));
#endif
    memset(&big_end,0,sizeof(big_end));
    memset(&big_start,0,sizeof(big_start));
    build_level_desc(0,k,0);
	fill_in(begin,end,1,k-1,1);
  }
  T * lower_bound(T e){
    int id=1;

    int fake=1;
    int level=k-1;
    T * larger=0;
    while(true){
      path[level]=id;
      if(my[id]==e){
        return my+id;
      }else{
        if(!level){
		  if(e<my[id])
			return my+id;
          return larger;
        }
        const int old_height=big_end[level];
		const int old_size=(1<<old_height)-1;
        const int new_height=big_start[level-1];
#ifdef ROOTLEVEL
		const int old_root= path[ root_level[level] ];
#else
        const int old_root= path[ level+old_height-1];
#endif
        --level;
        fake=fake<<1;
        if(my[id]<e){
          ++fake;
        }else{
          larger=my+id;
        }
        const int which_child= fake & old_size;
        const int child_offset= (which_child <<new_height)-which_child;
        
        id= old_root + old_size + child_offset;
      }
    }
    
  }
};

void test_veb(){
  start();
  prepare();
  veb<int> v(tab,tab+N);
#ifndef VERIFY
  delete tab; 
#endif
  int x=0;
  end("PREPARATION");
  start();
  for(int i=0;i<T;++i){
    int q=myrand();
    int * it=v.lower_bound(q);
#ifdef VERIFY
	int * it2=lower_bound(tab,tab+N,q);
#endif
    if(it==0){
#ifdef VERIFY
	  assert(it2==tab+N)
#endif
      x--;
    }else{
#ifdef VERIFY
	  assert(*it==*it2);
#endif
      x+=*it;
    }
  }
  printf("x=%d\n",x);
#ifdef VERIFY
  delete tab;
#endif
  end("VEB");
}
int * my_lower_bound(int * from,int * to,int e){
  int a=-1;
  int b=(int)(to-from);
  while(a+1<b){
    int c=(a+b)>>1;
    if(from[c]==e)
      return from+c;
    if(from[c]<e){
      a=c;
    }else{
      b=c;
    }
  }
  return from+b;
}
void test_tab(){
  start();
  prepare();
  vector<int> v(tab,tab+N);
  int x=0;
  end("PREPARATION");
  start();
  for(int i=0;i<T;++i){
    int * it=my_lower_bound(tab,tab+N,myrand());

    if(it==tab+N){
      x--;
    }else{
      x+=*it;
    }
  }
  printf("x=%d\n",x);
  end("TAB");
  delete tab;
}
void test_vector(){
  start();
  prepare();
  vector<int> v(tab,tab+N);
  delete tab;
  int x=0;
  end("PREPARATION");
  start();
  for(int i=0;i<T;++i){
    vector<int>::iterator it=lower_bound(v.begin(),v.end(),myrand());
    if(it==v.end()){
      x--;
    }else{
      x+=*it;
    }
  }
  printf("x=%d\n",x);
  end("VECTOR");
}
void test_set(){
  start();
  prepare();
  set<int> s(tab,tab+N);
  delete tab;
  printf("sizediff %d\n",s.size()-N);
  int x=0;
  end("PREPARATION");
  start();
  for(int i=0;i<T;++i){
    set<int>::iterator it=s.lower_bound(myrand());
    if(it==s.end()){
      x--;
    }else{
      x+=*it;
    }
  }
  printf("x=%d\n",x);
  end("SET");
}
int main(){
  N=(1<<16)-1;
  T=10000000;
  seed=42;
  test_veb();
  test_tab();
  test_set();
  test_vector();
  system("PAUSE");
}
