#include<cstdio>
using namespace std;
int c[1000000];
void inc(int pos,int amount){
  while(pos<1000000){
    c[ pos ]+=amount;
    pos|=  pos+1;
  }
}
int getTo(int to){
  if(to<0)
  	return 0;
  return c[to] +  getTo(  (to & (to+1))-1);
}
int getRange(int from,int to){
  return getTo(to-1)-getTo(from-1);
}

int main(){
 while(1){
   char c;
   scanf(" %c",&c);
   if(c=='c'){
 	 	 int from,to;
   	 scanf("%d %d",&from,&to);
   	 printf("%d\n",getRange(from,to));
   }else{
     int pos,amount;
 		 scanf("%d %d",&pos,&amount);
 		 inc(pos,amount);
   }
 }
 return 0;
}
