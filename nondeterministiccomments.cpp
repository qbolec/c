#include<cstdio>
#include<cstring>
char text[1024];
int best[1024][1024];
int main(){
  scanf("%s",text);
  int len=strlen(text);
  best[len][0]=0;
  for(int i=1;i<=len;i++)
    best[len][i]=-len;
  for(int s=len;s--;){
    bool mayclose=false;
    bool mayopen=false;
    bool notsure=false;
    if(text[s]=='*' && text[s+1]=='/'){
      mayclose=true;
      if(text[s+2]=='*' )
        notsure=true;
    }
    if(text[s]=='/' && text[s+1]=='*'){
      mayopen=true;
      if(text[s+2]=='/' )
        notsure=true;
    }
    if(!mayclose && !mayopen){
      best[s][0]=best[s+1][0];
      for(int o=1;o<len;o++)
        best[s][o]=best[s+1][o]+1;
    }else{
      if(notsure==false){
        if(mayopen){//mustopen
          for(int o=0;o<len;o++)
            best[s][o]=best[s+2][o+1]+2;
        }else{//mustclose
          for(int o=1;o<len;o++)
            best[s][o]=best[s+2][o-1]+2;
          best[s][0]=-len;
        }
      }else{//notsure
        if(mayopen){
          for(int o=0;o<len;o++)
            best[s][o]=best[s+2][o+1]+2;
          for(int o=1;o<len;o++)
            best[s][o]>?=  best[s+3][o-1]+3;
        }else{//mayclose
          for(int o=1;o<len;o++)
            best[s][o]=best[s+2][o-1]+2;
          best[s][0]=  best[s+3][0+1]+2;
          for(int o=1;o<len;o++)
            best[s][o]>?=  best[s+3][o+1]+3;
        }        
      }
    }
  }
    
  printf("%d\n",len-best[0][0]);
  return 0;
}
