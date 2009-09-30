#include<cstdio>
#include<cstring>
using namespace std;
char filename[1000][16];
char ext[1000][4];
void lcs(char *A,char *B,char * out){
  int tmp[15][15];
  for(int i=0;i<15;i++)
    for(int j=0;j<15;j++)
      tmp[i][j]=0;
  for(int i=1;A[i-1];i++)
    for(int j=1;B[j-1];j++)
      if(A[i-1]==B[j-1])
        tmp[i][j]=1+tmp[i-1][j-1];
      else
        tmp[i][j]= tmp[i-1][j] >? tmp[i][j-1];
  int i=0;
  while(A[i])
    i++;
  int j=0;
  while(B[j])
    j++;
  int p=tmp[i][j];
  char LCS[15];
  for(int i=0;i<15;i++)
    LCS[i]=0;
  while(p){
    if(p==tmp[i-1][j-1]+1){
      i--;
      j--;
      p--;
      LCS[p]=A[i];
    }else{
      if(tmp[i][j]==tmp[i][j-1])
        j--;
      else
        i--;
    }
  }
  printf("LCS(%s,%s)=%s\n",A,B,LCS);
  for(int i=0;i<15;i++)
    out[i]=LCS[i];        
}
char LCS[15];
int fc=1;
int todel[1000];
int todelc=0;
char wildchar[15];
int limit;
bool match(char * name,char * wild){
  if(!*name){
    if(!*wild)
      return true;
    if(*wild=='*')
      return match(name,wild+1);
    return false;
  }
  if(!*wild)
    return false;
  if(*name==*wild || *wild=='?')
    return match(name+1,wild+1);
  
  if(*wild=='*')
    return match(name+1,wild)||match(name,wild+1);
  return false;  
}
char flag(char * name){
  //w zasadzie to nalezaloby zbudowac automat... ale dla 1000 testow to chyba nie ma sensu?
  return (match(name,wildchar))?'-':'+';
}
bool test(){
  printf("Testing: %s limit=%d\n",wildchar,limit);
  if(limit==8){
    for(int i=0;i<fc;i++)  
      if(flag(filename[i]+1)!=filename[i][0])
        return false;
  }else{
    for(int i=0;i<fc;i++)  
      if(flag(ext[i])!=filename[i][0])
        return false;
  }
  return true;
}
bool subs(int pos,char * lcs){
  if(wildchar[pos]==0)
    return test();
  if(wildchar[pos]=='_'){
    if(*lcs){
      if(subs(pos,lcs+1))
        return true;
      wildchar[pos]=*lcs;
      if(subs(pos+1,lcs+1))
        return true;      
    }else
      return false;    
    wildchar[pos]='_';
    return false;
  }else
    return subs(pos+1,lcs);  
}
bool guess(int pos){
  wildchar[pos]=0;
  if(subs(0,LCS))
    return true;

  if(pos==limit)
    return false;
    
  if(!pos || wildchar[pos-1]!='*'){
  
    wildchar[pos]='?';
    if(guess(pos+1))
      return true;
  
    wildchar[pos]='*';  
    if(guess(pos+1))
      return true;            
  }  

  wildchar[pos]='_';
  if(guess(pos+1))
    return true;
    
  return false;
}
void solve(){
  scanf(" ");
  todelc=0;
  fc=0;
  while(1){
    gets(filename[fc]);
    if(filename[fc][0]){
      if(filename[fc][0]=='-')
        todel[todelc++]=fc;
      fc++;
    }else
      break;
  }
  for(int i=0;i<fc;i++){
    int cut=0;
    while(filename[i][cut]!='.' && filename[i][cut])
      cut++;
    if(filename[i][cut]==0)
      filename[i][cut+1]=0;
    else
      filename[i][cut]=0;
    strcpy(ext[i],filename[i]+cut+1);
  }
  printf("Wczytano %d stringow:\n",fc);
  for(int i=0;i<fc;i++)
    printf("%s<kropka>%s\n",filename[i],ext[i]);
  
  
  strcpy(LCS,filename[todel[0]]+1);
  for(int i=1;i<todelc;i++)
    lcs(LCS,filename[todel[i]]+1,LCS);

  limit=8;
  printf("LCS=%s\n",LCS);
  if(guess(0)){
    char fore[1024];
    strcpy(fore,wildchar);

    strcpy(LCS,ext[todel[0]]);
    for(int i=1;i<todelc;i++)
      lcs(LCS,ext[todel[i]],LCS); 
    
    
    limit=3;
    printf("LCS=%s\n",LCS);
    if(guess(0)){
      printf("DEL %s.%s\n",fore,wildchar);
    }else
      printf("IMPOSSIBLE\n");
  }else
    printf("IMPOSSIBLE\n");
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    solve();
    if(t)
      printf("\n");
  }
  return 0;
}
