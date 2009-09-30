#include<fstream>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<set>
#include<sstream>
using namespace std;
char t[256];
int main(int argc,char *args[]){
  if(argc!=2)return 0;
  ifstream fin(args[1]);
  ifstream x("slowa.txt");
  for(int i=0;i<256;i++)
    t[i]=i;
  t[162]='o';
  t[228]='n';
  t[165]='a';
  t[169]='e';
  t[149]=t[190]='z';
  t[134]='c';
  t[152]='s';
  t[136]='l';
  set<string> s;
  while(!x.eof()){
    string z;
    x>>z;
    s.insert(z);
    string y=z;
    for(int i=0;i<z.length();i++)
      if(z[i]<'a' || z[i]>'z')
        z[i]=t[(unsigned char)z[i]];
    if(z!=y)
      s.insert(z);
  }
  x.close();
  int linijka=0;
  while(!fin.eof()){
    char buf[1025];
    fin.getline(buf,1024,'\n');
    int j=0;
    for(int i=0;buf[i];i++)
      if('A'<=buf[i] && buf[i]<='Z')
        buf[j++]=buf[i]+'a'-'A';
      else if('a'<=buf[i] && buf[i]<='z')
        buf[j++]=buf[i];
      else if(0<=buf[i] &&buf[i]<=32)
        buf[j++]=buf[i];
      else
        buf[j++]=' ';
    buf[j]=0;
    istringstream x(string(buf,buf+j));
    linijka++;
    while(!x.eof()){
      string z;
      x >> z;
      if(z.length()>3 && s.find(z)==s.end())
        cout << args[1] << " : " << linijka << " :" << z << endl;
    }
  }
  return 0;
}
