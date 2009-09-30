#include<cstdio>
#include<cstring>
#include<string>
#include<set>
using namespace std;
set<string> words;
int wc=0;
int gc=0;
int gcd(int a,int b){
  if(!b)return a;
  return gcd(b,a%b);
}
int main(){

  while(1){
    char text[1024];
    char org[1024];
    gets(text);
    strcpy(org,text);
    if(feof(stdin)){
      int g=gcd(wc,gc);
      printf("%d / %d\n",wc/g,gc/g);
      return 0;
    }    
    int start=-1;
    int len=strlen(text);
    for(int i=0;i<=len;i++){
      if('A'<=text[i] && text[i]<='Z')
        text[i]-='A'-'a';
      if('a'<=text[i] && text[i]<='z'){
        if(start<0)
          start=i;
      }else if(start>=0){
        text[i]=0;
        org[i]=0;
        if(!strcmp(org+start,"BULLSHIT")){
          wc+=words.size();
          words.clear();
          gc++;
        }else{
          words.insert( string(text+start));
        }
        start=-1;        
      }      
    }
  }
}
