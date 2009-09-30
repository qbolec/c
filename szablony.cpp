#include<vector>
#include<cstdio>
using namespace std;
char text[1000000];
int dsbp[1000000];//dlugosc sufixu wlasciwego slowa [0..i-1] bedacego prefixem text
int match[1000000];//dlugosc szablonu jaki mozna przylozyc poczawszy od pozycji text[i...]=text[0...match-1]
int next[1000000];
int prev[1000000];
vector<int> lista[1000000];
#define FOR(x,c) for(typeof(c.begin()) x=c.begin();x!=c.end();++x)
int main(){
  scanf("%s",text);
  int len=0;
  while(text[len]){
    match[len]=-1;
    len++;
  }
  dsbp[0]=0;
  dsbp[1]=0;
  for(int i=1;i<len;i++){
    int k=dsbp[i];
    while(k && text[k]!=text[i])
      k=dsbp[k];
    dsbp[i+1]= text[k]==text[i] ? k+1 : 0;
  }
  int m=0;// text[l..r]==text[0..m-1]
  match[0]=len;
  for(int r=1;r<=len;r++){
    while(m && text[r]!=text[m]){
      match[r-m]=m;
      m=dsbp[m];
    }
    if(text[r]==text[m])
      m++;
    else{
      match[r]=0;
      m=0;
    }
  }
  int last=0;
  for(int p=0;p<=len;p++){
    if(match[p]==-1){
      match[p]= match[p-last] <? (match[last]-p+last);
    }else
      last=p;
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
