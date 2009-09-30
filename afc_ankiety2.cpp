#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<map>
#include<vector>
#include<string>
#include<set>
using namespace std;
int main(){
  map<string,map<string,int> > wyniki;
  while(!feof(stdin)){
    char l[1024];
    gets(l);
    if(feof(stdin))break;
    int i;
    for(i=0;l[i]!='\'';i++);
    i++;
    int j;
    for(j=i;l[j]!='\'';j++);
    l[j]=0;
    string pytanie=l+i;
    for(i=j+1;l[i]!='\'';i++);
    i++;
    for(j=i;l[j]!='\'';j++);
    l[j]=0;
    string odpowiedz=l+i;
    wyniki[pytanie][odpowiedz]++;
  }
  for(map<string,map<string,int> >::iterator it=wyniki.begin();it!=wyniki.end();++it){
    int total=0;
    for(map<string,int>::iterator it2=it->second.begin();it2!=it->second.end();++it2){
      total+=it2->second;
    }
    printf("Pytanie %s  (uzyskano na nie %d odpowiedzi)\n",it->first.c_str(),total);
    for(map<string,int>::iterator it2=it->second.begin();it2!=it->second.end();++it2){
      printf("\tOdpowiedz %s wybralo %d osob, czyli %d procent\n",it2->first.c_str(),it2->second,100*it2->second/21);
    }
  }
  system("PAUSE");
}
