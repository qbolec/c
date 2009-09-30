#include<cstdio>
#include<iostream>
using namespace std;
typedef unsigned long long uint64;
uint64 MAX_D=1LL<<63;
const int SIZE=7;
struct bn{
  uint64 digit[SIZE];
  int len;
  bn(int x=0){
    for(int i=SIZE;i--;)
      digit[i]=0;
    len=1;
    digit[0]=x;
  }
  void add(const bn & x){
    uint64 r=0;
    int i;
    for(i=0;(i < x.len) || r;i++){
      digit[i]+=r+x.digit[i];
      if(digit[i]>=MAX_D){
        digit[i]-=MAX_D;
        r=1;
      }else
        r=0;
    }
    if(i>len)
      len=i;
  }
  void inc(){
    int i;
    for(i=0;;i++){
      digit[i]++;
      if(digit[i]>=MAX_D)
        digit[i]-=MAX_D;
      else{        
        i++;
        break;      
      }
    }
    if(i>len)
      len=i;  
  }
  void shr(){
    for(int i=len;i--;){
      if(i&&digit[i]&1)
        digit[i-1]|=MAX_D;
      digit[i]>>=1;    
    }  
    if(len>1 && !digit[len-1])
      len--;
  }
  bool ge(const bn& x)const{
    if(len!=x.len)
      return len>x.len;    
    for(int i=len;i--;)
      if(digit[i]!=x.digit[i])
        return digit[i]>x.digit[i];
    return true;
  }
  bool ne(const bn & x)const{
    if(len!=x.len)
      return true;    
    for(int i=len;i--;)
      if(digit[i]!=x.digit[i])
        return true;
    return false;  
  }
};
bn tab[201][201];
int lastm=-1;
int lastn=-1;
void solve(){
  int n,m;
  scanf(" %d %d",&m,&n);

  if(m==lastm && n==lastn){  
  }else{
    for(int j=n;j<=m;j++)
      tab[n][j]=bn(1);
    tab[n][n-1]=bn(0);
    for(int i=n-1;i>0;i--){
      tab[i][m]=bn(1);
      for(int j=m-1;j>=i;j--){
      //tab[i][j]= suma po k >= j tab[i+1][j]
        tab[i][j]=tab[i][j+1];
        tab[i][j].add(tab[i+1][j]);
      }
      tab[i][i-1]=bn(0);
    }
    lastm=m;
    lastn=n;    
  }

  bn min(1);
  bn max=tab[1][1];
  for(int i=2;i<=m;i++)
    max.add(tab[1][i]);
  char text[1023];
  scanf(" 0.%s",text);  
  for(int p=0;text[p] && min.ne(max);p++ ){
    if(text[p]=='1'){
      min.add(max);
      min.shr();
      min.inc();
    }else{
      max.add(min);
      max.shr();
    }    
  }
  bn sum(0);
  int last=1;
  for(int p=1;p<=n;p++){
    bn ts=sum;
    for(int j=last;j<=m;j++){
      ts.add(tab[p][j]);
      if(ts.ge(min)){
        if(p>1)
          printf(" %3d",j);
        else
          printf("%3d",j);
        last=j;        
        break;
      }
      sum=ts;
    }
    if(p%20==0 )
      printf("\n");
  }
  printf("\n");
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    solve(); 
    if(t)
      printf("\n");
  } 
  return 0;
}
