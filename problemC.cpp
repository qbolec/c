#include<iostream.h>
int r,c,n,k;
int a[40][40];
int v[40][40];
int h;
int maxkbydiff[100];
struct entry{
	int x;
	int y;
	int c;
};
entry que[100000];
int qr=0;
int qw=0;
void add(int x,int y,int cs){
	if(x>=c)return;
	if(x<0)return;
	if(y>=r)return;
	if(y<0)return;
	if(a[x][y]<h)return;
	if(a[x][y]-h>cs)
		cs=a[x][y]-h;
	if(v[x][y]>=0){
		if(v[x][y]<=cs)
			return;
	}
	v[x][y]=cs;
	que[qw].x=x;
	que[qw].y=y;
	que[qw].c=cs;
	qw++;
	if(qw==100000)
		qw=0;
}

void zerov(){
    for(int x=0;x<c;x++)
		for(int y=0;y<r;y++)
			v[x][y]=-1;
}
int main(){
	cin >> r >> c;
	for(int y=0;y<r;y++)
		for(int x=0;x<c;x++)
			cin >> a[x][y];
	for(int x=0;x<c;x++)
		for(int y=0;y<r;y++){
			zerov();
			h=a[x][y];
			add(x,y,0);
			while(qr!=qw){
				int x=que[qr].x;
				int y=que[qr].y;
				int c=que[qr].c;
				qr++;
				if(qr==100000)
					qr=0;
				if(c<=v[x][y]){
					add(x+1,y,c);
					add(x-1,y,c);
					add(x,y+1,c);
					add(x,y-1,c);
				}
			}
			int g[100];
			for(int i=0;i<100;i++)
				g[i]=0;
			for(int ax=0;ax<c;ax++)
				for(int ay=0;ay<r;ay++)
					if(v[ax][ay]>=0)
	            		g[v[ax][ay]]++;
	        int k[100];
	        k[0]=g[0];
	        for(int i=1;i<100;i++)
	        	k[i]=k[i-1]+g[i];
	       	for(int i=0;i<100;i++)
	       		if(k[i]>maxkbydiff[i])
	       			maxkbydiff[i]=k[i];
		}
	cin >> n;
	while(n--){
		cin >> k;
		for(int i=0;i<100;i++)
			if(maxkbydiff[i]>=k){
				cout << i << endl;
				break;
			}
	}
	return 0;
}
