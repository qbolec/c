#include<iostream.h>
#include<math.h>
int abs(int a){
	if(a<0)return -a;
	return a;
}
double D,L,xs,ys,xt,yt,dx,dy,dryy;
double water(double pos){
	double p=pos/D;
	double wt=0;
	if(p>=0){
		long p_=(long)p;
		wt=p_*2*L;
		pos-=p_*D;
		if(pos<=L)
			wt+=pos;
		else if(pos>=D-L)
			wt+=L+pos-(D-L);
		else
			wt+=L;
		return wt;
    }else
    	return -water(-pos);
}
int main(){

	while(1){
		cin >> D >> L >> xs >> ys >> xt >> yt;
		if(cin.eof())
			return 0;
		double w=water(yt)-water(ys);
		if(w<0)w=-w;
		dy=yt-ys;
		dx=xt-xs;
		if(dy<0)
			dy=-dy;
		dryy=dy-w;

		cout << "The gopher has to swim " ;
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << w << " meters and walk " ;
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << sqrt(dryy*dryy+dx*dx) << " meters." << endl;
	}
	return 0;
}
