/*   @JUDGE_ID:   14143RZ   705   C++   "Hello World"   */
#include<iostream.h>

struct info{
int up;
int foo;
};

int x,y;
info buffer1[75];
info buffer2[75];
info * backbuffer;
info * frontbuffer;
int cc;
int lc;
char fb[76];
void flip()
{
  info * swap;
  swap=backbuffer;
  backbuffer=frontbuffer;
  frontbuffer=swap;
  for(int i=0;i<x;i++)
   frontbuffer[i].up=0;
}
void oneline()
{
  flip();
  int a,b;
  cin >> fb;
  info * FA;
  info * FB;
  info * BA;
  info * BB;
  FA=frontbuffer;
  FB=&frontbuffer[1];
  BA=backbuffer;
  BB=&backbuffer[1];
  if(fb[0]=='/') // pre-check
  {
    if(backbuffer[0].up)
    {
      if(backbuffer[backbuffer[0].foo].foo==0)
        backbuffer[backbuffer[0].foo].up=0;
    }
  }
  for(a=0;a<x-1;a++)
  {
  b=a+1;
    if(fb[a]=='/')
    {
      if(fb[b]=='/')
      {
        if(BB->up)
        {
          FA->up=BB->up+2;
          FA->foo=BB->foo;
          if(FA->foo<a) //foo
            frontbuffer[FA->foo].foo=a;
          else //foo is stil in back.
            backbuffer[FA->foo].foo=a;
        }
      }
      else
      {
        FA->foo=b;
        FA->up=1;
        FB->foo=a;
        FB->up=2;
      }
    }
    else
    {
      if(fb[b]=='/')
      {
        if(BA->up && BB->up)
        {
          if(BA->foo==b) //end of cycle
          {
            cc++;
            if(lc<BA->up+BB->up+1)
              lc=BA->up+BB->up+1;
          }
          else //conector of cycles
          {
            if(BA->foo<=a)frontbuffer[BA->foo].foo=BB->foo;
            else backbuffer[BA->foo].foo=BB->foo;
            if(BB->foo<=b)
            {
              frontbuffer[BB->foo].foo=BA->foo;
              frontbuffer[BB->foo].up+= 1+BA->up+BB->up;
            }
            else
            {
              backbuffer[BB->foo].foo=BA->foo;
              backbuffer[BB->foo].up+= 1+BA->up+BB->up;
            }
          }
        }
        else //special's deletions
        {
          if(BA->up)
          {
            if(BA->foo>a)
              backbuffer[BA->foo].up=0;
            else
              frontbuffer[BA->foo].up=0;
          }
          else
          {
            if(BB->up)
            {
              if(BB->foo>b)
                backbuffer[BB->foo].up=0;
              else
                frontbuffer[BB->foo].up=0;
            }
          }

        }
      }
      else // slide to da rajt
      {
        if(BA->up)
        {
          FB->up=BA->up+2;
          FB->foo=BA->foo;
          if(FB->foo<b) //foo is in front.
            frontbuffer[FB->foo].foo=b;
          else //foo is stil in back.
            backbuffer[FB->foo].foo=b;
        }
      }
    }
  FA=FB++;
  BA=BB++;

  }
  if(fb[x-1]!='/')
  {
    if(backbuffer[x-1].up)
    {
      if(frontbuffer[backbuffer[x-1].foo].foo==x-1)
        frontbuffer[backbuffer[x-1].foo].up=0;
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
  frontbuffer=buffer1;
  backbuffer=buffer2;
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


