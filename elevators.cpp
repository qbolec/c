#include<cstdio>
int start[110];
int jmp[110];
int reach[110];
int process[110];
int pc,wc;
int f;
int gcd_ex(int x,int p,int a,int b){
  if(!x) return b;
  int r=p/x;
  return gcd_ex(p%x,x,b-a*r,a);
}
long long rev(int x,int p){
   int z= gcd_ex(x,p,1,0);
   return (z+p) %p;
}
int gcd(int a,int b){
  if(!b)return a;
  return gcd(b,a%b);
}
bool solve(int a,int x,int b,int y,int f,int t){
  if(f>=t)return false;
  int g=gcd(a,b);
  int ad=x%g;
  int x2=x/g;
  if(ad !=  y%g) return false;
  int l=a/g*b;
  if(t-f>=l)return true;
  int a2=a/g;
  int b2=b/g;
  int y2=y/g;
  int c=(((1LL*rev(a2,b2)*a2*((y2-x2+b2)%b2 )+x2))*g+ad)%l;
  return (t-1-(t-1-c+l)%l>=f);
}
bool meet(int i,int j){
  return solve( jmp[i],start[i]%jmp[i], jmp[j],start[j]%jmp[j],start[i]>?start[j],f); 
}
void solve(){
  int a,b,e;
  scanf("%d %d %d %d",&f,&e,&a,&b);
  for(int i=0;i<e;i++)
    reach[i]=0;
  for(int i=0;i<e;i++)
    scanf("%d %d",jmp+i,start+i);
  if(a==b){
    puts("It is possible to move the furniture.");        
    return;    
  }
  wc=pc=0;
  for(int i=0;i<e;i++)
    if( a - start[i] >=0 && (a - start[i])%jmp[i]==0){
      reach[i]=1;
      process[pc++]=i;
    }
  for(int i=0;i<e;i++)
    if( b - start[i] >=0 && (b - start[i])%jmp[i]==0)
      if(reach[i]){
        puts("It is possible to move the furniture.");        
        return;
      }else{
        reach[i]=-1;  
        process[pc++]=i;
      }
  
  while(wc<pc){
    int w=process[wc++];
    for(int i=0;i<e;i++)
      if(reach[i]!=reach[w]){
        if(meet(i,w)){
          if(reach[i]){
            puts("It is possible to move the furniture.");        
            return;            
          }else{
            reach[i]=reach[w];
            process[pc++]=i;
          }
        }
      }
  }
  puts("The furniture cannot be moved.");     
}
int main(){
  int z;
    scanf("%d",&z);
  while(z--)
    solve();
  return 0;
}
  
