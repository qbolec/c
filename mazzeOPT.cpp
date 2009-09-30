/*   @JUDGE_ID:   14143RZ   705   C++   "Hello World"   */
#include<iostream.h>


int x,y;
int ubuff1[75];
int ubuff2[75];
int fbuff1[75];
int fbuff2[75];

int * ubackbuffer;
int * ufrontbuffer;
int * fbackbuffer;
int * ffrontbuffer;

int cc;
int lc;
char fb[76];
void flip()
{
  int * swap;
  swap=fbackbuffer;
  fbackbuffer=ffrontbuffer;
  ffrontbuffer=swap;
  swap=ubackbuffer;
  ubackbuffer=ufrontbuffer;
  ufrontbuffer=swap;

  for(int i=0;i<x;i++)
   ufrontbuffer[i]=0;
}
void oneline()
{
  flip();
  int a,b;
  cin >> fb;
  int * uFA;
  int * uFB;
  int * uBA;
  int * uBB;
  int * fFA;
  int * fFB;
  int * fBA;
  int * fBB;

  uFA=ufrontbuffer;
  uFB=&ufrontbuffer[1];
  uBA=ubackbuffer;
  uBB=&ubackbuffer[1];
  fFA=ffrontbuffer;
  fFB=&ffrontbuffer[1];
  fBA=fbackbuffer;
  fBB=&fbackbuffer[1];

  if(fb[0]=='/') // pre-check
  {
    if(ubackbuffer[0])
    {
      if(fbackbuffer[fbackbuffer[0]]==0)
        ubackbuffer[fbackbuffer[0]]=0;
    }
  }
  for(a=0;a<x-1;a++)
  {
  b=a+1;
    if(fb[a]=='/')
    {
      if(fb[b]=='/')
      {
        if(*uBB)
        {
          *uFA=*uBB+2;
          *fFA=*fBB;
          if(*fFA<a) //foo
            ffrontbuffer[*fFA]=a;
          else //foo is stil in back.
            fbackbuffer[*fFA]=a;
        }
      }
      else
      {
        *fFA=b;
        *uFA=1;
        *fFB=a;
        *uFB=2;
      }
    }
    else
    {
      if(fb[b]=='/')
      {
        if(*uBA && *uBB)
        {
          if(*fBA==b) //end of cycle
          {
            cc++;
            if(lc<*uBA+*uBB+1)
              lc=*uBA+*uBB+1;
          }
          else //conector of cycles
          {
            if(*fBA<=a)ffrontbuffer[*fBA]=*fBB;
            else fbackbuffer[*fBA]=*fBB;
            if(*fBB<=b)
            {
              ffrontbuffer[*fBB]=*fBA;
              ufrontbuffer[*fBB]+= 1+*uBA+*uBB;
            }
            else
            {
              fbackbuffer[*fBB]=*fBA;
              ubackbuffer[*fBB]+= 1+*uBA+*uBB;
            }
          }
        }
        else //special's deletions
        {
          if(*uBA)
          {
            if(*fBA>a)
              ubackbuffer[*fBA]=0;
            else
              ufrontbuffer[*fBA]=0;
          }
          else
          {
            if(*uBB)
            {
              if(*fBB>b)
                ubackbuffer[*fBB]=0;
              else
                ufrontbuffer[*fBB]=0;
            }
          }

        }
      }
      else // slide to da rajt
      {
        if(*uBA)
        {
          *uFB=*uBA+2;
          *fFB=*fBA;
          if(*fFB<b) //foo is in front.
            ffrontbuffer[*fFB]=b;
          else //foo is stil in back.
            fbackbuffer[*fFB]=b;
        }
      }
    }
  uFA=uFB++;
  uBA=uBB++;
  fFA=fFB++;
  fBA=fBB++;
  }
  if(fb[x-1]!='/')
  {
    if(ubackbuffer[x-1])
    {
      if(ffrontbuffer[fbackbuffer[x-1]]==x-1)
        ufrontbuffer[fbackbuffer[x-1]]=0;
    }
  }

}

void one()
{
  flip();
  cc=lc=0;
  for(int l=0;l<y;l++)
      oneline();

 if(cc)cout << cc << " Cycles; the longest has length "
            << lc << "." << endl;
 else  cout << "There are no cycles." << endl;
}


int main()
{
  int i=0;
  ufrontbuffer=ubuff1;
  ubackbuffer=ubuff2;
  ffrontbuffer=fbuff1;
  fbackbuffer=fbuff2;

  cin >> x >> y;
  while(x || y)
  {
    cout << "Maze #" << ++i << ":" << endl;
    one();
    cout << endl;
    cin >> x >> y;
  }
  return 0;
}


//@END_OF_SOURCE_CODE


