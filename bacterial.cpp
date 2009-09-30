#include<cstdio>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;
const double eps=1e-11;
const double EPS=1e-5;
double minx= -10000;
double maxx= -10000;
double miny= 10000;
double maxy= 10000;

typedef pair<double, double> p2;

double det( double a11,double a12,double a21,double a22){
	return  a11*a22 - a12*a21;
}
double UVsinus(const p2 & U,const p2 & V){
	return V.first*U.second - U.first*V.second;
}

double dlugosc(const p2 & p){
  return p.first*p.first + p.second*p.second;
}
p2 operator - (const p2 & A,const p2 & B){
  return p2( A.first - B.first, A.second - B.second);
}
double atam(double y,double x){
 if(x>=0){
   if(y>=0)
     return y/(x+y);
   return 4.0+y/(x-y);
 }
 if(y>=0)
   return 2.0-y/(y-x);
 return 2.0-y/(-x-y);
}
bool diffang(const p2 & A,const p2 & B){
  double a1=atam(A.second,A.first);
  double a2=atam(B.second,B.first);
  return (a1+eps<a2)||(a2+eps<a1);
}
bool cmpanganddist(const p2 & A,const p2 & B){
  double a1=atam(A.second,A.first);
  double a2=atam(B.second,B.first);
  if(a1+eps<a2)
    return true;
  if(a2+eps<a1)
    return false;
  return dlugosc(A) < dlugosc(B);
}


struct line{
  double A,B,C;
  bool nie_po_stronie_zera(const p2 & P){
    double p = A * P.first + B*P.second + C;
    return (p<eps)&&(p>-eps)||(p>eps)&&(C<-eps)||(p<-eps)&&(C>eps);
  }
  line(double A,double B,double C):A(A),B(B),C(C){}
};
double pole(const p2 &A,const p2 &B,const p2 &C){
	double ret= UVsinus( C-A,B-A)*0.5;
	return (ret<0)?-ret:ret;
}
int w,h,m;
vector<p2> punkty;


p2 przeciecie(const line & L,const line & K){
  double D=det(L.A,L.B,K.A,K.B);
  double Dx=det(-L.C,L.B,-K.C,K.B);
  double Dy=det(L.A,-L.C,K.A,-K.C);
  return p2( Dx/D , Dy/D);
}
line symetralna(const p2 & P){
  p2 S(P.first/2,P.second/2);
  double A=P.first;
  double B=P.second;
  double C= -S.first*A -S.second*B;
  return line(A,B,C);
}

vector<p2> pkt;
double add_cluster(int id){
  p2 p=punkty[id];
  pkt.clear();
  for(int i=0;i<punkty.size();i++)
    if(i!=id)
    	pkt.push_back(punkty[i]-p);

  pkt.push_back(p2(-2.0*(p.first-minx),0));
  pkt.push_back(p2(0,-2.0*(p.second-miny)));
  pkt.push_back(p2(2.0*(maxx-p.first),0));
  pkt.push_back(p2(0,2.0*(maxy-p.second)));

  sort(pkt.begin(),pkt.end(),cmpanganddist);
  int j=1;
  for(int i=1;i<pkt.size();i++)
    if(diffang(pkt[i],pkt[i-1]))
      pkt[j++]=pkt[i];
  pkt.resize(j);

  vector<p2> punkty;
  vector<line> proste;

  proste.push_back( symetralna(pkt[0]));
  proste.push_back( symetralna(pkt[1]));
  punkty.push_back( przeciecie(proste[0],proste[1]));
  for(int i=2;i<pkt.size();i++){
  	line l=symetralna(pkt[i]);
  	while(punkty.size() && l.nie_po_stronie_zera(punkty.back()) ){
  		punkty.pop_back();
  		proste.pop_back();
  	}
  	punkty.push_back(przeciecie(proste.back(),l));
  	proste.push_back(l);
  }
  int skip=0;
  bool need=true;
  while(need){
  	need=false;
  	while( punkty.size()-skip && proste[skip].nie_po_stronie_zera(punkty.back())){
    	punkty.pop_back();
  		proste.pop_back();
  		need=true;
  	}
  	//back<->front
  	while( punkty.size()-skip && proste.back().nie_po_stronie_zera(punkty[skip])){
  		skip++;
  		need=true;
  	}
  }
  p2 last=przeciecie( proste.back(),proste[skip]);
  punkty.push_back(last);  
  double area=0;
  for(int i=skip;i<punkty.size();i++){
   	area+=pole( p2(0,0) ,punkty[i] , last);
   	last=punkty[i];
 	}

/*
  deque<p2> punkty;
  deque<line> proste;

  proste.push_back( symetralna(pkt[0]));
  proste.push_back( symetralna(pkt[1]));
  punkty.push_back( przeciecie(proste[0],proste[1]));
  for(int i=2;i<pkt.size();i++){
  	line l=symetralna(pkt[i]);
  	while(punkty.size() && l.nie_po_stronie_zera(punkty.back()) ){
  		punkty.pop_back();
  		proste.pop_back();
  	}
  	punkty.push_back(przeciecie(proste.back(),l));
  	proste.push_back(l);
  }
  bool need=true;
  while(need){
  	need=false;
  	while( punkty.size() && proste.front().nie_po_stronie_zera(punkty.back())){
    	punkty.pop_back();
  		proste.pop_back();
  		need=true;
  	}
  	//back<->front
  	while( punkty.size() && proste.back().nie_po_stronie_zera(punkty.front())){
    	punkty.pop_front();
  		proste.pop_front();
  		need=true;
  	}
  }

  punkty.push_front( przeciecie( proste.back(),proste.front()) );
  punkty.push_back(punkty.front());
  double area=0;
  for(int i=1;i<punkty.size();i++)
   	area+=pole( p2(0,0) ,punkty[i] , punkty[i-1]);*/
  return area;
}


int main(){
  while(1){
	 scanf("%d %d",&w,&h);
   if(w==0 || h==0)
     return 0;
   minx=0;
   maxx=w;
   miny=0;
   maxy=h;
   punkty.clear();
	 scanf("%d",&m);
   for(int i=0;i<m;i++){
     double x,y;
      scanf("%lf %lf",&x,&y);
      if(x==minx)
      	x+=EPS;
      if(x==maxx)
      	x-=EPS;
      if(y==miny)
      	y+=EPS;
      if(y==maxy)
      	y-=EPS;
      punkty.push_back(p2(x,y));
   }
   vector< pair<double,int> > results;
   for(int i=0;i<m;i++)
     results.push_back(make_pair(add_cluster(i)+eps, i+1) );
   sort(results.begin(),results.end());
   for(int i=m;i--;)
     printf("%03d%14.2lf\n",results[i].second,results[i].first);
	  printf("\n");
	}
	return 0;
}
