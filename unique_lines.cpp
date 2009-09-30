#include<set>
#include<string>
using namespace std;
int main(){
  set<string> seen;
  while(!feof(stdin)){
    char line[1024];
    gets(line);
    string l=line;
    if(seen.insert(l).second==true)
      puts(line);
  }
}
