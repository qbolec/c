#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
inline bool leq(int a1, int a2,   int b1, int b2) { // lexic. order for pairs
  return(a1 < b1 || a1 == b1 && a2 <= b2); 
}                                                   // and triples
inline bool leq(int a1, int a2, int a3,   int b1, int b2, int b3) {
  return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3)); 
}
int cnt=0;
// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
static void radixPass(int* a, int* b, int* r, int n, int K) 
{ // count occurrences
  cnt++;
  int* c = new int[K + 1];                          // counter array
  for (int i = K+1;  i--;  ) c[i] = 0;         // reset counters
  for (int i = n;  i--;  ) c[r[a[i]]]++;    // count occurences
  for (int i = 1;  i <= K;  i++) c[i]+=c[i-1]; // prefix sum  
  for (int i = n;  i--;  ) b[--c[r[a[i]]]] = a[i];      // sort
  delete [] c;
}

// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void suffixArray(int* s, int* SA,const int n,const int K) {
  const int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2, nn0n1=n+n0-n1; 
  int* s12  = new int[n02 + 3];  s12[n02]= s12[n02+1]= s12[n02+2]=0; 
  int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
 
  // generate positions of mod 1 and mod  2 suffixes
  // the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
  int * sp = s12;
  for (int i=1;  i < nn0n1;  i+=2){
    *sp++=i++;
    *sp++=i;    
  }
  if(*--sp >= nn0n1) *sp=0;
  // lsb radix sort the mod 1 and mod 2 triples
  radixPass(s12 , SA12, s+2, n02, K);
  radixPass(SA12, s12 , s+1, n02, K);  
  radixPass(s12 , SA12, s  , n02, K);
  // find lexicographic names of triples
  int name = 0, c0 = -1, c1 = -1, c2 = -1;
  for (int i = 0;  i < n02;  i++) {
    if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) { 
      name++;  
      c0 = s[SA12[i]];  
      c1 = s[SA12[i]+1];  
      c2 = s[SA12[i]+2];
    }
    if (SA12[i] % 3 == 1) { s12[SA12[i]/3]      = name; } // left half
    else                  { s12[SA12[i]/3 + n0] = name; } // right half
  }

  // recurse if names are not yet unique
  if (name < n02) {
    suffixArray(s12, SA12, n02, name);
    // store unique names in s12 using the suffix array 
    for (int i = n02;  i--;) s12[SA12[i]] = i + 1;
  } else // generate the suffix array of s12 directly
    for (int i = n02;  i--;) SA12[s12[i] - 1] = i; 


  int* s0   = new int[n0];
  int* SA0  = new int[n0];
  // stably sort the mod 0 suffixes from SA12 by their first character
  for (int i=0, j=0;  i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
  radixPass(s0, SA0, s, n0, K);
  delete [] s0; 
  
  
  // merge sorted SA0 suffixes and sorted SA12 suffixes
  for (int p=0,  t=n0-n1,  k=0;  k < n;  k++) {
#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
    int i = GetI(); // pos of current offset 12 suffix
    int j = SA0[p]; // pos of current offset 0  suffix
    if (SA12[t] < n0 ? 
        leq(s[i],       s12[SA12[t] + n0], s[j],       s12[j/3]) :
        leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0])){ // suffix from SA12 is smaller
      SA[k] = i;  t++;
      if (t == n02) { // done --- only SA0 suffixes left
        for (k++;  p < n0;  p++, k++) 
          SA[k] = SA0[p];
      }
    } else { 
      SA[k] = j;  p++; 
      if (p == n0)  { // done --- only SA12 suffixes left
        for (k++;  t < n02;  t++, k++) 
          SA[k] = GetI(); 
      }
    }  
  } 
  delete [] s12; delete [] SA12; delete [] SA0; 
}

