#include <iostream.h>
struct punkt
{
	short int x;
	short int y;
};
punkt rycerz[100000];
long r=0;
long rc=0;
struct list
{
	list * ne;
	long id;
};
long cox[100000];
long coxc=0;
long top10[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
list * hash[100000];
long u[100000];
struct jaskinia
{
	long maxy;
	long miny;
	long coxlink;
};
jaskinia j[100000];
void coxswap(long a,long b)
{
	long swp=cox[a];
	cox[a]=cox[b];
	cox[b]=swp;
	j[cox[a]].coxlink=a;
	j[cox[b]].coxlink=b;
}
void coxrepair(long id)
{
	if(id<2)return;
	if(-u[cox[id]]>-u[cox[id>>1]])
	{
		coxswap(id,id>>1);
		coxrepair(id>>1);
	}
}
void coxadd(long n)
{
	coxc++;
	cox[coxc]=n;
	j[n].coxlink=coxc;
	coxrepair(coxc);
}
void coxrepairdown(long id)
{
	long c1=id>>1;
	long c2=c1+1;
	if(c1>=coxc)c1=id;
	if(c2>=coxc)c2=id;
	long c=(-u[cox[c1]]>-u[cox[c2]])?c1:c2;
	if((-u[cox[id]]<-u[cox[c]]))
	{
		coxswap(id,c);
		coxrepairdown(c);
		return;
	}

}
void coxremove(long id)
{
	j[id].coxlink=-1;
	cox[id]=cox[coxc];
	coxrepairdown(id);
	coxc--;
}
long coxget()
{
	if(coxc<1)return -1;//tak dla bajera
	long toret=cox[1];
	coxremove(1);
	return toret;
}

long gethash(long x,long y)
{
	x--;y++;
	return (x^y+100000)%100000;
}
void un(long a,long b)
{
	while(u[a]>0)a=u[a];
	while(u[b]>0)b=u[b];
	if(a==b)return;//nic sie nie dzieje
	//rob cos z jaskiniami a,b
	if(u[a]<u[b])
	{
		//j[b] juz nie istnieje wiec trzeba wyjac b z kopca
		if(j[b].coxlink>=0)coxremove(j[b].coxlink);
		else
			for(long i=0;i<10;i++)
				if(top10[i]==b)top10[i]=-1;
		if(j[a].miny>j[b].miny)j[a].miny=j[b].miny;
		if(j[a].maxy<j[b].maxy)j[a].maxy=j[b].maxy;
		u[a]=u[b]-1;
		u[b]=a;
		//j[a] zwiekszyla liczebnosc
		if(j[a].coxlink>=0)coxrepair(j[a].coxlink);
	}
	else
	{
		//j[a] juz nie istnieje wiec trzeba wyjac a z kopca
		if(j[a].coxlink>=0)coxremove(j[a].coxlink);
		else
			for(long i=0;i<10;i++)
				if(top10[i]==a)top10[i]=-1;
		if(j[b].miny>j[a].miny)j[b].miny=j[a].miny;
		if(j[b].maxy<j[a].maxy)j[b].maxy=j[a].maxy;
		u[b]=u[a]-1;
		u[a]=b;
		//j[b] zwiekszyla liczebnosc
		if(j[b].coxlink>=0)coxrepair(j[b].coxlink);

	}
}
void addtolist(list * & l,long i)
{
	list * nexus=new list;
	nexus->id=i;
	nexus->ne=l;
	l=nexus;
}
void osiedl(long x,long y)
{
	long h=gethash(x,y);
	rycerz[r].x=x;
	rycerz[r].y=y;
	addtolist(hash[h],r);
	j[r].miny=y;
	j[r].maxy=y;
	coxadd(r);
	r++;
	rc++;
}
long find(list * l,long x,long y)
{
	for(;((rycerz[l->id].x!=x)||(rycerz[l->id].y!=y));l=l->ne);
	return l->id;
}

void polacz(long x1,long y1,long x2, long y2)
{
	long h1=gethash(x1,y1);
	long h2=gethash(x2,y2);
	long r1=find(hash[h1],x1,y1);
	long r2=find(hash[h2],x2,y2);
	un(r1,r2);
}
void naprawtop10()
{

	for(long i=0;i<10;i++)
		if(top10[i]!=-1)
			if((1-u[top10[i]])*10<rc)
			{//sprawdzamy czy jest >10%
				coxadd(top10[i]);
				top10[i]=-1;
			}
	long wp=0;
	for(long i=0;i<10;i++)
		if(top10[i]!=-1)
			top10[wp++]=top10[i];
	while((coxc)&&((1-u[cox[1]])*10>=rc)top10[wp++]=coxget();
	while(wp<10)top10[wp++]=-1;
}

void przelot(long y)
{
	naprawtop10();
	for(long i=0;i<10;i++)
		if(top10[i]>=0)
			if((y>=j[top10[i]].miny)&&(y<=j[top10[i]].maxy))
			{
			    rc-=1-u[top10[i]];
				cout << 1-u[top10[i]] << endl;
				top10[i]=-1;
			}
}
int main()
{
	long n;
	cin >> n;
	while(n--)
	{
		char c;
		cin >> c;
		switch(c)
		{
		case('R'):
			{
				long x,y;
				cin >> x>>y;
				osiedl(x,y);
			}
			break;
		case('K'):
			{
				long x1,y1,x2,y2;
				cin >> x1>>y1>>x2>>y2;
				polacz(x1,y1,x2,y2);
			}
			break;
		case('P'):
			{
				long y;
				cin >> y;
				przelot(y);
			}
			break;
		}
	}
	return 0;
}
