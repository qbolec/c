#include<cstdio>
#include<cstring>
#define EXCLUZIF
struct TablicaCzestosci{
  int czestosci[256];
  int escape;//w tej implementacji zawsze 1
  int sum;
  TablicaCzestosci(){
    for(int i=256;i--;)
      czestosci[i]=0;
    sum=escape=1;
  }
  bool seen(unsigned char znak){
    return czestosci[znak];
  }
  void increment(unsigned char znak){
    czestosci[znak]++;
    sum++;
  }
  void mark_xcept(bool * xcept){
    for(int i=0;i<256;i++)
      if(czestosci[i])
        xcept[i]=true;
  }
  void encode(unsigned char znak,float &l, float &r, bool * xcept){ 
    printf("(%c)",znak);
    int sum=escape;
    int c=0;
    for(int i=0;i<256;i++)
      if(!xcept[i])
        sum+= czestosci[i];
    for(int i=0;i<znak;i++)
      if(!xcept[i])
        c+= czestosci[i];
    printf("%d vs %d\n",sum,this->sum);
    float s=r-l;
    r= l + s*(c+czestosci[znak])/sum;
    l= l + s*(c)/sum;
  }
  void encode(unsigned char znak,float &l, float &r){ 
    printf("(%c)",znak);
    int c=0;
    for(int i=0;i<znak;i++)
      c+= czestosci[i];
    float s=r-l;
    r= l + s*(c+czestosci[znak])/sum;
    l= l + s*(c)/sum;
  }
  void encode_escape(float &l, float &r){
    printf("ESC");
    float s=r-l;
    l= l + s*(sum-escape)/sum;
  }  
  void encode_escape(float &l, float &r, bool * xcept){
    printf("ESC");
    int sum=escape;
    for(int i=0;i<256;i++)
      if(!xcept[i])
        sum+= czestosci[i];
    printf("%d vs %d\n",sum,this->sum);        
    float s=r-l;
    l= l + s*(sum-escape)/sum;
  }
};
struct DrzewoKontekstow{
  TablicaCzestosci * tablica;
  DrzewoKontekstow * dzieci[256];
  DrzewoKontekstow * father;
  void encode(unsigned char znak,float & l, float & r){
    if(tablica->seen(znak)){
      tablica->encode(znak, l , r );
    }else{
      tablica->encode_escape( l,r );
      if(father){
        father->encode(znak,l,r);            
      }else{
        printf("[%c]",znak);
        float s=r-l;
        r= l + s* (znak+1)/256;
        l= l + s* (znak)/256;
      }
    }
  }
  void encode(unsigned char znak,float & l, float & r, bool * xcept){
    if(tablica->seen(znak)){
      tablica->encode(znak, l , r, xcept );
    }else{
      tablica->encode_escape( l,r, xcept );
      tablica->mark_xcept(xcept);
      if(father){
        father->encode(znak,l,r,xcept);            
      }else{
        printf("[%c]",znak);
        int sum=0;
        for(int i=0;i<256;i++)
          if(!xcept[i])
            sum++;
        int c=0;
        for(int i=0;i<znak;i++)
          if(!xcept[i])
            c++;            
            
        float s=r-l;
        r= l + s* (c+1)/sum;
        l= l + s* (c)/sum;
      }
    }
  }
  DrzewoKontekstow * find(unsigned char * last){
    if(dzieci[*last])
      return dzieci[*last]->find(last-1);
    return this;
  } 
  void new_context_info(unsigned char * last,unsigned char znak,int limit=3){
    tablica->increment(znak);
    if(*last && limit){
      if(!dzieci[*last])
        dzieci[*last]=new DrzewoKontekstow(this);
      dzieci[*last]->new_context_info(last-1,znak,limit-1);
    }      
  }
  void encode(unsigned char * letter,float &l, float &r){
    DrzewoKontekstow * bestfit=find(letter-1);
#ifdef EXCLUZIF
    bool xcept[256];
    for(int i=0;i<256;i++)
      xcept[i]=false;
    bestfit->encode(*letter,l,r,xcept);
#else
    bestfit->encode(*letter,l,r);
#endif
    new_context_info(letter-1,*letter);    
  } 
  DrzewoKontekstow(DrzewoKontekstow * father=0):father(father){
    for(int i=256;i--;)
      dzieci[i]=0;
    tablica=new TablicaCzestosci();
  }
};

int main(){
  DrzewoKontekstow * root=new DrzewoKontekstow();
  root->tablica->increment(';');
  root->tablica->increment('A');
  root->tablica->increment('C');
  root->tablica->increment('E');  
  root->tablica->increment('H');
  root->tablica->increment('T');  
  unsigned char text[1024];
  scanf("%s",text+1);//nulle z obu stron
  int len=strlen((const char*)(text+1));
  float l=0;
  float r=1;
  int bits=0;
  for(int i=1;i<=len;i++){
    root->encode(text+i,l,r);
    while(l>0.5 || r<0.5){
      if(r<0.5){
        bits++;
        printf(" r < 0.5 mozna wypisac 0\n");
        l*=2;
        r*=2;
      }
      if(l>0.5){
        bits++;
        printf(" l > 0.5 mozna wypisac 1\n");
        l*=2;
        r*=2;
        l-=1;
        r-=1;
      }
    }
  }
  printf("przedzial (%.8f %.8f) zawiera 0.5 wiec mozemy wypisac 1 albo go nie wypisywac...\n",l,r);
  printf("uzyto %d bitow\n",bits);
  
  return 0;
}
