#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<map>
#include<vector>
#include<string>
#include<set>
using namespace std;
int main(){
  map<int,map<int,int> > wyniki;
  while(!feof(stdin)){
    int pytanie,odpowiedz;
    scanf("%*d, %d, %d, %*d",&pytanie,&odpowiedz);
    if(feof(stdin))break;
    wyniki[pytanie][odpowiedz]++;
  }
  for(map<int,map<int,int> >::iterator it=wyniki.begin();it!=wyniki.end();++it){
    int total=0;
    for(map<int,int>::iterator it2=it->second.begin();it2!=it->second.end();++it2){
      total+=it2->second;
    }
    printf("Pytanie nr. %d  (uzyskano na nie %d odpowiedzi)\n",it->first,total);
    for(map<int,int>::iterator it2=it->second.begin();it2!=it->second.end();++it2){
      printf("\tOdpowiedz %d wybralo %d osob, czyli %d procent\n",it2->first,it2->second,100*it2->second/21);
    }
  }
  system("PAUSE");
}
