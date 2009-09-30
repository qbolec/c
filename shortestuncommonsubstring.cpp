#include<cstdio>
#include<cstring>
const int MAX_LEN=2000000;
char t[MAX_LEN];
struct node{
  int suf;
  int children[4];
  int h;
  void clear(){
    for(int i=4;i--;)children[i]=-1;
    h=0;
  }
};
node nodebank[MAX_LEN];
int nb=0;
void go(int id){
  for(int i=0;i<4;i++)
    if(nodebank[id].children[i]<0){
      nodebank[id].h=0;
      return;
    }
  nodebank[id].h=1024;
  for(int i=0;i<4;i++)
    if(nodebank[id].children[i]>=0){
      go(nodebank[id].children[i]);
      nodebank[id].h<?= nodebank[nodebank[id].children[i]].h+1;
    }      
}
void go2(int id){
  if(!nodebank[id].h){
    for(int i=0;i<4;i++)
      if(nodebank[id].children[i]<0){
        putchar('a'+i);
        puts("");
        return;
      }
  }else{
    for(int i=0;i<4;i++)
      if(nodebank[id].children[i]>=0 && nodebank[id].h== nodebank[nodebank[id].children[i]].h+1){
        putchar('a'+i);
        go2(nodebank[id].children[i]);
        return;
      }
  }
}
void solve(){
  scanf("%s",t);
  nb=0;
  nodebank[0].clear();
  nodebank[0].suf=-1;
  nb++;
  int root=0;
  int len=strlen(t);
  int l=0;
  int lc=1;
  for(;lc+l-1 <= len;l++)
    lc*=4; 
  for(int i=0;i<len;i++){
    int a=t[i]-'a';
    int r=nodebank[root].suf;
    nodebank[root].children[a] = nb;
    root=nb;
    nodebank[nb].clear();
    nb++;
    while(1){
      if(r<0){
        nodebank[nb-1].suf=0;
        break;
      }
      if(nodebank[r].children[a]>=0){
        nodebank[nb-1].suf=nodebank[r].children[a];
        break;
      }else{
        nodebank[nb-1].suf=nb;
        nodebank[r].children[a]=nb;
        nodebank[nb].clear();
        nb++;        
      }
      r=nodebank[r].suf;
    }
    if(i>l)root=nodebank[root].suf;
  }
  go(0);
  go2(0);
}
int main(){
  int z;
  scanf("%d",&z);
  while(z--)
    solve();
  
}
