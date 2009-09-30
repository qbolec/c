#include <iostream.h>

struct GENESIS
{
int beg[4];
int begend[16];
};

GENESIS nullo,ones[2],spawn,spawnresult;

char test[33];
int atest[33];
int N;
int GECKID;

void clear()
{
  N=0;
  GECKID=0;
  for( int t=0;t<33;t++)
   test[t]=atest[t]=0;
  ones[0]=nullo;
  ones[1]=nullo;
  spawn  =nullo;
}
int zeronone()
{
  int thereis[2]={0,0};
  int total[2]={0,0};

  for(int i=0;i<N;i++)
    thereis[atest[i]]=1;

  for(int x=0;x<8;x++)
  {
    if(GECKID & (1<<x))
    {
       ones[1].beg[(x>>1)&3]=1;
       ones[1].begend[((x<<1)&12)|(x&3)]=1;
       total[1]++;
    }
    else
    {
       ones[0].beg[(x>>1)&3]=1;
       ones[0].begend[((x<<1)&12)|(x&3)]=1;
       total[0]++;
    }
  }
  for(int x=0;x<2;x++)
    if(thereis[x] && (total[x]==0))
      return -1;

  return 0;
}
int isGE()
{
  if(zeronone()==-1)return 1;
  spawn=ones[ atest[0] ] ;

  for(int i=1;i<N;i++)
  {
    spawnresult=nullo;
    int out=0;
    int *o=ones[atest[i]].begend;
    for(int bega=0;bega<4;bega++)
      if(spawn.beg[bega])
        for(int endb=0;endb<4;endb++)
        {
          int enda=endb>>1;

          if(spawn.begend[(bega<<2)|enda] && o[(enda<<2)|endb])
          {
            out=spawnresult.beg[bega]=spawnresult.begend[(bega<<2)|endb]=1;

          }
          else
          {
            enda+=2;
            if(spawn.begend[(bega<<2)|enda] && o[(enda<<2)|endb])
            {
              out=spawnresult.beg[bega]=spawnresult.begend[(bega<<2)|endb]=1;
            }
          }
        }
    if(out==0)return 1;
    spawn=spawnresult;
  }
  for(int a=0;a<16;a+=5)
    if( spawn.begend[a]==1 ) return 0;


  return 1;
}

int main()
{
  cin >> GECKID ;

  while(!cin.eof())
  {
    cin >> N >> test;
    for(int i=0;i<N;i++)
      atest[i]=test[i]-'0';

    if(isGE()) cout << "GARDEN OF EDEN" << endl;
    else cout << "REACHABLE" << endl;

    clear();
    cin >> GECKID;
  }
}

