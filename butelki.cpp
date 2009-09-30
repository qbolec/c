#include<cstdio>
#include<vector>
using namespace std;
int p1[5];
int p2[5];
int b1[5];
int b2[5];
int n,maxm;
vector<int> v[5];
vector<int> m[5];
int best_value_using_of_mass[77][77][2000];
int best_val[6][1001];
int promo(int c,int u){
  if(u>=p2[c])
    return 100 + b2[c];
  if(u>=p1[c])
    return 100 + b1[c];
  return 100;
}
void solve(){
  scanf("%d %d",&n,&maxm);  
  for(int i=0;i<5;i++){
    scanf("%d %d %d %d",p1+i,b1+i,p2+i,b2+i);
    v[i].clear();
    m[i].clear();
  }
  for(int i=0;i<n;i++){
    int c,val,mass;
    scanf("%d %d %d",&val,&mass,&c);
    c--;
    m[c].push_back(mass);
    v[c].push_back(val);
  } 
  for(int mass=0;mass<=maxm;mass++)
    best_val[0][mass]=0;
  for(int c=0;c<5;c++){
    for(int o=0;o<=v[c].size();o++)
      for(int u=0;u<=o;u++)
        for(int mass=0;mass<=maxm;mass++){
          if(!u){
            if(mass==0)
              best_value_using_of_mass[u][o][mass]=0;
            else
              best_value_using_of_mass[u][o][mass]=-1;
          }else{
            if(u<=o-1)
              best_value_using_of_mass[u][o][mass]=best_value_using_of_mass[u][o-1][mass];
            else
              best_value_using_of_mass[u][o][mass]=-1;
            if(mass>=m[c][o-1] && best_value_using_of_mass[u-1][o-1][mass- m[c][o-1]]>=0)
              best_value_using_of_mass[u][o][mass]>?=best_value_using_of_mass[u-1][o-1][mass- m[c][o-1]]+v[c][o-1];            
          }
        }   
    for(int mass=0;mass<=maxm;mass++)
      best_val[c+1][mass]=best_val[c][mass];
    for(int mass=0;mass<=maxm;mass++){
      int best= -1;
      for(int u=0;u<=v[c].size();u++)
        if(best_value_using_of_mass[u][v[c].size()][mass]>0)
          best>?=best_value_using_of_mass[u][v[c].size()][mass]*promo(c,u);
      if(best>0)
        for(int mas=mass;mas<=maxm;mas++)
          best_val[c+1][mas]>?= best_val[c][mas-mass]+best;        
    }             
  }
  int best=best_val[5][maxm];
  printf("%d.", best/100);
  best%=100;
  if(best<10)
    printf("0%d\n",best);
  else
    printf("%d\n",best);  
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
  return 0;
}
