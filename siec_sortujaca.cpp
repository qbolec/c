#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int P=2063;
int inv[P];
int md=0;
void bfs(int s){
  int d[P];
  int q[P];
  int w,r;
  for(int i=1;i<P;i++){
    d[i]=P;
  }
  r=w=0;
  q[w++]=s;
  d[s]=0;
  while(r<w){
    int i=q[r++];
    int m[3]={i+1,i-1,inv[i]};
    for(int j=0;j<3;j++){
      if(m[j]<P && m[j]>0 && d[m[j]]>d[i]+1){
        d[m[j]]=d[i]+1;
        q[w++]=m[j];
      }
    }
  }
  md>?=d[q[r-1]];
}
void bfs_up(int s){
  int d[P];
  int q[P];
  int w,r;
  for(int i=1;i<P;i++){
    d[i]=P;
  }
  r=w=0;
  q[w++]=s;
  d[s]=0;
  while(r<w){
    int i=q[r++];
    int m[3]={i+1,i-1,inv[i]};
    for(int j=0;j<3;j++){
      if(m[j]>i && m[j]<P && m[j]>0 && d[m[j]]>d[i]+1){
        d[m[j]]=d[i]+1;
        q[w++]=m[j];
      }
    }
  }
  printf("from %d to %d is %d\n",s,P-1,d[P-1]);
  md>?=d[P-1];
}
void bfs_down(int s){
  int d[P];
  int q[P];
  int w,r;
  for(int i=1;i<P;i++){
    d[i]=P;
  }
  r=w=0;
  q[w++]=s;
  d[s]=0;
  while(r<w){
    int i=q[r++];
    int m[4]={i+1,i-1,inv[i],P-i};
    for(int j=0;j<4;j++){
      if(m[j]<i && m[j]<P && m[j]>0 && d[m[j]]>d[i]+1){
        d[m[j]]=d[i]+1;
        q[w++]=m[j];
      }
    }
  }
  printf("from %d to %d is %d\n",s,1,d[1]);
  md>?=d[1];
}
const int N=31;
char t[1+N];
char t2[1+N];
int F[1+N];
int C1[1+N];
int C2[1+N];
int reverse(int x,int b){
  return b>2? ((x&1)*(b/2)) | reverse(x>>1,b/2) : x;
}
void heapify_step(){
  for(int level_parity=1;level_parity<=2;level_parity++){
    for(int level_start=level_parity;level_start<N;level_start*=4){
      for(int d=0;d<level_start;d++){
        const int f=level_start+d;
        const int c1=C1[f];
        const int c2=C2[f];
        char max=t[f]|t[c1];
        char min=t[f]&t[c1];
        char max2=max|t[c2];
        char min2=max&t[c2];
        t[f]=max2;
        t[c1]=min;
        t[c2]=min2;
      }
    }
    for(int level_start=level_parity;level_start<N;level_start*=4){
      for(int d=0;d<level_start;d++){
        const int f=level_start+d;
        const int c1=f*2;
        const int c2=c1+1;
        char max=t[f]|t[c1];
        char min=t[f]&t[c1];
        char max2=max|t[c2];
        char min2=max&t[c2];
        t[f]=max2;
        t[c1]=min;
        t[c2]=min2;
      }
    }
  }
}
int max_steps=0;
void draw(){
  for(int start=1;start<N;start*=2){
    for(int d=0;d<start;d++){
      printf("%d",(int)t[start+d]);
    }
    printf("\n");
  }
}
int heapify(){
  int steps=0;
  bool d=false;
  while(1){
    do{
      ++steps;
      memcpy(t2,t,sizeof(t));
      if(d)draw();
      heapify_step();
    }while(memcmp(t,t2,sizeof(t)));

    if(d){
      system("PAUSE");
      break;
    }

    int c=0;
    for(int i=1;i<N;i++){
      if(t[i]){
        c++;
      }
    }
    int start=1;
    while(start<=c){start*=2;}
    for(int i=start;i<=N;i++)
      if(t[i]){
        d=true;
      }
    if(!d){
      break;
    }
  }
  return steps;
}
int main(){
  /*for(int i=1;i<P;i++){
    for(int j=1;j<P;j++){
      if(i*j%P==1){
        inv[i]=j;
        break;
      }
    }
  }*/
  for(int start=1;start*2<N;start*=2){
    for(int d=0;d<start;d++){
      int f=start+d;
      int c1=start*2 + reverse(2*d,start*2);
      int c2=start*2 + reverse(2*d+1,start*2);
      
      C1[f]=c1;
      C2[f]=c2;
      F[c1]=f;
      F[c2]=f;
      //printf("%d -> %d,%d\n",f,c1,c2);
    }
  }

//  int Z[]={4,8,9,16,17,18,19,0};
//  for(int z=0;Z[z];z++){
//    t[Z[z]]=1;
//  }
//  heapify();
//  system("PAUSE");

  for(unsigned int v=(1<<N);v--;){
    for(int i=0;i<N;i++){
      t[1+i]=!!(v&1<<i);
    }
    int steps=heapify();
    if(steps>max_steps){
      max_steps=steps;
      printf("heapify(%d) gave %d steps\n",v,steps);
    }
      
  }
  
  system("PAUSE");
  return 0;
}
