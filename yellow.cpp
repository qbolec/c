#include<cstdio>
char yellow[5000][20]={
"00",
"10",
"01",
"11"
};
int main(){
  for(int d=4;d<=12;d+=2){
    int l=1<<(d-2);
    for(int t=1;t<4;t++){
      for(int i=0;i<l;i++){
        for(int j=0;j<d-2;j++)
          yellow[t*l+i][j]=yellow[i][j];
      }
    }
    for(int i=0;i<l;){
      yellow[i    ][d-2]='0';yellow[i    ][d-1]='0';i++;
      yellow[i    ][d-2]='1';yellow[i    ][d-1]='1';i++;
    }
    for(int i=0;i<l;){
      yellow[i+l  ][d-2]='1';yellow[i+l  ][d-1]='0';i++;
      yellow[i+l  ][d-2]='0';yellow[i+l  ][d-1]='1';i++;
    }       
    for(int i=0;i<l;){
      yellow[i+l*2][d-2]='1';yellow[i+l*2][d-1]='1';i++;
      yellow[i+l*2][d-2]='0';yellow[i+l*2][d-1]='0';i++;
    }
    for(int i=0;i<l;){
      yellow[i+l*3][d-2]='0';yellow[i+l*3][d-1]='1';i++;
      yellow[i+l*3][d-2]='1';yellow[i+l*3][d-1]='0';i++;
    }
 
  }
  int z=0;
  while(1){
    int n;
    scanf("%d",&n);
    if(!n)return 0;
    if(z++)puts("");
    for(int i=0;i< (1<<n);i++){
      char x=yellow[i][n];
      yellow[i][n]=0;
      puts(yellow[i]);
      yellow[i][n]=x;
    }
  }
}
