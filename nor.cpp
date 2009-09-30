#include<cstdio>
#include<vector>
using namespace std;
bool val[300100];
int left[300100];
int right[300100];
char res[100100];
int n,m,nm;


int check(int z){
  for(int i=0;i<z;)
    val[++i]=false;
  
  for(int i=z;i<n;)
    val[++i]=true;
  
  for(int i=n+1;i<=nm;i++)
    val[i]=!(val[left[i]]& val[right[i]]);
  return val[nm];
}
void trans(int & x){
  if(x<0)
    x= -x;
  else
    x+=n;
}
void solve(){  
  scanf("%d %d",&n,&m);
  res[n]=0;
  nm=n+m;
  for(int i=n;i--;)
    res[i]='0';      
  for(int i=n+1;i<=nm;i++){
    scanf("%d %d",left+i,right+i);
    trans(left[i]);
    trans(right[i]);    
  }
  if(check(0)!=check(n)){
    int keep=val[nm];
    int a=0;
    int b=n;
    while(a+1<b){
      int c=(a+b)/2;
      if(check(c)==keep){
        b=c;
      }else{
        a=c;
      }
    }
    for(int i=a;i<n;i++)
      res[i]='1';
    res[a]='x';
  }
  puts(res);
}
int main(){
  int d;
  scanf("%d",&d);
  while(d--)
    solve();
}
