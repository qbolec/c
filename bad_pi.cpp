#include<cstdio>
#include<cstring>
char v[1023];
int p[12121];
int r[12121];
int main(){
  while(true){
  gets(v);
  int vlen=strlen(v);
  int k=0;
  for(int q=2;q<=vlen;q++)
  {
    while(k>0 && v[k]!=v[q-1]) k=p[k];
    if(v[k]==v[q-1]) k++;
    p[q]=k;
  }

  for(int i=2;i<=vlen;i++){
   int w=i-1;
    while(w&&v[r[w]]!=v[i-1])w=r[w];
    r[i]=w?r[w]+1:0;
  }

  for(int i=0;i<=vlen;i++){
    printf("%d %d  przed %c\n",p[i],r[i],v[i]);
  }
  }
  return 0;
}
