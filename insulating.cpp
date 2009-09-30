#include<cstdio>
#include<cmath>
const double piPI=2*acos(0);
using namespace std;
int x[26];
int y[26];
int n;
bool marked[505][505];
int clc=0;
int clx[300000];
int cly[300000];
int inside(int i,int j){
	int cnt=0;
	for(int k=0;k<n;k++){
		if(
			(x[k]!=x[k+1])
			&&
			(
				(x[k]<=i && i<x[k+1])
				||
				(x[k+1]<=i && i<x[k])
			)
		){
			double yy= (i-x[k])*y[k+1] + (x[k+1]-i)*y[k];
			yy/= x[k+1]-x[k];
			if(yy==(double)j)
				return 1;
			if(yy>j)
				cnt++;
		}
	}
	if(cnt&1)
		return 2;
	return 0;
}
double dist(double A,double C,double x,double y){//B=-1.0
	return fabs(A*x - y + C)/ sqrt(A*A+1.0);
}
int gcd(int a,int b){
	if(!b)
		return a;
	return gcd(b,a%b);
}
int main(){
	for(int t=1;t;t++){
		scanf("%d",&n);
		if(!n)
			return 0;

		int pole=0;
		for(int i=0;i<n;i++){
			scanf("%d %d",x+i,y+i);
			x[i]+=250;
			y[i]+=250;
		}
		x[n]=x[0];
		y[n]=y[0];
		for(int i=0;i<n;i++){
			pole+= (x[i+1]-x[i])*(y[i+1]+y[i]);
			if(x[i+1]!=x[i] && y[i+1]!=y[i]){

				int fx= x[i+1]<?x[i];
				int tx= x[i+1]>?x[i];

				int fy= y[i+1]<?y[i];
				int ty= y[i+1]>?y[i];

				int d=gcd(ty-fy, tx-fx);
				double a= (double)(y[i+1]-y[i])/(double)(x[i+1]-x[i]);
				double c= (double)y[i]-a*(double)x[i];// Ax -y + C=0
        if(ty-fy < tx-fx){
					int dx=(tx-fx)/d;
					for(int xb=fx;xb<tx;xb+=dx)
						for(int x=xb+1;x<xb+dx;x++){
							double yy=a*x+c;
							int y1=(int)floor(yy);
							int y2=(int)ceil(yy);
							if(!marked[x][y1] && dist(a,c,x,y1) <= 0.5 ){
								marked[x][y1]=true;
								clx[clc]=x;
								cly[clc]=y1;
								++clc;
							}
							if(!marked[x][y2] && dist(a,c,x,y2) <= 0.5){
								marked[x][y2]=true;
								clx[clc]=x;
								cly[clc]=y2;
							  ++clc;
							}
						}
				}else{
					int dy=(ty-fy)/d;
					for(int yb=fy;yb<ty;yb+=dy)
						for(int y=yb+1;y<yb+dy;y++){
							double xx=(double)((double)y-c)/a;
							int x1=(int)floor(xx);
							int x2=(int)ceil(xx);
							if(!marked[x1][y] && dist(a,c,x1,y) <= 0.5 ){
								marked[x1][y]=true;
								clx[clc]=x1;
								cly[clc]=y;
								++clc;
							}
							if(!marked[x2][y] && dist(a,c,x2,y) <= 0.5 ){
								marked[x2][y]=true;
								clx[clc]=x2;
								cly[clc]=y;
								++clc;
							}
						}
				}
			}
		}
		while(clc){
			--clc;
			pole-=inside(clx[clc],cly[clc]);
			marked[clx[clc]][cly[clc]]=false;
		}
		//POLE = SRODEK + OBWODOWE/2
		//INSULATING = SRODEK + OBWODOWE/2 -

		double area=piPI*(0.5*pole)*0.25;
		printf("Shape %d\nInsulating area =%.3lf cm^2\n",t,area);
	}

	return 0;
}
