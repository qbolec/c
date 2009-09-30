/*   @JUDGE_ID:   14143RZ   705   C++   "Hello World"   */
#include<iostream.h>
int x,y;

struct info{
int up;
int foo;
};
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
   frontbuffer[i].up=frontbuffer[i].foo=frontbuffer[i].done=0;
}
void oneline()
{
  flip();
  int a,b;
  cin >> fb;
  for(a=0;a<x-1;a++)
  {
    b=a+1;
    switch(fb[a])
    {
      case('/'):
        switch(fb[a+1])
        {
          case('/'):
            if(backbuffer[b].up)
            {
              frontbuffer[a].up=backbuffer[b].up+2;
              frontbuffer[a].foo=backbuffer[b].foo;
              if(a>frontbuffer[a].foo) //foo is in front.
                frontbuffer[frontbuffer[a].foo].foo=a;
              else //foo is stil in back.
                backbuffer[frontbuffer[a].foo].foo=a;
            }
          break;
          case('\\')://cr8or
            frontbuffer[a].foo=b;
            frontbuffer[b].foo=a;
            frontbuffer[a].up=1;
            frontbuffer[b].up=2;
          break;
        }
      break;
      case('\\'):
        switch(fb[a+1])
        {
          case('/'):
             if(backbuffer[a].up && backbuffer[b].up)
              if(backbuffer[a].foo==b) //end of cycle
              {
                cc++;
                if(lc<backbuffer[a].up+backbuffer[b].up+1)
                  lc=backbuffer[a].up+backbuffer[b].up+1;
              }
              else //conector of cycles
              {
                frontbuffer[backbuffer[a].foo].foo=backbuffer[b].foo;
                backbuffer[backbuffer[b].foo].foo=backbuffer[a].foo;
                backbuffer[backbuffer[b].foo].up+=
                1+backbuffer[a].up+backbuffer[b].up;
              }
          break;
          case('\\'):
            if(backbuffer[a].up)
            {
              frontbuffer[b].up=backbuffer[a].up+2;
              frontbuffer[b].foo=backbuffer[a].foo;
              if(b>frontbuffer[b].foo) //foo is in front.
                frontbuffer[frontbuffer[b].foo].foo=b;
              else //foo is stil in back.
                backbuffer[frontbuffer[b].foo].foo=b;
            }
          break;
        }
      break;
    }
  }
}

void one()
{
  flip();
  cc=lc=0;
  for(int l=0;l<y;l++)
  {
    oneline();
  }

 if(cc)cout << cc << " Cycles; the longest has lenght "
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


