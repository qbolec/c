#include<cstdio>
//Ilosc nieizomorficznych kolorowan K_n przy pomocy M kolorow modulo P
using namespace std;
int n,m,p;
int maxinverted=0;
long long LIMIT;
int inverted[54*54];// i^-1 %p
int total=0;//wynik
int mk[54*54];//m ^ k % p
int a[54];//dlugosc cyklu
int ak[53];//ilosc cykli o tej dlugosci
int gcd[54][54];//gcd[i][j]
int gcd_foo(int a,int b){
  while(b){
    int c=b;
    int d=a%b;
    if(!d)
      return c;
    a=d;
    b=c%d;  
  }
  return a;
}
int gcd_ex(int a,int c,int w,int z){
  while(w){
     int r=z/w;
     z%=w;
     c-=r*a;
     if(!z)
      return a;
     int l=w/z;
     w%=z;
     a-=l*c;
  }
  if(c<0)c+=p;
  if(c>=p)c-=p;
  return c;
}
int inv(int x){
  return gcd_ex(1,0,x,p);
}
int pos=-1;
void generuj(int num,int min=1,int ww=0,long long div=1){
  pos++;
  for(int i=min;i<= num; i++){
    a[pos]=i;
    int w=i>>1;
    for(int j=pos;j--;)
      w+=gcd[i][a[j]]*ak[j];          
    int ws=ww+w;
    long long divdiv=div;
    int n=num-i;
    int j;
    for(j=1; n>i; j++,n-=i){
      divdiv*= i*j;
      if(divdiv>=(((1LL<<63)-1) / 53 ))divdiv%=p;
      ak[pos]=j;    
      generuj(n,i+1,ws, divdiv);
      ws+= i*j+w;
    }    
    if(n==i){
      divdiv*= i*j;
      if(divdiv>=(((1LL<<63)-1) / 53 ))divdiv%=p;
      ws+= i*j+w;      
      j++;
      n=0;
    }  
    if(!n){
      divdiv*= i*j;
      if(divdiv>=(((1LL<<63)-1) / 53 ))divdiv%=p;      
      total=((long long)inv(divdiv%p)*mk[ws]+total)%p;      
    }  
    
  }
  pos--;
}/*
void generuj(int num,int min=1,int ww=0,long long div=1){
  pos++;
  for(int i=min;i<= num; i++){
    a[pos]=i;
    int w=i>>1;
    for(int j=pos;j--;)
      w+=gcd[i][a[j]]*ak[j];          
    int ws=ww+w;
    long long divdiv=div;
    int n=num-i;
    for(int j=1; n>=0; j++,n-=i){
      divdiv*= inverted[i*j];
      if(divdiv>=LIMIT)divdiv%=p;
      if(!n){
        total=(divdiv*mk[ws]+total)%p;//tu brakuje jednego modulo ale z jakiegos powodu dziala;)
      }else if(n>i){      
        ak[pos]=j;        
        generuj(n,i+1,ws, divdiv);
      }
      ws+= i*j+w;
    }    
  }
  pos--;
}*/
int main(){
  scanf("%d %d %d",&n,&m,&p);
  /*
  policzymy sobie ile jest punktow stalych danej permutacji
  bo pan Burnside powiedzial ze jak chcemy policzyc ilosc istotnie roznych rzeczy
  to trzeba popatrzec ile mamy roznych sposobow unifikowania 
  oraz dla kazdego sposobu unifikowania policzyc ile rzeczy sie mu nie poddaje
  i wynik to
  1/ n!  *  suma po permutacjach fixedpoint(permutacji)
  Jasne jest dla coponiektorych ze istotne jest tylko rozbicie permutacji na cykle
  jesli permutacja n ma cykle o dlugosciach a[1]<=...<=a[k] to jej punkty stale...
  ..stale sa jak kazda krawedz jest stala:)  
  krawedz moze zachaczac o dwa cykle wtedy musi wspoldzielic kolor z lcm(a[i],a[j]) krawedziami
  moze tez zawierac sie calkowicie w jednym cyklu i z reguly oznacza to ze ma ten sam kolor co a[i] krawedzi
  chyba ze a[i] jest parzyste wtedy bycmozne jest krawedzia ktora po obrocie o 180* wraca na sama siebie
  wtedy w jej towarzystwie jest a[i]/2 krawedzi
  zasadniczo interesuje nas ile roznych klas abstrakcji jest w swiecie tych krawedzi
  no wiec dla kazdej pary cykli istnieje gcd(a[i],a[j]) roznych grupek
  zas dla kazdego cyklu o nieparzystej dlugosci jest ich (a[i]-1)/2
  a dla kazdego cyklu o parzystej dlugosci jest ich a[i]/2, tak czy owak a[i]>>1
  majac zatem rozbicie a[1]<=...<=a[k] mozemy powiedziec ze istnieje
  m^( sum a[i]/2 + sum gcd(a[i],a[j]) )  punktow stalych
  pytanie jeszcze ile jest permutacji ktore maja cykle takiej dlugosci
  mysle ze od biedy jest ich tyle co:
    n!
    ------------------
    PI(a[i]) (ilosc takich samych a[i])!
    
  z racji tego ze na koniec mielismy wszystko dzielic przez silnie
  to ja sobie daruje
  */
  mk[0]=1;
  for(int i=1;i<=n*n+n;i++)
    mk[i]=((long long)mk[i-1]*m)%p;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=i;j++)
      gcd[i][j]=gcd[j][i]=gcd_foo(i,j);
/*
  for(int i=1;i<=n;i++)
    maxinverted >?= inverted[i]=inv(i);
  LIMIT = ((1LL <<63 ) -1) /maxinverted;
  */
  generuj(n);
  int res=total%p;
  printf("%d\n",res);
}
