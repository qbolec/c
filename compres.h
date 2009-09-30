#include <iostream.h>

struct treenode
{
  treenode *     child[2];
  unsigned long     stats;
  unsigned char character;
};
struct dictform
{
  unsigned char fullbyte[32];
  unsigned char fbc;
  unsigned char bits[8];
  unsigned char bc;
};

unsigned char stackbits[256];
treenode * cox[257];
treenode * D3;
dictform dictionary[256];
int incox=0;
unsigned char bigmem[16000000];
unsigned long stats[256];
unsigned char * wb;
unsigned char qrentbyte=0;
unsigned char bmlt=128;
istream qin;
ostream qout;
void BIT(int x)
{
  if(x)qrentbyte|=bmlt;
  bmlt>>=1;
  if(bmlt==0)
  {
    qout.put(qrentbyte);
    qrentbyte=0;
    bmlt=128;
  }
}
void BYTE(unsigned char x)
{
  if(bmlt==128)
    qout.put(x);
  else
    for(int mt=128;mt;mt>>=1)
      BIT(x & mt);
}
void cash()
{
  wb=bigmem;
  while(!qin.eof())
    *wb++= qin.get();
  wb--;
  qout.put( (unsigned char) (((wb-bigmem)>>24) & 255) );
  qout.put( (unsigned char) (((wb-bigmem)>>16) & 255) );
  qout.put( (unsigned char) (((wb-bigmem)>>8) & 255) );
  qout.put( (unsigned char) (((wb-bigmem)>>0) & 255) );
}
void statsgether()
{
 
  for(unsigned char * rb=bigmem;rb<wb;rb++)
    stats[*rb]++;
}
inline void swap(int a,int b)
{
  treenode *swp=cox[a];
  cox[a]=cox[b];
  cox[b]=swp;
}
void coxinsert(treenode * c)
{
  incox++;
  cox[incox]=c;
  int id=incox;
  while(id>1)
  {
    if(cox[id]->stats < cox[id>>1]->stats)
    {
      swap(id,id>>1);
      id>>=1;
    }
    else
      break;
  }
}
treenode * coxgive()
{
  treenode * out;
  out=cox[1];
  cox[1]=cox[incox];
  incox--;
  if(incox<2)return out;
  int id=1;
  while((id<<1)<incox)
  {
    if( (cox[id]->stats > cox[id<<1]->stats) &&
        (cox[(id<<1)+1]->stats >= cox[id<<1]->stats)  )
    {
       swap(id,id<<1);
       id<<=1;
    }
    else
      if( (cox[id]->stats > cox[(id<<1)+1]->stats) &&
          (cox[(id<<1)+1]->stats <= cox[id<<1]->stats)  )
      {
        swap(id,(id<<1)+1);
        id=(id<<1) + 1;
      }
      else
        break;
  }
  if(id<<1==incox)
    if( (cox[id]->stats > cox[id<<1]->stats) )
      swap(id,id<<1);
  return out;
}
void treegen()
{
 
  for(unsigned int i=0;i<256;i++)
    if(stats[i])
    {
      treenode* c=new treenode;
      c->character=i;
      c->stats=stats[i];
      c->child[0]=0;
      c->child[1]=0;
      coxinsert(c);
    }
  while(incox>1)
  {
    treenode* a=coxgive();
    treenode* b=coxgive();
    treenode* c=new treenode;
    c->stats=a->stats+b->stats;
    c->child[0]=a;
    c->child[1]=b;
    coxinsert(c);
  }
  D3=cox[1];
}
void clearing()
{
 
  for(unsigned int i=0;i<256;i++)
  {
    cox[i]=0;
    stats[i]=0;
  }
  qin.close();
}
void save3(treenode * c)
{
  if(c->child[0])
  {
    BIT(1);
    save3(c->child[0]);
    save3(c->child[1]);
  }
  else
  {
    BIT(0);
    BYTE(c->character);
  }
}
void cr8dict(treenode * c,int stackpos)
{
  if(c->child[0])
  {

    stackbits[stackpos]=0;

    cr8dict(c->child[0],stackpos+1);
    stackbits[stackpos]=1;

    cr8dict(c->child[1],stackpos+1);
  }
  else
  {
    dictionary[c->character].fbc=stackpos>>3;
    int bp=0;
    
    for(int i=0;i<dictionary[c->character].fbc;i++)
    {
      for(int mt=128;mt;mt>>=1)
        if(stackbits[bp++])
          dictionary[c->character].fullbyte[i]|=mt;
    }
    dictionary[c->character].bc=stackpos-bp;
    for(int i=0;i<dictionary[c->character].bc;i++)
      dictionary[c->character].bits[i]=stackbits[bp++];
  }

}
void savetreeinfo()
{

  save3(D3);
}
void treetodict()
{

  cr8dict(D3,0);
}
void compressing()
{

  for( unsigned char * rb=bigmem;rb<wb;rb++)
  {
    for(unsigned char i=0;dictionary[*rb].fbc>i;i++)
      BYTE(dictionary[*rb].fullbyte[i]);
    for(unsigned char i=0;dictionary[*rb].bc>i;i++)
      BIT(dictionary[*rb].bits[i]);
  }
}
int compresSTREAMtoSTREAM(istream fin,ostream fout)
{
  qin=fin;
  qout=fout;
  cash();
  statsgether();
  treegen();
  clearing();
  savetreeinfo();
  treetodict();
  compressing();
  if(bmlt!=128)qout.put(qrentbyte);
  return 0;
}
