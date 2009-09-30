#include<iostream>
#include<cstdio>
using namespace std;
const int digs=4;
const int maxdig=100000000;
char * kkk[]={
"0",
"0",
"0",
"1",
"4",
"11",
"32",
"89",
"260",
"765",
"2311",
"7067",
"21964",
"68953",
"218750",
"699533",
"2253675",
"7305787",
"23816742",
"78023601",
"256738750",
"848152863",
"2811996971",
"9353366563",
"31204088380",
"104384620069",
"350064856814",
"1176693361955",
"3963752002319",
"13378623786679",
"45239588651120",
"153240818590337",
"519912789574757",
"1766619052715571",
"6011347688123181",
"20482407087281251",
"69877466482844742",
"238676628349960271",
"816152419833089260",
"2793801492359711045",
"9573240168274121860",
"32835189611525865411",
"112724133440468057719",
"387322012171317591555",
"1331949519982339239882",
"4584028190211586682875",
"15788302200638335434997",
"54417417222035985939309",
"187690108045076510973697",
"647788546222807672353959",
"2237184452843397899719966"  
};
struct bignum{
  int dig[digs];
  void operator +=(const bignum & o){
    int r=0;
    for(int i=0;i<digs;i++){
      dig[i]+=o.dig[i]+r;
      if(dig[i]>=maxdig){
        r=1;
        dig[i]-=maxdig;
      }else
        r=0;
    }
  }
  void operator -=(const bignum & o){
    int r=0;
    for(int i=0;i<digs;i++){
      dig[i]-=o.dig[i]+r;
      if(dig[i]<0){
        r=1;
        dig[i]+=maxdig;
      }else
        r=0;
    }
  }
  
  void operator *=(int x){
    int r=0;
    for(int i=0;i<digs;i++){
      long long y=(long long)dig[i]*x+r;
      r=y/maxdig;
      dig[i]=y%maxdig;      
    }
  }
  void operator *=(const bignum & o){
    bignum res=0;
    for(int i=0;i<digs;i++){
      bignum tmp=o;
      tmp*=dig[i];
      for(int j=digs;j--;)
        tmp.dig[j]= j>=i ? tmp.dig[j-i] : 0;
      res+=tmp;
    }
    for(int i=0;i<digs;i++)
      dig[i]=res.dig[i];
  }
  void operator /=(int x){
    long long r=0;
    for(int i=digs;i--;){
      long long y=r*maxdig+dig[i];
      dig[i]=y/x;
      r=y%x;
    }
  }  
  void dump()const{
    int i=digs-1;
    while(i && !dig[i])i--;
    printf("%d",dig[i]);
    while(i--)
      printf("%08d",dig[i]);    
  }
  bignum(int x=0){
    dig[0]=x;
    for(int i=1;i<digs;i++)
      dig[i]=0;
  }
};
bignum kglony[100]={1,1};//konkretnie tylko te spojne:)
bignum choose(bignum n,int k){
  if(k<0)
    return 0;
  bignum ret=1;    
  for(int i=1;i<=k;i++){
    ret*= n;
    ret/= i;
    n-=1;
  }
  return ret;
}
bignum select(bignum n,int k){
  if(!k)
    return 1;
  bignum m=n;
  m+=k-1;
  return choose(m,k);
}
int c[100];
void foreachsubdivision(int n,int todiv,int pos){
  if(pos){    
    for(int i=0;todiv>=0;i++,todiv-=pos){
      c[pos]=i;
      foreachsubdivision(n,todiv,pos-1);
    }
  }else if(!todiv){
    bignum res=1;
    for(int i=1;i<n;i++)
      res*=select(kglony[i],c[i]);
    kglony[n]+=res;
  }
}
int main(){  
  /*
  for(int n=2;n<=50;n++){
    kglony[n]= //ilosc spojnych kglonow o n wierzcholkach
               //spojnych jest dokladnie tyle samo co niespojnych bo sa ich dopelnieniami
               //niespojne skladaja sie z ilustam mniejszych spojnych
               //trzeba sobie zatem wymyslec jakis podzial n na skladniki s1,...,sk
               //powiedzmy ze jest c[i] skladnikow o rozmiarze i, czyli suma c[i]*i = n
               //wtedy musimy wybrac c[i] sposrod klgony[i] ze zwracaniem ale bez rozrozniania
               //tego jest choose( c[i]+kglony[i]-1  , kglony[i]-1 )
               0;
    foreachsubdivision(n,n,n-1);                  
  }
  for(int i=1;i<=50;i++){
    printf("\"");
    kglony[i]-=1;
    kglony[i].dump();    
    puts("\",");
  }*/
  int d;
  scanf("%d",&d);
  while(d--){
    int n;
    scanf("%d",&n);
    puts(kkk[n]);
  }
  return 0;
}
