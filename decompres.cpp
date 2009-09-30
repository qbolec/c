#include <iostream.h>
#include <fstream.h>
ifstream qin;
ofstream qout;
struct treenode
{
  treenode *     child[2];
  unsigned char character;
};
treenode * D3;
unsigned long bs=0;
unsigned char bmlt=0;
unsigned char qrentbyte=0;
int BIT()
{
  
  if(bmlt==0)
  {
    qrentbyte=qin.get();
    bmlt=128;
  }
  if(qrentbyte & bmlt)
  {
     bmlt>>=1;
     return 1;
  }
  else
  {
     bmlt>>=1;
     return 0;
  }
}
int BYTE()
{
  int out=0;
  for(int mlt=128;mlt;mlt>>=1)
    if(BIT())
      out|=mlt;
  return out;
}
void filesset()
{
  char filename[256];
  cout << ".:welcome 2 the first q.decompressor for dos:."<<endl << endl;
  cout << ".:type name of file to decompress::";
  cin >> filename;
  qin.open(filename,ios::bin);
  cout << endl << ".:type name of output file::";
  cin >> filename;
  qout.open(filename,ios::bin);
  bs=BYTE();
  bs<<=8;
  bs+=BYTE();
  bs<<=8;
  bs+=BYTE();
  bs<<=8;
  bs+=BYTE();
}
void cr8tree(treenode * c)
{
  if(BIT())
  {
    c->child[0]=new treenode;
    c->child[1]=new treenode;
    
    cr8tree(c->child[0]);
    cr8tree(c->child[1]);
  }
  else
  {
    c->character=BYTE();
    c->child[0]=0;
    c->child[1]=0;
  }
}
void treein()
{
   D3=new treenode;
   cr8tree(D3);
}
void onebyte(treenode * c)
{
  if(c->child[0])
    onebyte(c->child[BIT()]);
  else
    qout.put(c->character); 
}
void decompres()
{
  for(unsigned long int i=0;i < bs;i++)
    onebyte(D3);
 
}
int main()
{
  filesset();
  treein(); 
  decompres();
  return 0;
}
