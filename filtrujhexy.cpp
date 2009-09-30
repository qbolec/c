#include<cstdio>
int main(){
  char t[1023];
  while(scanf("%s",t)==1){
    if(true || t[0]=='o'){
      bool dupa=false;
      for(int i=0;t[i];i++)
        if(!(t[i]=='o' ||t[i]>='a' && t[i]<='f'))
          dupa=true;
      if(!dupa)
        puts(t);
    }
  }
}
