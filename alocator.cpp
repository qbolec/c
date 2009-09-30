#include<cstdio>
#include<set>
#include<vector>
using namespace std;
set<int> freemem;
set<int> kill[66000];
int when_to_kill[33000];
int current_time=0;
int aloc(){
  set<int>::iterator x=freemem.begin();
  int ad= *x;
  freemem.erase(x);
  when_to_kill[ad]=current_time+600;
  kill[when_to_kill[ad]].insert( ad );
  return ad;
}
char aces(int adres){
  if(when_to_kill[adres]){
    kill[ when_to_kill[adres] ] .erase( adres) ;
    when_to_kill[adres]=current_time+600;
    kill[when_to_kill[adres]].insert( adres );    
    return '+';
  }else{
    return '-';
  }
}
void catchup(int t){
  while(current_time<= t){
    for(set<int>::iterator x= kill[current_time].begin() ; x!= kill[current_time].end(); ++x){
      int ad=*x;
      when_to_kill[ad]=0;
      freemem.insert(ad);      
    }
    kill[current_time].clear();
    current_time++;
  }
  current_time--;
}
int main(){
  for(int i=1;i<=30000;i++)
    freemem.insert(i);
    
  while(1){
    int t;
    if(scanf("%d ",&t)!=1)
      return 0;
    catchup(t);
    char typ;
    scanf(" %c",&typ);
    if(typ=='.'){
      int ad;
      scanf("%d",&ad);
      printf("%c\n",aces(ad));
    }else if(typ=='+'){
      printf("%d\n",aloc());
    }else{
      return 0;
    }
  }
  return 0;
}
