#include <iostream.h>

struct node{unsigned char colors[24];
            node * previous;
            unsigned char side; //0-bad , 1-win
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

tree * hashtable[64000];
queue * qfirstB;
queue * qlastB;
queue * qfirstW;
queue * qlastW;
unsigned char winner[17];
unsigned char propos[17];
unsigned char propID=0;
unsigned char sidebadprogres;
unsigned char sidewinprogres;
unsigned char correct[24]={0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0,1,2,1} ;
//[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
void move( unsigned char * A,unsigned char * B, unsigned char M)
{
  switch(M)
  {
    case(1):
      for(int i=0;i<10;i++)
        B[i+2]=A[i];
      B[0]=A[10];
      B[1]=A[11];
      for(int i=11;i<24;i++)
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
      for(int i=0;i<12;i++)
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
      for(int i=11;i<24;i++)
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
      for(int i=0;i<12;i++)
       B[i]=A[i];
      B[11]=B[23];
      B[10]=B[22];
      B[9]=B[21];
  }
}
//[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
int main()
{
int x;
 cout << "\nPlease enter begining situation:\n";
unsigned char tab[24];
unsigned char tab2[24];
for (int i=0;i<24;i++)
  {
    cin >> x;
    tab[i]=x;
  }
 cout << "\nNow Please Enter The Transform - end it with -1\n";
 cin >> x;
 while(x>=0)
 {
   move(tab,tab2,x);
   for (int i=0;i<24;i++)
   {
     tab[i]=tab2[i];
     cout << (int) tab[i];
   }
   cout << "\n";
   cin>>x;
 }
}

