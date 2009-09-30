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
p2 operator + (const p2 & A,const p2 & B){
  return p2( A.first + B.first, A.second + B.second);
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


struct line{
  double A,B,C;
  bool nie_po_stronie_zera(p2 & P){
    double p = A * P.first + B*P.second + C;
    return (p<eps)&&(p>-eps)||(p>eps)&&(C<-eps)||(p<-eps)&&(C>eps);
  }
  line(double A,double B,double C):A(A),B(B),C(C){}
};
struct trojkat{
	int id;
	p2 p[3];
	bool contains(const p2 & P){
		for(int i=0;i<3;i++){
			p2 X=P-p[i];
			p2 Y=p[(i+1)%3]-p[i];
			if(UVsinus(X,Y)>eps)
				return false;
		}
		return true;
	}
	trojkat(const p2 & A,const p2 & B,const p2 & C,int id):id(id){
		p[0]=A;
		p[1]=B;
		p[2]=C;
	}
};
struct tree{
  virtual int search(const p2 & p)=0;
};
struct treeVertical:tree{
	double div;
	tree * l;
	tree * b;
	int search(const p2 & p){
		if(p.first>div)
			return b->search(p);
		return l->search(p);
	}
	treeVertical(tree * l,tree *b,double div):div(div),l(l),b(b){}
	virtual ~treeVertical(){
		delete l;
		delete b;
	}
};
struct treeHorizontal:tree{
	double div;
	tree * l;
	tree * b;
	int search(const p2 & p){
		if(p.second>div)
			return b->search(p);
		return l->search(p);
	}
	treeHorizontal(tree * l,tree *b,double div):div(div),l(l),b(b){}
	virtual ~treeHorizontal(){
		delete l;
		delete b;
	}
};
struct treeLeaf:tree{
	vector<trojkat> t;
	int search(const p2 & p){
		for(int i=0;i<t.size();i++)
			if(t[i].contains(p))
				return t[i].id;
		return -1;
	}
	treeLeaf(const vector<trojkat> & t):t(t){}
};
tree * root=0;
int w,h,m;
vector<p2> punkty;
vector<trojkat> trojkaty;


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


void add_cluster(int id){
  p2 p=punkty[id];

  vector<p2> pkt;
  for(int i=0;i<punkty.size();i++)
    if(i!=id)
    	pkt.push_back(punkty[i]-p);

  pkt.push_back(p2(-2.0*(p.first-minx),0));
  pkt.push_back(p2(0,-2.0*(p.second-miny)));
  pkt.push_back(p2(2.0*(maxx-p.first),0));
  pkt.push_back(p2(0,2.0*(maxy-p.second)));

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

  punkty.push_front( przeciecie( proste.back(),proste.front()) );
  punkty.push_back(punkty.front());
  for(int i=1;i<punkty.size();i++)
    trojkaty.push_back(trojkat( p,p+ punkty[i] , p+punkty[i-1] , id));
}


double choose(const p2& p ,bool & first){
	return first?p.first:p.second;
}
tree * make_browser(const vector<trojkat> & t,bool vertical=false){
	if(t.size()<6)
		return new treeLeaf(t);
	vector<double> ops;
	for(int i=0;i<t.size();i++)
		for(int j=0;j<3;j++)
			ops.push_back( choose(t[i].p[j],vertical) );
	int id=ops.size()/2;
	nth_element(ops.begin(),ops.begin()+ id, ops.end() );
	double div=ops[id];
	vector<trojkat> lower;
	vector<trojkat> bigger;
	for(int i=0;i<t.size();i++){
		for(int j=0;j<3;j++)
			if(choose(t[i].p[j],vertical)>div){
				bigger.push_back(t[i]);
				break;
			}
		for(int j=0;j<3;j++)
			if(choose(t[i].p[j],vertical)<div){
				lower.push_back(t[i]);
				break;
			}
	}
	tree * l=make_browser( lower,!vertical);
	tree * b=make_browser( bigger,!vertical);
	if(vertical)
	  return new treeVertical(l,b,div);
	return new treeHorizontal(l,b,div);
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
		trojkaty.clear();
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
    for(int i=0;i<m;i++)
      add_cluster(i);
    int q;
		scanf("%d",&q);
    
        
    delete root;
    root=make_browser(trojkaty);

		for(int i=0;i<q;i++){
		  double x,y;
      scanf("%lf %lf",&x,&y);
      p2 p(x,y);
    	int id=root->search(p);
    	if(id<0)
    	 printf("NOT FOUND\n");
   	  else{
    	  printf("Point (%lf,%lf) is closest to point (%lf,%lf)\n",x,y,punkty[id].first,punkty[id].second);
	    }
		}
	}
	return 0;
}
