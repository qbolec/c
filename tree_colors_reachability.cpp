#include<cstdio>
#include<cstdlib>
char c[1<<20+2];
void build_stripes(int k){
  for(int i=0;i<k;i++){
    for(int j=1<<i;j< 1<<i+1;j++)
      c[j]=i;
  }
}
void build_rec(int i,int t,int k,int s){
  if(i< 1<<k){
    c[i]=t;
    t++;
    if(t==k){
      t=s;
    }
    build_rec(i*2,t,k,s);
    build_rec(i*2+1,t,k,s);
  }
}
void build_stripes_cyc(int k){
  int s;
  for(s=0;1<<s < k-s; s++);
  build_stripes(s);
  for(int j=1<<s;j < 1<<s+1;j++)
    build_rec(j,s+j-(1<<s),k,s);
}
void build_rand(int k,int i,int v){
  if(i< 1<<k){
    int r;
    do{
      r=rand()%k;
    }while(v&1<<r);
    c[i]=r;
    build_rand(k,i*2,v|1<<r);
    build_rand(k,i*2+1,v|1<<r);
  }
}
void build_rand(int k){
  build_rand(k,1,0);
}
int check(int i,int k,int v){
  if(1 < 1<<k){
    if(1<<c[i]&v){
      return
        1 +
        check(i*2,k,v^1<<c[i]) +
        check(i*2+1,k,v^1<<c[i]);
    }else
      return 1;
  }else
    return 0;
}
void process(int k){
  int b[32]={};
  long long t[32]={};
  int h[32]={};
  for(int v=0;v<1<<k;v++){
    int s=check(1,k,v);
    int z=0;
    for(int i=0;i<k;i++)
      if(v&1<<i)
        z++;
    t[z]+=s;
    b[z]>?=s;
    h[z]++;
  }
  for(int i=0;i<=k;i++){
    printf("%d colors (%d) reach: %d  (%d)\n",i,h[i],b[i],t[i]/h[i]);
  }
}
double reach(int k, int f){
  if(!f)return !!k;
  return (double)f*2*reach(k-1,f-1)/k + 1;
}
void expect(int k){
  for(int i=0;i<=k;i++){
    printf("%d colors should reach: %.1lf\n",i,reach(k,i));
  }
}
int main(){
  srand(43);
  build_stripes(20);
  process(20);
  build_stripes_cyc(20);
  process(20);
  expect(20);
  while(true){
  build_rand(20);
  process(20);

  system("PAUSE");
}
}
