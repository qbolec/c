#import<algorithm>
#import<cstdio>
using namespace std;
int w[1000];
int main(){
  int b=0;
  int bd=0;
  for(int d=1;d<1000;d++){
    memset(w,0,sizeof(w));
    int s=1;
    int n=1;
    for(;!w[s];s=s*10%d){
      w[s]=n++;
    }
    if(n-w[s]>b){
      b=n-w[s];
      bd=d;
    }
  }
  printf("%d  -> %d\n",bd,b);
  scanf("%d");
}
