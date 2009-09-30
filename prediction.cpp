//ej to jest takie dla jaj napisane;P powinno byc liniowe i nie uzywac pamieci:D
#include<fstream>
#include<cstdio>
#include<vector>
using namespace std;
vector<char> data;
vector<char> out;
char buffer=0;
int bufferpos=0;

void say(int what,int bits){
  for(int i=0;i<bits;i++){
    if( what & (1<<i) ){
      buffer |= (1<<bufferpos);
    }
    if(++bufferpos==8){
      out.push_back(buffer);
      buffer=0;
      bufferpos=0;
    }
  }
}
int main(int argc,char * args[]){
  if(argc!=3){
    printf("usage: %s whattocompres wheretoput",args[0]);
    return 0;
  }
  int ok=0;
  int quick=-1;
  ifstream file(args[1],ios::binary);
  ofstream pack(args[2],ios::binary);
  while(1){
    char c=file.get();    
    if( file.eof() ){
      if(ok){
        say(0xFFFFFFFF,ok);
        say(0,1);
      }
      if(bufferpos)
        out.push_back(buffer);
      pack.write(&out[0],out.size());
      printf("%d to %d",data.size(),out.size());      
      return 0;
    }

    if(quick>=0 && data[quick]==c){
      ok++;
      quick++;
    }else{
      int b=1,bp=0;
      for(int i=1;i<data.size();i++){
        int j=1,l=data.size()-1;
        for(;i<=l && data[l-i]==data[l];j++,l--);
        if(j>b){
          b=j;
          bp=i;
        }
      }
      if(bp && data[data.size()-bp]==c){
          ok++;
          quick=data.size()-bp+1;
      }else{
          say(0xFFFFFFFF,ok);
          say(0,1);
          say(c,8);
          ok=0;
          quick=-1;
      }
    }
    data.push_back(c);
  }

}
