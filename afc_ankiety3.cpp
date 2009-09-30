#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<map>
#include<vector>
#include<string>
#include<set>
using namespace std;
int main(){
  map<int,int> odp[2];
  while(!feof(stdin)){
    int pytanie,odpowiedz,user;
    scanf("%*d, %d, %d, %d",&pytanie,&odpowiedz,&user);
    if(feof(stdin))break;
    if(pytanie==4 || pytanie==10){
      odp[pytanie==10][user]=odpowiedz;
    }
  }
  map< pair<int,int> ,int > wyniki;
  for(map<int,int>::iterator it=odp[0].begin();it!=odp[0].end();++it){
    int user=it->first;
    int odp1=it->second;
    int odp2=odp[1][user];
    printf("odp2=%d\n",odp2);
    wyniki[make_pair(odp1,odp2)]++;
  }
  for(map< pair<int,int> ,int >::iterator it=wyniki.begin();it!=wyniki.end();++it){
    printf("Wariant %d w pytaniu 4 oraz %d w pytaniu 10 wybralo %d osob\n",it->first.first,it->first.second,it->second);
  }
  system("PAUSE");
}
