#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
int n,m,M;
void display(int x,bool nl=true){
  for(int i=n;i--;)
    putchar(x&1<<i?'1':'0');
  if(nl)
    puts("");
}
int read(){
  char t[33];
  scanf("%s",t);
  int x=0;
  for(int i=0;i<n;i++)
    if(t[i]=='1')
      x|=1<<n-i-1;
  return x;
}
int main(){
  puts("podaj n, czyli polowe liczby bitow");
  scanf("%d",&n);
  M=(1<<n)-1;
  set<int> alive;
  multiset<int> saper;
  puts("ilu saperow?");
  scanf("%d",&m);
  puts("podaj saperow (jako ciagi 0-1-kowe)");
  for(int i=m;i--;){
   saper.insert(read());
  }
  puts("퓓we ci퉓i na starcie:");
  for(int v=1<<n;v--;){
    if(saper.find(v)==saper.end()){
      alive.insert(v);
      display(v);
    }
  }
  
  for(int t=1;t<=n;++t){
    printf("warstwa %d\n",t);
    set<int> alive2;
    for(set<int>::iterator it=alive.begin();it!=alive.end();++it){
      alive2.insert( (*it)<<1 & M );
      alive2.insert( ((*it)<<1|1) & M );
    }
    swap(alive,alive2);
    puts("potencjalnie osi퉓alne ci퉓i:");
    for(set<int>::iterator it=alive.begin();it!=alive.end();++it){
      display(*it);
    }
    puts("saperzy");
    for(multiset<int>::iterator it=saper.begin();it!=saper.end();++it){
      display( (*it) <<1 & M,false);
      printf(" lub ");
      display( ((*it) <<1 | 1) & M);
    }
    puts("decyzje?");
    multiset<int> saper2;
    for(multiset<int>::iterator it=saper.begin();it!=saper.end();++it){
      int x;
      scanf("%d",&x);
      x=(*it<<1|x) &M;
      saper2.insert(x);
      alive.erase(x);
    }
    swap(saper2,saper);
    puts("퓓we ci퉓i:");
    for(set<int>::iterator it=alive.begin();it!=alive.end();++it){
      display(*it);
    }
  }

}
