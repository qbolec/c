#include<map>
#include<cstring>
#include<cstdlib>
using namespace std;
#define MAX_PAYLOAD_LEN 100
#define MAX_VARCHAR_LEN 128
template<int LEN>
struct varchar{
  char key[LEN];
  varchar(){
    key[0]='\0';
  }
  varchar(const char * p){
    strcpy(key,p);
  }
  bool operator == (const varchar & other)const{
    // puts("varchar == called");
    return !strcmp(key,other.key);
  }
  bool operator < (const varchar & other)const{
    //  puts("varchar < called");
    return strcmp(key,other.key)<0;
  }
  void pseudorandom(){
    memset(key,'0',LEN-1);
    sprintf(key+LEN-13,"%012d",rand());
    key[LEN-1]='\0';
  }
};
typedef varchar<MAX_VARCHAR_LEN+1> key_varchar;
typedef varchar<MAX_PAYLOAD_LEN+1> payload_varchar;

typedef key_varchar K;
typedef payload_varchar V;

template<typename T>
struct comp_state{
  int smaller_agree;
  int bigger_agree;
  const T * saved;
  void reset(const T * s){
//    printf("reset %x\n",this);
    smaller_agree=bigger_agree=0;
    saved = s;
  }
};

template<int LEN>
struct varchar_compare{
  typedef varchar<LEN> V;
  comp_state<V> * state;
  void reset(const V * s=NULL){
    state->reset(s);
  }
  varchar_compare(){
    state = new comp_state<V>();
//    printf("constructed %d\n",LEN);
  }
  bool operator () (const V &a,const V &b){
//    printf("%x . compare (%d,%d) %x, %x, %x\n",this->state,this->state->smaller_agree,this->state->bigger_agree,&a,&b,this->state->saved);
    if(this->state->saved!=&a){
      this->reset(&a);
    }
    const int start=(this->state->smaller_agree<?this->state->bigger_agree);
    if(start>0){
//      printf("gain %d\n",start);
    }
    for(int i=start;i<LEN;++i){
      if(a.key[i]<b.key[i]){
        if(this->state->saved==&a){
//          printf("ret true, saved\n");
          this->state->bigger_agree=i;
        }else{
          printf("ret true, notsaved\n");
          system("PAUSE");
        }
        return true;
      }else if(b.key[i]<a.key[i]){
        if(this->state->saved==&a){
//          printf("ret false, saved\n");
          this->state->smaller_agree=i;
        }else{
          printf("ret false, notsaved\n");
          system("PAUSE");
        }
        return false;
      }
    }
//    printf("hit\n");
//    system("PAUSE");
    return false;
  }
};

varchar_compare<MAX_VARCHAR_LEN+1> comparator;
typedef multimap<K,V,less<K> > N;
typedef multimap<K,V,varchar_compare<MAX_VARCHAR_LEN+1> > M;
N data;
//M data(comparator);
int main(){
  srand(2);
  key_varchar x;
  payload_varchar y;
  y.pseudorandom();
  for(int i=0;i<1000000;++i){
    x.pseudorandom();
    y.pseudorandom();
//printf("{{{{ %x\n",&x);
    comparator.reset();
    data.insert(make_pair(x,y));
//printf("}}}}\n");
  }
  puts("DONE");
  system("PAUSE");
  const char * last=0;
  for(M::iterator it = data.begin();it!=data.end();++it){
    if(last){
      if(strcmp(it->first.key,last)<0){
        puts("BAD");
        system("PAUSE");
      }else{
        puts("OK");
      }
    }
    last=it->first.key;
    printf("%s -> %s \n==\n",it->first.key,it->second.key);
  }

  system("PAUSE");
}
