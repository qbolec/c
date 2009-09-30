#include<cstdio>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;
int w,h,m;
typedef pair<double, double> p2;
const double eps=1e-20;
const double EPS=1e-6;
struct line{
  double A,B,C;
  bool nie_po_stronie_zera(p2 & P){
    double p = A * P.first + B*P.second + C;
    return (p<eps)&&(p>-eps)||(p>eps)&&(C<-eps)||(p<-eps)&&(C>eps);
  }
  line(double A,double B,double C):A(A),B(B),C(C){}
};
double det( double a11,double a12,double a21,double a22){
	return  a11*a22 - a12*a21;
}
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
vector<p2> punkty;
double safest;
p2 safestP;

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
bool cmpang(const p2 & A,const p2 & B){
  double a1=atam(A.second,A.first);
  double a2=atam(B.second,B.first);
  return (a1<a2);
}
bool cmpanganddist(const p2 & A,const p2 & B){
  double a1=atam(A.second,A.first);
  double a2=atam(B.second,B.first);
  if(a1<a2)
    return true;
  if(a1>a2)
    return false;
  return dlugosc(A) < dlugosc(B);
}

void check(int id){
  p2 p=punkty[id];

  vector<p2> pkt;
  for(int i=0;i<punkty.size();i++)
    if(i!=id)
    	pkt.push_back(punkty[i]-p);

  pkt.push_back(p2(-2.0*p.first,0));
  pkt.push_back(p2(0,-2.0*p.second));
  pkt.push_back(p2(2.0*(w-p.first),0));
  pkt.push_back(p2(0,2.0*(h-p.second)));

  sort(pkt.begin(),pkt.end(),cmpanganddist);
  vector<p2> pktnew;
  pktnew.push_back(pkt[0]);
  for(int i=1;i<pkt.size();i++){
    if( cmpang(pkt[i],pkt[i-1]) || cmpang(pkt[i-1],pkt[i]) )
      pktnew.push_back(pkt[i]);
  }
  swap(pkt,pktnew);

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

  punkty.push_back( przeciecie( proste.back(),proste.front()) );

  for(deque<p2>::iterator i=punkty.begin();i!=punkty.end();++i){
    double d= dlugosc( *i );
    if(d > safest){
      safest=d;
      safestP=p2(i->first+p.first,i->second+p.second);
    }
  }
}

void solve(){
    scanf("%d %d %d",&w,&h,&m);
    punkty.clear();

    for(int i=0;i<m;i++){
        int x,y;
        scanf("%d %d",&x,&y);

        double xx=x;
        double yy=y;
        if(x==0)
          xx+=EPS;
        else if(x==w)
          xx-=EPS;

        if(y==0)
          yy+=EPS;
        else if(y==h)
          yy-=EPS;

        punkty.push_back(p2(xx,yy));

    }


    safest=0;
    for(int i=0;i<m;i++)
      check(i);
    printf("The safest point is (%.1lf,%.1lf).\n",safestP.first+1e-9,safestP.second+1e-9);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)
      solve();
    return 0;
}
