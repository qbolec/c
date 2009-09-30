#include <iostream.h>

struct node{unsigned char colors[24];
            node * previous;
            unsigned char side;
            unsigned char moveID;
            unsigned char moveNUM;
           };

struct tree{ node * value;
             tree * bigger;
             tree * smaller;
           };

struct queue{node * value;
             queue * next;
            };

tree * hashtable[0x10000];//[64000];
queue * qfirstB;
queue * qlastB;
queue * qfirstW;
queue * qlastW;
unsigned char winner[17];
unsigned char propos[17];
unsigned char propID=0;
unsigned char sidebadprogres;
unsigned char sidewinprogres;
unsigned char correct[24]=
{0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0,1,2,1} ;
int compare(unsigned char * A,unsigned char * B)
{
  for(int i=0;i<24;i++)
  {
    if( A[i]>B[i]) return 1;
    if( A[i]<B[i]) return-1;
  }
  return 0;
}
void move( unsigned char * A,unsigned char * B, unsigned char M)
{
  switch(M)
  {
    case(1):
      for(int i=0;i<10;i++)
        B[i+2]=A[i];
      B[0]=A[10];
      B[1]=A[11];
      for(int i=12;i<21;i++)
        B[i]=A[i];
      B[23]=B[11];
      B[22]=B[10];
      B[21]=B[9];
    break;
    case(2):
      for(int i=14;i<24;i++)
        B[i-2]=A[i];
      B[22]=A[12];
      B[23]=A[13];
      for(int i=0;i<9;i++)
       B[i]=A[i];
      B[11]=B[23];
      B[10]=B[22];
      B[9]=B[21];
    break;
    case(3):
      for(int i=2;i<12;i++)
        B[i-2]=A[i];
      B[10]=A[0];
      B[11]=A[1];
      for(int i=12;i<21;i++)
        B[i]=A[i];
      B[23]=B[11];
      B[22]=B[10];
      B[21]=B[9];
    break;
    case(4):
      for(int i=12;i<22;i++)
        B[i+2]=A[i];
      B[12]=A[22];
      B[13]=A[23];
      for(int i=0;i<9;i++)
       B[i]=A[i];
      B[11]=B[23];
      B[10]=B[22];
      B[9]=B[21];
  }
}
unsigned int hash(unsigned char * A)
{
  unsigned int out1=0;
  unsigned int out=0;

  for(int i=0;i<8;i++)
  {
   out1=out1<<2;
   out1^=A[i];
  }
  out=out1;
  out1=0;
  for(int i=8;i<16;i++)
  {
   out1=out1<<2;
   out1^=A[i];
  }
  out^=out1;
  out1=0;
  for(int i=16;i<24;i++)
  {
   out1=out1<<2;
   out1+=A[i];
  }
  out^=out1;
  out&=0xFFFF;
  return out;
}
int putmetotree( node * H)
{
 tree * t;
 tree * l;
 unsigned int h;
 int c;
 t=hashtable[h= hash(H->colors) ];

 if(t!=NULL)
 {
   while(t!=NULL)
   {
     l=t;
     c=compare(t->value->colors,H->colors);
     if(c==0)
     {
       if(t->value->side==H->side)return 0;
       else return 1;
     }
     if(c>0) t=t->bigger;
     if(c<0) t=t->smaller;
   }
   if(c>0)
   {
     l->bigger=new tree;
     t=l->bigger;
   }
   else
   {
     l->smaller=new tree;
     t=l->smaller;
   }
 }
 else
 {
  hashtable[h]=new tree;
  t=hashtable[h];
 }
  t->value=H;
  t->bigger=NULL;
  t->smaller=NULL;
  return 2;
}

int visited(node * H)
{
 tree * t;
 t=hashtable[hash(H->colors) ];
 int c;
 while(t!=NULL)
 {
   c=compare(t->value->colors,H->colors);
   if(c==0)return t->value->side;
   if(c>0) t=t->bigger;
   if(c<0) t=t->smaller;
 }
 return -1;
}

node * getfromtree(node * H)
{
 tree * t;
 t=hashtable[ hash(H->colors) ];
 int c;
 while(t!=NULL)
 {
   c=compare(t->value->colors,H->colors);
   if(c==0)return t->value;
   if(c>0) t=t->bigger;
   if(c<0) t=t->smaller;
 }
}
unsigned char oposite(unsigned char A)
{
  switch(A)
  {
    case(1):  return 3;
    case(2):  return 4;
    case(3):  return 1;
    case(4):  return 2;
  }
  return 0;
}

void traceback(node * H)
{
  if(H->previous)
  {
    traceback(H->previous);
    propos[propID++]= H->moveID;
    propos[propID]=13;
  }
  else
    propID=0;


}

void compwin()
{

  unsigned char dlw=0,dlp=0;
  while(winner[dlw++]!=13);
  while(propos[dlp++]!=13);

  if(dlp>dlw)return;
  if(dlp<dlw)
  {
    for(dlw=0;dlw<=dlp;dlw++)
      winner[dlw]=propos[dlw];
  }
  if(dlp==dlw)
  {
    dlw=0;
    while(winner[dlw]==propos[dlw])dlw++;
    if(winner[dlw]>propos[dlw])
      for(;dlw<=dlp;dlw++)//dlw=0
        winner[dlw]=propos[dlw];

  }

}

