/*
	Wierzê
*/

#include <iostream.h>

int flow[404][404];
int beenhere[404];
struct node
{
	int sc;
	int * sa;
};
node graph[404];
int n;//n jest od 1 do 200
int s;
int d;
void wczytaj()
{
	cin >> n;
	s=0;
	d=2*n+1;
	for(int x=1;x<=n;x++)
	{
		flow[s][x]=1;
		flow[x][s]=0;

	}
	for(int x=n+1;x<=2*n;x++)
	{
		flow[x][d]=1;
		flow[d][x]=0;
	}
	for(int y=1;y<=n;y++)
		for(int x=1;x<=n;x++)
		{
			char a;
			cin >> a;
			if(a == 'B')
			{
				flow[x][n+y]=1;
				flow[n+y][x]=0;
			}
			else
			{
				flow[x][n+y]=0;
				flow[n+y][x]=0;
			}
		}	
	for(int i=0;i<=d;i++)
	{
		graph[i].sc=0;
		for(int j=0;j<=d;j++)
		{
			if(flow[i][j]+flow[j][i]>0)
			{
				graph[i].sc++;
			}
		}
		graph[i].sa = new int[graph[i].sc];
		int f=0;
		for(int j=0;j<=d;j++)
		{
			if(flow[i][j]+flow[j][i]>0)
			{
				graph[i].sa[f++]=j;
			}
		}
		
	}
}
long flowflood(int id,int fl)//0 jesli nie da sie nic dopompowac albo tyle ile sie udalo
{
	if( id == d)
	{
		return fl;
	}
	beenhere[id]=1;
	for(int si=0;si<graph[id].sc;si++)
	{
		int si2=graph[id].sa[si];
		if( beenhere[si2] ) continue;
		if(flow[id][si2]>0)
		{
			int m=flow[id][si2];
			if(m >fl )m=fl;
			flow[id][si2]-=m;
			flow[si2][id]+=m;
			int x=flowflood(  si2 , m );
			if( x > 0)return x;
			flow[id][si2]+=m;
			flow[si2][id]-=m;
		}
	}
	beenhere[id]=0;
	return 0;
}
void wypisz()
{
	for(int x=1;x<=n;x++)
		for(int y=1;y<=n;y++)
		{
			if(flow[x][n+y] + flow[n+y][x] >0)
			{
				if(flow[x][n+y]==0)
				{
					cout << "Pole w wierszu " << y << " i kolumnie " << x << endl;
				}
			}
		}
}
int main()
{
	wczytaj();
	int x;
	while(flowflood(s,1));
	wypisz();
	return 0;
}


