#include<cstdio>
const int logH=12;
const int H=1<<logH;
const int N=H*H;
struct game{
  int p[H*2];
  int level;
  int moves;
  void deb(){
    printf("level %d, %d moves so far.\n",level,moves);
    for(int i=0;i<level*2-1;i++)
      if(i%2)
        printf("%c ",'a'+p[i]);
      else
        printf("%d ",p[i]);
    printf("\n");
  }
  void step(){
    int adversary=0;
    for(int i=1;i<level;i++)
      if(p[i*2]<p[adversary*2])
        adversary=i;
    for(int i=1;i<level;i++)
      p[i*2-1]++;
    level++;
    for(int i=level*2-2;i>adversary*2+2;i--)
      p[i]=p[i-2];
    p[adversary*2+1]=0;
    p[adversary*2+2]=0;
    if(p[adversary*2]>1){
      int h=(p[adversary*2]+1)/2;
      p[adversary*2]-=h;
      p[adversary*2+2]+=h;
    }else{
      int l=adversary*2;
      int r=adversary*2;
      for(int h=1;h<level;h++){
        while(l>0 && p[l-1]<=h) l-=2;
        while(r<level*2-2 && p[r+1]<=h) r+=2;
        int bots=0;
        for(int i=l;i<=r;i+=2)
          bots+=p[i];
        int slots=(r-l)/2+1;
        int ratio=bots/slots;
        if(ratio>=H){
          for(int i=l;i<=r;i+=2){
            p[i]=bots/slots;
            bots-=p[i];
            slots--;
          }
          moves+=h;
  //        printf("forced %d rebalance\n",h);
          break;
        }
      }      
    }
    
  }
  game(){
    p[0]=N;
    level=1;
    moves=0;
  }
};
int main(){
  game g;
  for(int i=1;i<H;i++){
//    g.deb();
    g.step();
  }
  printf("reached level %d using %d bots in %d movements\n",g.level,N,g.moves);
}
