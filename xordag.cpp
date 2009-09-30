#include<cstdio>
#include<cstdlib> 
const int p=3;
int goals[p*p];

void show(int x){
  for(int r=p*p;r--;)
    printf("%d",(x&(1<<r))?1:0);
  puts("");
}
int s[p*p*p];
bool bgoals[1<<(p*p)];
bool bs[1<<(p*p)];
int limit=0;
int breached=0;
int reached=0;
int goalscount;
bool go(int i,int minb=0){
  if(reached==goalscount){
    puts("");
    puts("FOUND RESULT");
    for(int j=0;j<i;j++)
      show(s[j]);
    return true;
  }
  if(reached>breached){
    puts("");
    breached=reached;
    printf("reached %d:\n",reached);
    /*
    for(int j=0;j<i;j++)
      show(s[j]);    
    */
  }
    /*
  if(i==p*p+2){
    puts("");
    puts("now processing:");
    for(int j=0;j<i;j++)
      show(s[j]);    
  }
  */
  if(limit-i+reached<goalscount)
    return false;
  if(i==limit)return false;
  for(int b=minb;b<i;b++)
    for(int a=0;a<b;a++){
        int r=s[a]^s[b];
        if(bs[r])continue;
                    
        s[i]=r;
        if(bgoals[r])
          reached++;
        bs[r]=true;
        bool res=go(i+1,b);
        bs[r]=false;
        if(bgoals[r])
          reached--;
        if(res)return true;
      
      }
    
  return false;
}
int main(){
  for(int a=0;a<p;a++)
    for(int b=0;b<p;b++){
      int g=0;
      for(int i=0;i<p;i++)
        g|= 1<<(i*p+((a*i+b)%p));
      goals[a*p+b]=g;
      bgoals[g]=true;
    }
  
  for(int i=0;i<p*p;i++)
    bs[s[i]=1<<i]=true;
  goalscount=7;
  printf("GOALS: %d\n",goalscount);
  for(limit=goalscount*(p-1)+p*p-1;limit<=goalscount*(p-1)+p*p;limit++){
    printf("\nusing limit %d\n",limit);
    reached=0;
    if(go(p*p)){
      printf("\n\nReached using %d nodes\n",limit);
      break;      
    }
  }
  system("pause");
}
