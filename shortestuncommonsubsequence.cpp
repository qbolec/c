#include<cstdio>
#include<cstring>

int jmp[1024+1];
char t[1024];
int c[4];
int cj[4];
void solve(){
  scanf("%s",t);
  int l=strlen(t);
  for(int i=4;i--;){
    c[i]=0;
    cj[i]=l+i;
    t[l+i]='a'+i;
  }
  for(int p=l;p--;){
    int best=1024;
    for(int i=0;i<4;i++)
      if(c[i]<best){
        best=c[i];
        jmp[p]=cj[i];
      }
    c[t[p]-'a']=best+1;
    cj[t[p]-'a']=p;
  }
  int best=1024;
  int pos=0;
  for(int i=0;i<4;i++)
    if(c[i]<best){
      best=c[i];
      pos=cj[i];
    }  
  putchar(t[pos]);  
  for(;pos<l;pos=jmp[pos])
    putchar(t[jmp[pos]]);
  puts("");
}
int main(){
  int z;
  scanf("%d",&z);
  while(z--)
    solve();
  return 0;
}
/*
20
ababababa
c
aaaa
b
ababab
c
ab
c
ba
c
ca
b
c
a
aa
b
bbbbbabcacbabcbac
d
cabcbabcabcbacbacbd
da
abcabdbcbadbbcabdcbadbcbacdbabac
dddddd
*/