void tracefoward(node * H)
{
  while(H->previous)
  {
    propos[propID++]= H->moveID;
    H=H->previous;
  }
  propos[propID]=13;
}

int flushW()
{
  if(qfirstW==NULL)return 440;

  node * adreskonca;
  node * adrespoczatku;
  adreskonca=qfirstW->value;

  if(visited(adreskonca)==0)
  {
    adrespoczatku=getfromtree(adreskonca);
    traceback(adrespoczatku);
    tracefoward(adreskonca);
    compwin();
  }

  qfirstW=qfirstW->next;

  return 0;
}


int procidW()
{
  node * adres;
  adres=qfirstW->value;
  if( adres->moveNUM != sidewinprogres)
  {
    sidewinprogres=adres->moveNUM;
    return 2;
  }

  switch(putmetotree(adres))
  {
    case(0):
      delete adres;
    break;
    case(2):
      for(int m=1;m<=4;m++)
       {
         if(m==adres->moveID) continue;

         node * tempnode;
         tempnode=new node;
         tempnode->side=1;
         tempnode->previous=adres;
         tempnode->moveID=oposite(m);
         tempnode->moveNUM=adres->moveNUM+1;
         move(adres->colors,tempnode->colors,m);
//         if(visited(tempnode)!=1)
//         {
           qlastW->next=new queue;
           qlastW=qlastW->next;
           qlastW->value=tempnode;
           qlastW->next=NULL;
//         }
//         else
//           delete tempnode;
//         tempnode=NULL;
       }
    break;
    case(1):
      return 440;
    break;

  }
  qfirstW=qfirstW->next;
  return 0;
}
int procidB()
{
  node * adres;
  adres=qfirstB->value;
  if( adres->moveNUM != sidebadprogres)
  {
    sidebadprogres=adres->moveNUM;
    return 2;
  }
  switch(putmetotree(adres))
  {
     case(0):
       delete adres;
     break;
     case(2):
       for(int m=1;m<=4;m++)
       {
         if(oposite(m)==adres->moveID) continue;

         node * tempnode;
         tempnode=new node;
         tempnode->side=0;
         tempnode->previous=adres;
         tempnode->moveID=m;
         tempnode->moveNUM=adres->moveNUM+1;
         move(adres->colors,tempnode->colors,m);
//         if(visited(tempnode)!=0)
//         {
           qlastB->next=new queue;
           qlastB=qlastB->next;
           qlastB->value=tempnode;
           qlastB->next=NULL;
//         }
//         else
//           delete tempnode;
//         tempnode=NULL;
       }
     break;
     case(1):
       traceback(adres);
       adres=getfromtree(adres);
       tracefoward(adres);
       compwin();
       return 440;
     break;
  }
  qfirstB=qfirstB->next;

  return 0;
}

int startB()
{
  sidewinprogres=0;
  sidebadprogres=0;
  for(unsigned int i=0;i<0x10000;i++)
    if(hashtable[i])
    {
      delete hashtable[i];
      hashtable[i]=NULL;
    }

  if(qfirstB)
    delete qfirstB;

  for(int i=0;i<16;i++)
    winner[i]=11;

  winner[16]=13;

  qfirstB=NULL;
  qlastB=NULL;


      node * tempnode;
      tempnode=new node;
      tempnode->previous=NULL;
      tempnode->moveID=0;
      tempnode->side=0;
      tempnode->moveNUM=0;

  for(int i=0;i<24;i++)
  {
    unsigned int x;
    cin>>x;
    tempnode->colors[i]=x;
  }


  if(compare(tempnode->colors,correct)==0)
  {
    cout << "PUZZLE ALREADY SOLVED";
    return 440;
  }
  else
  {
    qfirstB=new queue;
    qfirstB->value=tempnode;
    qfirstB->next=NULL;
    qlastB=qfirstB;
  }
  return 0;


}

int startW()
{
  if(qfirstW)
    delete qfirstW;

  qfirstW=NULL;
  qlastW=NULL;


      node * tempnode;
      tempnode=new node;
      tempnode->previous=NULL;
      tempnode->moveID=0;
      tempnode->side=1;
      tempnode->moveNUM=0;

  for(int i=0;i<24;i++)
    tempnode->colors[i]=correct[i];

  qfirstW=new queue;
  qfirstW->value=tempnode;
  qfirstW->next=NULL;
  qlastW=qfirstW;

  return 0;

}


void typeoutwinner()
{
  unsigned char i=0;
  while(winner[i]!=13)
  {
    cout << (int)winner[i++];
  }
}

void doall()
{
  if(startB()==440)return;

  startW();
  int p;

  while(sidebadprogres<9)
  {
    while((p=procidB())==0);
    if(p==440)
    {
      typeoutwinner();
      return;
    }
    while((p=procidW())==0);
    if(p==440)
    {
      while(flushW()==0);
      typeoutwinner();
      return;
    }
  }
  cout << "NO SOLUTION WAS FOUND IN 16 STEPS";
}

int main()
{
 int n;
 cin >> n;
 for (int i=n;i;i--)
 {
  doall();
  cout << endl;
 }
 return 0 ;
}

