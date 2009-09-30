#include<cstdio>
#include<cstring>
#include<cstdlib>

int t[5][4]={
  {1,0,0,0},
  {0,0,0,1},
  {1,1,1,1},
  {1,2,4,8},
  {8,4,2,1}
};
int q[4]={0,1,2,3};
int a[7][7];
int ar=0;
char tmp[1024];
char * upper_abcd(const char * t){
  strcpy(tmp,t);
  for(int i=0;t[i];i++){
    if(!i||t[i-1]!='%')
      if(t[i]>='a'&&t[i]<='d')
        tmp[i]+='A'-'a';
  }
  return tmp;
}
const char  formats[8][1023]={
"Q_ex c%d(c); c%d*=%dU;\n",
"Q_ex a%d_c%d(a); a%d_c%d*=%dU;  a%d_c%d+= c%d;\n",
"Q_ex d%d(d); d%d*=%dU;\n",
"Q_ex b%d_d%d(b); b%d_d%d*=%dU; b%d_d%d+=d%d;\n",
"Q_ex a%d_b%d_c%d_d%d(a%d_c%d); a%d_b%d_c%d_d%d+=b%d_d%d;\n",
"S_ex a%d_b%d_c%d_d%dA%d_B%d_C%d_D%d=a%d_b%d_c%d_d%d*A%d_B%d_C%d_D%d;\n",
"Q_ex a%d_minus_b%d_c%d_minus_d%d(a%d_c%d); a%d_minus_b%d_c%d_minus_d%d-=b%d_d%d;\n",
"S_ex a%d_minus_b%d_c%d_minus_d%dA%d_minus_B%d_C%d_minus_D%d=a%d_minus_b%d_c%d_minus_d%d*A%d_minus_B%d_C%d_minus_D%d;\n",
  };
char uberformats[8][1023];
void go(int * t,const char formats[][1023]){
  printf(formats[0],t[2],t[2],t[2]);
  printf(formats[1],t[0],t[2],t[0],t[2],t[0],t[0],t[2],t[2]);
  printf(formats[2],t[3],t[3],t[3]);
  printf(formats[3],t[1],t[3],t[1],t[3],t[1],t[1],t[3],t[3]);
  printf(formats[4],t[0],t[1],t[2],t[3],t[0],t[2],t[0],t[1],t[2],t[3],t[1],t[3]);
}
int name[8][4];
void go(int * t){
  for(int i=0;i<8;i++)
    strcpy(uberformats[i],upper_abcd(formats[i]));

  go(t,formats);
  go(t,uberformats);

  printf(formats[5],t[0],t[1],t[2],t[3],t[0],t[1],t[2],t[3],t[0],t[1],t[2],t[3],t[0],t[1],t[2],t[3]);
  for(int j=0;j<7;j++)
    a[ar][j]=t[j/2]*t[j-j/2];
  for(int j=0;j<4;j++)
    name[ar][j]=t[j];
  ar++;
  if(t[1]&&ar<7){
    printf(formats[6],t[0],t[1],t[2],t[3],t[0],t[2],t[0],t[1],t[2],t[3],t[1],t[3]);
    printf(upper_abcd(formats[6]),t[0],t[1],t[2],t[3],t[0],t[2],t[0],t[1],t[2],t[3],t[1],t[3]);
    printf(formats[7],t[0],t[1],t[2],t[3],t[0],t[1],t[2],t[3],t[0],t[1],t[2],t[3],t[0],t[1],t[2],t[3]);
    for(int j=0;j<4;j++)
      name[ar][j]=t[j]*(j%2?-1:1);
    for(int j=0;j<7;j++)
      a[ar][j]=t[j/2]*t[j-j/2]*(j%2?-1:1);
    ar++;
  }
  
}
bool rows_taken[7];
bool cols_taken[7];
int main(){
  for(int i=0;i<5;i++){
    go(t[i]);
  }

  printf("S_ex rows[7]={\n");
  const char * f="a%d_%sb%d_c%d_%sd%d";
  for(int i=0;i<7;i++){
    if(i)printf(",\n");
    printf(f,name[i][0],name[i][1]>=0?"":"minus_",abs(name[i][1]),name[i][2],name[i][3]>=0?"":"minus_",abs(name[i][3]));
    printf(upper_abcd(f),name[i][0],name[i][1]>=0?"":"minus_",abs(name[i][1]),name[i][2],name[i][3]>=0?"":"minus_",abs(name[i][3]));
  }
  printf("};\n");
/*
  for(int r=0;r<7;r++){
    for(int c=0;c<7;c++)
      printf("%4d ",a[r][c]);
    puts("");
  }
*/
  int rs[7];
  int cs[7];
  for(int g=0;g<7;g++){
    int bestr=-1;int bestc=-1;int best=0;
    for(int r=0;r<7;r++)if(!rows_taken[r])
      for(int c=0;c<7;c++)if(!cols_taken[c] && a[r][c]){
        if(bestr<0 || abs(a[r][c])<best){
          best=abs(a[r][c]);
          bestr=r;
          bestc=c;
        }
      }
    rs[g]=bestr;
    cs[g]=bestc;
//    printf("chosen %d %d\n",rs[g],cs[g]);
    for(int r=0;r<7;r++)if(r!=bestr){
      if(a[r][bestc]%a[bestr][bestc]==0){
        int f=a[r][bestc]/a[bestr][bestc];
        if(f){
          printf("S_ex row%d_%d(rows[%d]); row%d_%d*=%dU;\n",bestr,abs(f),bestr,bestr,abs(f),abs(f));
          if(f>0)
            printf("rows[%d]-=row%d_%d;\n",r,bestr,f);
          else
            printf("rows[%d]+=row%d_%d;\n",r,bestr,abs(f));
        }
        for(int c=0;c<7;c++){
          a[r][c]-=f*a[bestr][c];
        }
        rows_taken[bestr]=true;
        cols_taken[bestc]=true;
      }else if(!rows_taken[r]){
        printf("//nie idzie zminimalizowac wiersza %d kolumna %d z wiersza %d\n",r,bestc,bestr);
      }
    }
/*
    for(int r=0;r<7;r++){
      for(int c=0;c<7;c++)
        printf("%4d ",a[r][c]);
      puts("");
    }
*/
  }
  for(int i=7;i--;){
    for(int r=0;r<7;r++)if(rows_taken[r]){
      int cnt=0;
      for(int c=0;c<7;c++)if(a[r][c]&&cols_taken[c])cnt++;
      if(cnt==1){
        rs[i]=r;
        for(int c=0;c<7;c++)if(a[r][c]&&cols_taken[c])
          cs[i]=c;
        rows_taken[rs[i]]=false;
        cols_taken[cs[i]]=false;
        break;
      }
    }
  }
  for(int i=7;i--;){

    printf("S_ex col%d(rows[%d]);\n",cs[i],rs[i]);
    for(int c=0;c<7;c++)if(a[rs[i]][c] && c!=cs[i]){
      printf("S_ex col%d_%d(col%d); col%d_%d*=%dU;\n",c,abs(a[rs[i]][c]),c,c,abs(a[rs[i]][c]),abs(a[rs[i]][c]));
      if(a[rs[i]][c]>0)
        printf("col%d-=col%d_%d;\n",cs[i],c,abs(a[rs[i]][c]));
      else
        printf("col%d+=col%d_%d;\n",cs[i],c,abs(a[rs[i]][c]));
    }
    if(a[rs[i]][cs[i]]!=1)
      printf("\tcol%d/=%d;\n",cs[i],a[rs[i]][cs[i]]);
  }
//  system("PAUSE");
}
