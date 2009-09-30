#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
const double EPS=1e-5;
using namespace std;
int m;
struct v3{
	double p[3];
	void operator /=(double d){
		for(int i=0;i<3;i++)
			p[i]/=d;
	}
	v3(double x=0,double y=0,double z=0){
		p[0]=x;
		p[1]=y;
		p[2]=z;
	}
	v3 operator *(const v3 &V)const{
		return v3(
			p[2]*V.p[1]-p[1]*V.p[2],//bez 0
			p[0]*V.p[2]-p[2]*V.p[0],//bez 1
			p[1]*V.p[0]-p[0]*V.p[1]//bez 2
			);
	}	
  v3 operator + (const v3 & V)const{
  	return v3(
    p[0]+V.p[0],
    p[1]+V.p[1],
    p[2]+V.p[2]);
	}
  v3 operator - (const v3 & V)const{
  	return v3(
    p[0]-V.p[0],
    p[1]-V.p[1],
    p[2]-V.p[2]);
	}
	double operator ^ (const v3 & V)const{
  	return 
    p[0]*V.p[0]+
    p[1]*V.p[1]+
    p[2]*V.p[2];
	}	
};

double dist2d(const v3 & U,const v3 & V){
  double dx=U.p[0]-V.p[0];
  double dy=U.p[1]-V.p[1];
  return dx*dx+dy*dy;
}	
struct t3{
	int id[3];	
	v3 normal;
	v3 v0;
	t3(){}
	t3(int a,int b,int c,const vector<v3> & mesh){
    v0=mesh[a];
		id[0]=a;
		id[1]=b;
		id[2]=c;
		normal= (mesh[b]-v0)*(mesh[c]-v0);
	}
	void flip(){
	 swap(id[1],id[2]);
	 normal=v3()-normal;
	}
	double side(const v3 & p){
		return normal^(p-v0);
	}
};
vector<v3> mesh;
vector<t3> hull;
char mask[1000][1000];
vector< pair<double,int> > results;
double UVsin(const v3 & U,const v3 & V){
	return U.p[0]*V.p[1]-U.p[1]*V.p[0];
}
double pole(const v3 & A,const v3 & B,const v3 & C){
	return 0.5*UVsin(A-B,C-B);
}
void add(double x,double y){
	mesh.push_back(v3(x,y,x*x+y*y));
}
void make_hull(){
  hull.clear();
	hull.push_back( t3( 0,1,2,mesh ) );
	int czwarty=3;
	while(!hull[0].side( mesh[czwarty]))
    czwarty++;
  if(hull[0].side(mesh[czwarty])>0)
    hull[0].flip();
	hull.push_back(t3(czwarty,hull[0].id[0],hull[0].id[2],mesh));
	hull.push_back(t3(czwarty,hull[0].id[1],hull[0].id[0],mesh));
	hull.push_back(t3(czwarty,hull[0].id[2],hull[0].id[1],mesh));
  vector<int> dobre;
  vector<int> zle;
	for(int i=3;i<mesh.size();i++){
	  if(i==czwarty)
	   continue;   
		for(int j=0;j<hull.size();j++){
			if(hull[j].side(mesh[i])>0){			 
			  mask[ hull[j].id[0] ][ hull[j].id[1] ]++;
			  mask[ hull[j].id[1] ][ hull[j].id[2] ]++;
			  mask[ hull[j].id[2] ][ hull[j].id[0] ]++;
			  mask[ hull[j].id[1] ][ hull[j].id[0] ]--;
			  mask[ hull[j].id[2] ][ hull[j].id[1] ]--;
			  mask[ hull[j].id[0] ][ hull[j].id[2] ]--;
			  zle.push_back(j);
			}else
			  dobre.push_back(j);
	  }
    for(int j=0;j<zle.size();j++){
		  for(int k=0;k<3;k++){
		    int a=hull[zle[j]].id[k];
		    int b=hull[zle[j]].id[(k+1)%3];
		    if(mask[ a ][ b ]>0){
 		      dobre.push_back(hull.size());
		      hull.push_back( t3( a,b,i,mesh ));
		      mask[ a ][ b ]=0;
		      mask[ b ][ a ]=0;
		    }		    
      } 
    }
    int f=0;
    for(int j=0;j<dobre.size();j++)
      hull[f++]=hull[dobre[j]];
    hull.resize(f);
    dobre.clear();
    zle.clear();
	}
}
double det( double a11,double a12,double a21,double a22){
	return  a11*a22 - a12*a21;
}
v3 center(const v3 & A,const v3 & B,const v3 & C){
  double a=C.p[0]-A.p[0];
  double b=C.p[1]-A.p[1];
  double c=C.p[0]-B.p[0];
  double d=C.p[1]-B.p[1];
  double D= det(a,b,c,d);
  double L1=0.5*(-A.p[1]*A.p[1]- A.p[0]*A.p[0] +C.p[1]*C.p[1]+ C.p[0]*C.p[0]);
  double L2=0.5*(-B.p[1]*B.p[1]- B.p[0]*B.p[0] +C.p[1]*C.p[1]+ C.p[0]*C.p[0]);  
  double Dx= det(L1,b,L2,d);
  double Dy= det(a,L1,c,L2);
  if(!D)
    return A;
  return v3(Dx/D,Dy/D);  
}
int main(){
  while(1){
  	mesh.clear();
    results.clear();
	  int w,h;
	  scanf("%d %d",&w,&h);
	  if(!w || !h)
	    return 0;
    scanf("%d",&m);
	  for(int i=0;i<m;i++){
		  double x,y;
		  scanf("%lf %lf",&x,&y);
      if(x==0)
     	  x+=EPS;
      if(x==w)
      	x-=EPS;
      if(y==0)
     	  y+=EPS;
      if(y==h)
      	y-=EPS;
		   add(x,y);
		   add(-x,y);
		   add(x,-y);
		   add(2*w-x,y);
		   add(x,2*h-y);		
		   results.push_back(make_pair(0.0,i+1));
	   }
	   make_hull();	
	   for(int i=0;i<hull.size();i++){
		   v3 v[3];
    	 for(int j=0;j<3;j++)
		     v[j]=mesh[hull[i].id[j]];				
		   v3 proj[3];
		   for(int j=0;j<3;j++){
		     proj[j]= v[j]+v[(j+1)%3];
		     proj[j]/=2;
		   }		
		   v3 c=center(v[0],v[1],v[2]);
		   for(int j=0;j<3;j++){
			   int id=hull[i].id[j];
			   if(id%5 == 0){
				   results[ id/5 ].first+= pole( v[j],c,proj[j] );
				   results[ id/5 ].first+= pole( proj[(j+2)%3],c,v[j] );
		 	   }
		   }
	   }
	   sort(results.begin(),results.end());
	   for(int i=m;i--;)
		   printf("%03d%14.2lf\n",results[i].second,results[i].first);
	   printf("\n");
  }
}
