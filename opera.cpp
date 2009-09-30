#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;
int max_level;
int caze;
struct p2{
  double x,y;
  p2 operator - (const p2& b)const{
    return p2(x-b.x,y-b.y);
  }
  p2 operator + (const p2&  b)const{
    return p2(x+b.x,y+b.y);
  }
  p2(double x=0,double y=0):x(x),y(y){}
  double alfa(){
    return atan2(y,x);
  }
  p2 operator * (double c)const{
    return p2(x*c,y*c);
  }
  double operator ^ (const p2&v)const{
    return x*v.x+y*v.y;
  }
  double operator *(const p2&v)const{
    return y*v.x-x*v.y;
  }
  double len()const{
    return sqrt(x*x+y*y);
  }
  p2 normalized(double l=1.0)const{
    return *this*(l/len());
  }
  bool operator ==(const p2 &v)const{
    return x==v.x && y==v.y;
  }
  bool operator < (const p2 &v)const{
    return x<v.x || x==v.x && y<v.y;
  }
};
ostream & operator << (ostream &o,p2 v){
  return o << v.x << ',' << v.y ;
}
p2 w[100];
vector<pair<double,bool> >oev[100];
const bool START=false;
const bool END=true;
int n;
double cross_t(p2 & v,p2 A,p2 B){
  double det=v.x*(B.y-A.y) -v.y*(B.x-A.x);
  double det_t=B.x*(B.y-A.y) -B.y*(B.x-A.x);
  double t=det_t/det;
  return t;
}
void cover(int id,p2 s,p2 e){
  p2 odc=w[id+1]-w[id];
  double start=((s-w[id])^odc)/odc.len();
  double end=((e-w[id])^odc)/odc.len();
//  assert(start<end);
//  cout << "oznakowuje od " << start << " do " << end << endl;
  oev[id].push_back(make_pair(start,START));
  oev[id].push_back(make_pair(end,END));
}
p2 rzut(p2 v,p2 a,p2 b){
  return v*cross_t(v,a,b);
}
p2 odbij(p2 v,p2 a,p2 b){
  p2 d=(b-a).normalized();
  p2 k=v-a;
  double common=k^d;
  return a+k-((k-(d*common))*2.0);
//  return d*(common*2.0)-k;
}
void mark(p2 o,p2 a,p2  b,int level=0);
void sweep(p2 o,p2 a,p2 b,int level=0){
//  cout << "sweep " << o << " " << a << " " << b << " " << level << endl;
  if(abs(a*b)<=1e-6)
    return;
  if(a*b<0)return;
//  assert(a*b > 0);
//  cout << "a*b=" << a*b << endl;
  p2 s=a+b;
  const double cut_t=0.5;
  double min_t=1e60;
  int hit=-1;
  for(int i=0;i<n;i++){
    p2 A=w[i]-o;
    p2 B=w[i+1]-o;
    if(A*s>0 && s*B>0){
      double t=cross_t(s,A,B);
      if(t>cut_t){
        if(t<min_t){
          min_t=t;
          hit=i;
//          cout << "TRAFILO W " << A << " -> " << B << endl;
        }else{
//          cout << A << " -> " << B << " jest za daleko : " << t << endl;
        }
      }else{
//        cout << A << " -> " << B << " jest za blisko : " <<t <<  endl;
      }
    }else{
//      cout << A << " -> " << B << " nie jest przeciety" << endl;
    }
  }
//  cout << "hit = " << hit << " czyli " << w[hit] << " " << w[hit+1] << endl;
  p2 A=w[hit]-o;
  p2 B=w[hit+1]-o;
  double ta=cross_t(a,A,B);
  double tb=cross_t(b,A,B);

  p2 odbite=odbij(o,w[hit],w[hit+1]);
//  cout << "odbite =" << odbite << endl;
  p2 hit_a=o+a*ta;
  p2 hit_b=o+b*tb;
  cover(hit,hit_a,hit_b);
  mark(odbite, hit_b-odbite,hit_a-odbite,level+1);
}
void mark(p2 o,p2 a,p2 b,int level){
  //assert(a*b>0);
  if(a*b<0)while(true);
  if(level>max_level)
    return;
//  cout << "mark " << o << " " << a << " " << b << " " << level << endl;
  pair<double,p2> po_katach[n+2];
  int m=0;
  po_katach[m++]=make_pair(a.alfa(),a);
  po_katach[m++]=make_pair(b.alfa(),b);

  for(int i=0;i<n;i++){
    p2 d=w[i]-o;
    const double t=cross_t(d,a,b);
    if(a*d>0 && d*b>0 && t<=1.0 && t>0)
      po_katach[m++]=make_pair( d.alfa(),d);
  }
//  cout << "n+2=" << n << " m=" << m << endl;
  sort(po_katach,po_katach+m);
  reverse(po_katach,po_katach+m);
  for(int i=0;i<m;i++)
    if(po_katach[i].second==a){
      rotate(po_katach,po_katach+i,po_katach+m);
      break;
    }
  for(int i=0;i<m;i++){
//    cout << "ten drugi to " << po_katach[i+1].second << endl;
    if(po_katach[i].second*po_katach[i+1].second<0)while(true);
    sweep(o,rzut(po_katach[i].second,a,b),rzut(po_katach[i+1].second,a,b),level);
    if(po_katach[i+1].second==b)
      return;
  }
//  puts("ojej");
}
bool solve(){
  n=0;
  scanf("%d %d",&n,&max_level);
  if(!n)return false;
  p2 o;
  scanf("%lf %lf",&o.x,&o.y);
  for(int i=0;i<n;i++)
    scanf("%lf %lf",&w[i].x,&w[i].y);
    
  w[n]=w[0];
  
  //dla rozgrzeweczki policzymy se pole, a co!:D
  double pole=0;
  for(int i=0;i<n;i++)
    pole+= (w[i+1].x-w[i].x)*(w[i+1].y+w[i].y)*0.5;
  if(pole<0)
    reverse(w,w+n+1);
    
  for(int i=0;i<n;i++)
    oev[i].clear();
  double empty_r=1e60;
  for(int i=0;i<n;i++){
    empty_r<?= (w[i]-o).len();
    const p2 tmp=(((w[i+1]-w[i]).normalized())*(o-w[i]));
    empty_r<?= tmp.len();
  }
  empty_r*=0.5;
//  cout << "empty_r " << empty_r<<endl;
  mark(o,p2(0,1).normalized(empty_r),p2(1,0).normalized(empty_r));
  mark(o,p2(1,0).normalized(empty_r),p2(0,-1).normalized(empty_r));
  mark(o,p2(0,-1).normalized(empty_r),p2(-1,0).normalized(empty_r));
  mark(o,p2(-1,0).normalized(empty_r),p2(0,1).normalized(empty_r));
//  for(int i=0;i<n;i++)
//    mark(o,(w[i]-o).normalized(empty_r),(w[i+1]-o).normalized(empty_r));
  double total=0;
  for(int i=0;i<n;i++){
    sort(oev[i].begin(),oev[i].end());
//    cout << "Krawedz " << w[i] << " -> " <<w[i+1] << endl;
    int opened=0;
    double start=-1;
    for(int j=0;j<oev[i].size();j++){
      if(oev[i][j].second==START){
//        cout << "[ " << oev[i][j].first << endl;
        if(opened==0)
          start=oev[i][j].first;
        opened++;
      }else{
//        cout <<oev[i][j].first << " ]" << endl;
        opened--;
        if(opened==0){
          total+=oev[i][j].first-start;
        }
      }
      assert(opened>=0);
    }
  }
  printf("Case %d: %.2lf\n",++caze,total);
  return true;
}
int main(){
  while(solve());
}
