#include<cstring>
#include<cstdio>
char a[1000000];
char b[1000000];
int main(){
  int n;
  scanf("%d",&n);
  while(n--){
    scanf("%s %s",a,b);
    int r=0;
    int i;
    for(i=0;r || a[i] || b[i]; i++){
      if(!a[i])a[i]='0';
      if(!b[i])b[i]='0';
      a[i]=a[i]+b[i]-'0'+r;
      if(a[i]>'9'){
        a[i]-=10;
        r=1;
      }else
        r=0;
    }
    int j;
    for(j=0;a[j]=='0';j++){}
    puts(a+j);
    for(;i>=0;i--)a[i]=b[i]=0;
  }
}
