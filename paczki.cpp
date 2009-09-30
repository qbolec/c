#include<cstdio>
int a[6];
int main(){
  int n;
  scanf("%d",&n);
  while(n--){
    int w=0;
    for(int i=0;i<6;i++)
      scanf("%d",a+i);
    w+=a[5];
    a[0]-=a[4]*11;
    if(a[0]<0)a[0]=0;
    w+=a[4];
    //0,1,2,3
    w+=a[3];
    int left=a[3]*5*4;
    int a1=a[1]<? left/4;
    a[1]-=a1;
    left-=a1*4;
    a[0]-=left;
    if(a[0]<0)a[0]=0;
    //0,1,2
    
    w+=(a[2]+3)/4;
    if(a[2]%4){
      left=(4-a[2]%4)*9;

      a1=a[1]<? (left*2-1)/9;
      a[1]-=a1;
      left-=a1*4;
      a[0]-=left;
      if(a[0]<0)a[0]=0;
    }
    w+=(a[1]*4+a[0]+35)/36;
    printf("%d\n",w);
  }
}
