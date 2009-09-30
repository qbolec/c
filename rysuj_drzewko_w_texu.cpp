#include<cstdio>
char * t[]={
"      ",
"     |",
"    /|",
"    ||",
"    ||",
"   /||",
"  //||",
" /||||",
"//||||"
};
int main(){
  for(int r=0;r<9;r++){
    for(int i=0;t[r][i];i++){
      if(t[r][i]=='/'){
        printf(" \\ar[ru] & ");
      }else if(t[r][i]=='|'){
        printf(" \\ar[u] & ");
      }else if(t[r][i]=='L'){
        printf(" & \\ar[lu] ");
      }else{
        printf(" & ");
      }
    }
    printf(" \\\\\n");
  }
  int i;
  scanf("%d",&i);
}
