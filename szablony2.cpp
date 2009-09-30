#include<vector>
#include<cstdio>
using namespace std;
char text[1000000];
int match[1000000];//dlugosc szablonu jaki mozna przylozyc poczawszy od pozycji text[i...]=text[0...match-1]
int next[1000000];
int prev[1000000];
vector<int> lista[1000000];
#define FOR(x,c) for(typeof(c.begin()) x=c.begin();x!=c.end();++x)
int main(){
  scanf("%s",text);
  int len=0;
  while(text[len])
    len++;
  int last=0;
  int fb=1;//first bad character
  match[0]=len;
  for(int r=1;r<=len;r++)
    if(r>=fb){
      for(match[r]=0;text[match[r]]==text[fb];match[r]++,fb++);
      last=r;
      fb=r+match[r];
    }else if(r+match[r-last]<fb)
      match[r]=match[r-last];
    else if(r+match[r-last]>fb)
      match[r]=fb-r;
    else{
      for(match[r]=match[r-last];text[match[r]]==text[fb];match[r]++,fb++);
      last=r;
      fb=r+match[r];
    }                      
  for(int p=0;p<=len;p++){
    next[p]=p<len ? p+1 : len;
    prev[p]=p ? p-1 : 0;
    lista[ match[p] ].push_back(p);
  }
  int max=1;
  for(int w=1;w<=len;w++){
    FOR(c,lista[w-1]){
      max >?= next[*c]-prev[*c];
      prev[next[*c]]=prev[*c];
      next[prev[*c]]=next[*c];
    }
    if(max<=w){
      printf("%d\n",w);
      break;
    }
  }
  return 0;
}