template<class T>
int maxCyclic(T *s,int n){
  int l=0;//utrzymujemy l<r, l to jedyna sensowna liczba mniejsza od r
  int r=1;
  while(r<n){
    int ll=l;
    int rr=r;
    while(s[ll]==s[rr]){
      if(++ll==n)ll=0;
      if(++rr==n)rr=0;
      if(ll==l)
        return l;
    }
    if(s[ll]>s[rr]){
      if(ll<l)
        return r;      
      l=ll+1;
      if(l<=r)//boost:D
        l=r++;      
    }else{
      if(rr<r)
        return l;
      r=rr+1;
    }      
  }
  return l;
}
void cyclicArray(int * s,int * CA,int n,int K){
  s[n]=s[n+1]=s[n+2]=0;
  for(int i=n;i--;)
    s[i]++;
  //aby nie modyfikowac algorytmu suffixArray
  //postanowilem poprostu znalesc maxymalne przesuniecie cykliczne
  //a potem tak obrocic stringa zeby tam gdzie jest null bylo minimalne przesuniecie cykliczne:)
  int mc=maxCyclic(s,n);
  //dzieci pamietajcie: obrot to zlozenie dwoch symetrii
  reverse(s,s+n);
  reverse(s,s+n-mc);    
  reverse(s+n-mc,s+n);
  suffixArray(s,CA,n,K+1);
  for(int i=n;i--;){
    CA[i]+=mc;
    if(CA[i]>=n)
      CA[i]-=n;
  }
  reverse(s+n-mc,s+n);
  reverse(s,s+n-mc);    
  reverse(s,s+n);  
  for(int i=n;i--;)
    s[i]--;

}
int codeBW(const unsigned char * input,unsigned char *output,int n){
  int * s=new int[n+3];
  int * CA=new int[n+3];
  for(int i=n;i--;)
    s[i]=input[i];
  s[n]=s[n+1]=s[n+2]=0;
  cyclicArray(s,CA,n,255);
  for(int i=0;i<n;i++)
    output[i]= input[ CA[i]?(CA[i]-1):(n-1) ] ;  

  int ret=0;
  for(int i=n;i--;)
    if(!CA[i]){
      ret=i;
      break;
    }
  delete[] s;
  delete[] CA;
  return ret;
}
void codeMTF(const unsigned char * input,unsigned char * output,int n){
  int letter[256];
  int pos[256];
  for(int i=0;i<256;i++)
    pos[i]=letter[i]=i;
  for(int i=0;i<n;i++){
    int k=pos[input[i]];
    output[i]=k;
    for(int j=k;j--;)
      letter[j+1]=letter[j];
    letter[0]=input[i];
    for(int j=k+1;j--;)
      pos[letter[j]]=j;
  }
}
double entropy(const unsigned char * data,int n){
  int s[256];
  for(int i=0;i<256;i++)s[i]=0;
  for(int i=n;i--;)
    s[data[i]]++;
  //for(int i=0;i<10;i++)
    //printf("stat of %d is %d\n",i,s[i]);
//  printf("total length %d\n",n);
  double P=0.0;
  for(int i=0;i<256;i++){
    if(s[i])
      P-=log2(s[i])*s[i];
  }
  P/=n;
  P+=log2(n);
  return P;
}
const int maximalLength=10000000;
unsigned char dupa[maximalLength];
unsigned char dups[maximalLength];
unsigned char dupk[maximalLength];
unsigned char dupz[maximalLength];
int pairstats[256][256];
int pairsvalue(unsigned char * f,unsigned char *t){
  int ret=0;
  for(unsigned char * i=f+1;i<t;i++)
    ret+=pairstats[i[-1]][i[0]];
  return ret;
}
void optpairs(unsigned char * f,unsigned char *t){
  int bestc=pairsvalue(f,t);
  string best(f,t);
  //sort(f+1,t-1);
  int l=10000;
  bool need=true;
  while(need){
    need=false;
  for(int i=best.length()-1;i--;)
    for(int j=i;j-->1;){
      swap(f[i],f[j]);
      int c=pairsvalue(f,t);
      if(c>bestc){
        best=string(f,t);
        bestc=c;
        need=true;
      }else{
        swap(f[i],f[j]);
      }
    }
  }
  for(int i=best.length();i--;)
    f[i]=best[i];
  while(++f<t)
    pairstats[f[-1]][f[0]]++;    
}
void sortlettersinwords(unsigned char * dupa){
  while(*dupa){
    while(*dupa && !('a'<=*dupa && *dupa<='z' || 'A'<=*dupa && *dupa<='Z'))dupa++;
    unsigned char * e=dupa;
    while(*e && ('a'<=*e && *e<='z' || 'A'<=*e && *e<='Z'))e++;
    if(dupa+1<e-1){
//      for(unsigned char * i=dupa+2;i<e-1;i+=2)
//        sort(i-1,i+1);
//    sort(dupa+1,e-1);
      optpairs(dupa,e);
    }
    dupa=e;
  }
}
int main (int argc,char * args[]){    
  int len=fread(dupa,1,maximalLength-1,fopen(args[1],"rb"));
 // gets(dupa);
 // int len=strlen(dupa);
  /*
  int mc=maxCyclic(dupa,len);
  printf("%d %s",mc,dupa+mc);
  return 0;*/
 // sortlettersinwords(dupa);

//  reverse(dupa,dupa+len);
 
  printf("przed transformacja:\t %.10lf (= %d)\n",entropy(dupa,len),(int)(len*entropy(dupa,len)+7)/8);
  int res=codeBW(dupa,dups,len);
  printf("%d radix passes\n",cnt);
  printf("przed MTF:\t %.10lf (= %d)\n",entropy(dups,len),(int)(len*entropy(dups,len)+7)/8);
//  printf("%d %s\n",res,dups);
  codeMTF(dups,dupa,len);
//  for(int i=0;i<len;i++)
//    printf("%d ",(int)dupa[i]);
  printf("po transformacji:\t %.10lf (= %d)\n",entropy(dupa,len),(int)(len*entropy(dupa,len)+7)/8);
  int j=0;
  int z=0;
  for(int i=0;i<len;){
    dupk[j++]=dupa[i];
    if(!dupa[i]){
      dupz[z]=0;
      while(i<len  && !dupa[i] && dupz[z]!=255 ){
        i++;
        dupz[z]++;
      }
      z++;
    }else 
      i++;
  }
  printf("strumienie maja dlugosci: %d i %d\n", j,z);
  printf("strumien danych:\t %.10lf (= %d) \n",entropy(dupk,j),(int)(j*entropy(dupk,j)+7)/8);
  printf("strumien powtorzen zer:\t %.10lf (= %d) \n",entropy(dupz,z),(int)(z*entropy(dupz,z)+7)/8);
  printf("razem:\t %d bajtow \n",(int)(j*entropy(dupk,j)+7)/8+(int)(z*entropy(dupz,z)+7)/8);
}
