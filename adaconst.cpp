#include<cstdio>
#include<cstring>
using namespace std;
int value(char * text,int len,bool final=true){
  if(len<=0)
    throw 666;
  bool sharp=text[len-1]=='#';
  if(sharp)len--;
  int i=len-1;
  while(i && text[i]!='#')i--;
  int base=10;
  if(sharp && text[i]!='#')
    throw 666;  
  if(text[i]=='#'){    
    if(i==0 || i==len-1)
      throw 666;
    if(!sharp)
      throw 666;
    base=value(text,i,false);    
    if(base>16 || base<2)
      throw 666;
  }else
    i=-1;
  int val=0;      
  for(int j=i+1;j<len;j++){
    int dig=0;
    if( text[j]>='0' && text[j]<='9'){
      dig=text[j]-'0';
    }else if(text[j]>='a' && text[j]<='f'){
      dig=text[j]-'a'+10;          
    }else
      throw 666;
    if(dig>=base)
      throw 666;
    val=val*base+dig;
    if(!final && val>16)
      throw 666;
  }
  return val;
}
bool parse(char * text,int len){
  try{
    int val=value(text,len);
  }catch(int x){
    return false;
  }
  return true;
}
int main(){
  int n;
  scanf("%d ",&n);
  while(n--){
    char text[80];
    scanf(" %s",text);
    if(parse(text,strlen(text)))
      printf("yes\n");
    else
      printf("no\n");
    
  }
  return 0;
}
