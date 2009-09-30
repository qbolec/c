#include <iostream.h>

struct node{
            int sa[32];
            int   saco;
            int      f;
            };

node graph[32];

char con[32][32];

void addnode(int a, int b)
{
graph[a].sa[graph[a].saco]=b;
graph[a].saco++;
}

void flood(int w)
{
 graph[w].f=1;
 for(int i=0;i<graph[w].saco;i++)
  if(graph[graph[w].sa[i]].f==0)
     flood(graph[w].sa[i]);
}

void tonextline()
{
unsigned char spc;
cin.get(spc);
while((spc!=10) && (!cin.eof()) )
cin.get(spc);
}

void oneproblem()
{
unsigned char a,b,m;
int aa,bb,mx,gp=0;

cin >> m;
mx=(m-'A')+1;
tonextline();


for(int i=0;i<mx;i++)
{
 graph[i].f=graph[i].saco=0;
};
for(int x=0;x<mx;x++)
 for(int y=0;y<mx;y++)
  con[x][y]=0;



cin.get(a);
 
while( (a!= 10) && (!cin.eof()) )
{
  cin.get(b);
  tonextline();

  aa=a-'A';
  bb=b-'A';
  if((con[aa][bb]==0) && (aa!=bb))
  {
  addnode(aa,bb);
  addnode(bb,aa);
  con[aa][bb]=1;
  con[bb][aa]=1;
  };
  cin.get(a);
}

for(int i=0;i<mx;i++)
{
  if(graph[i].f==0)
  {
  gp++;
  flood(i);
  }
}
cout << gp << endl;
}


int main()
{
int tc;
cin >> tc;

for(int i=0;i<tc;i++)
{
 oneproblem();
 if(i!=(tc-1))cout << endl;
}
return 0;
}

