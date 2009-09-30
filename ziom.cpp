#include<cstdio>
#include<cstdlib>
#include<ctime>
char* txt[]={
  "Jestes spoko ziom",
  "Masz wytrawny skill",
  "Robisz mi dobrze sama obecnoscia",
  "Powala mnie Twoj byt",
  "Naprawde, dajesz rade"
};
int main(){
  srand(time(0));
  puts(txt[rand()%5]);
  system("PAUSE");
}
