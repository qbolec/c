#include<cstdio>
#include<cstring>
char t[200002];
char v[10][200002];
int p[200002];
int c[256];
int g[200002];
int b[200002];
int d[200002];
int q[200002][26];
int vlen[10];
bool dead[10];
void need(int f,int l){
  
}
int main(){
  gets(t);
  int tlen=strlen(t);
  int k;
  scanf("%d ",&k);
  memset(g,-1,sizeof(g));
  memset(q,-1,sizeof(q));
  for(int j=k;j--;){
    gets(v[j]);
    vlen[j]=strlen(v[j]);
  }
  for(int j=0;j<k;j++){
    for(int i=2;i<=vlen[j];i++){
      int w=i-1;
      while(w&&v[j][p[w]]!=v[j][i-1])w=p[w];
      p[i]=w?p[w]+1:0;
    }
    for(int i=0;i<k;i++)if(i!=j && !dead[i])if(vlen[j]<vlen[i]){
      int m=0;
      for(int r=0;r+vlen[j]-m<=vlen[i];r++){
        while(m&&v[i][r]!=v[j][m])m=p[m];
        if(v[i][r]==v[j][m])m++;
        if(!v[j][m]){
          dead[i]=true;
          break;
        }
      }
    }else if(vlen[j]==vlen[i]&&i<j&&!strcmp(v[i],v[j]))
      dead[i]=true;
  }
  for(int j=0;j<k;j++)if(!dead[j]){
    for(int i=2;i<=vlen[j];i++){
      int w=i-1;
      while(w&&v[j][p[w]]!=v[j][i-1])w=p[w];
      p[i]=w?p[w]+1:0;
    }
    int m=0;
    for(int i=0;i+vlen[j]-m<=tlen;i++){
      while(m&&t[i]!=v[j][m])m=p[m];
      if(t[i]==v[j][m])m++;
      if(!v[j][m]){
        g[i]>?=i-m+1;
        m=p[m];
      }
    }
  }
  for(int i=0;i<26;i++){
    scanf("%d",&c['a'+i]);
    q[tlen][i]=tlen;
  }
  for(int i=tlen;i--;){
    memcpy(q+i,q+i+1,sizeof(int)*26);
    q[i][t[i]-'a']=i;
  }
  int e=-1;
  for(int i=0;t[i];i++){
    b[i]=c[t[i]];
    if(e>=0)b[i]+=d[e];
    if(g[i]>=0){
      e=i;
      d[i]=b[g[i]];
      for(int j=0;j<26;j++){
        int s=q[g[i]][j];
        if(s<=i)d[i]<?=b[s];
      }
    }
  }
  printf("%d\n",e>=0?d[e]:0);
}
