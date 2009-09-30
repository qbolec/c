#include<cstdio>
#include<cstring>
using namespace std;
char t[1000000];
void solve(){
  gets(t);
  int len=strlen(t);
  for(int i=0;i<len;i++)
    t[i+len]=t[i];  
  int l=0;
  int r=1;
  while(r<len){
    if(l>=r)r=l+1;
    else{
      int i=0;
      while(i<len && t[l+i]==t[r+i])i++;
      if(i==len)
        break;      
      if(t[l+i]<t[r+i])
        r+=i+1;
      else
        l+=i+1;
    }
  }
  printf("%d\n",l+1);
  return;
}
int main(){
  int z;
  scanf("%d ",&z);
  while(z--)
  solve();
  return 0;
}
