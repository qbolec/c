#include<algorithm>
#include<vector>
#include<utility>
typedef double POS;
typedef pair<POS,POS> punkt;
const POS INF= 10000.0*10000.0;
//const POS MAXPOS=40000+1;
vector<punkt> punkty;
POS best;
int bestA;
int bestB;
POS ds(punkt & a,punkt &b){
	POS dx=a.first-b.first;
	POS dy=a.second-b.second;
	return dx*dx+dy*dy;//UWAZAC NA ZAKRESY i na typ zwracany
}
/*jesli wspolrzedne sa male mozna uzyc wariantu przez zliczanie
void sortY(vector<int> & tab){
	int cnt[MAXPOS];
	memset(cnt,0,sizeof(cnt));
	for(int i=tab.size();i--;)
		cnt[punkty[tab[i]].second]++;
	for(int i=1;i<MAXPOS;i++)
		cnt[i]+=cnt[i-1];
	vector<int> newTab;
	newTab.resize(tab.size());
	for(int i=tab.size();i--;)
		newTab[--cnt[ punkty[tab[i]].second]] = tab[i];
	swap(newTab,tab);
}
void sortX(vector<int> & tab){//rozni sie tylko second/first
	int cnt[MAXPOS];
	memset(cnt,0,sizeof(cnt));
	for(int i=tab.size();i--;)
		cnt[punkty[tab[i]].first]++;
	for(int i=1;i<MAXPOS;i++)
		cnt[i]+=cnt[i-1];
	vector<int> newTab;
	newTab.resize(tab.size());
	for(int i=tab.size();i--;)
		newTab[--cnt[ punkty[tab[i]].first]] = tab[i];
	swap(newTab,tab);
}
*/
bool Xsort(const int & a,const int &b){
	return punkty[a].first < punkty[b].first;
}

bool Ysort(const int & a,const int &b){
	return punkty[a].second < punkty[b].second;
}
void test(int i,int j){
	POS d=ds(punkty[i],punkty[j]);
	if(d<best){
		best=d;
		bestA=i;
		bestB=j;
	}
}
void findnearest(const vector<int> & Xsorted,int f,int t,const vector<int> & Ysorted){
	int n=Ysorted.size();
	switch(n){
		case 0:
		case 1:
			return;
		case 2:
			test( Ysorted[0],Ysorted[1] );
			return;
		default:
			int m=(f+t)/2;
			POS div=punkty[Xsorted[m]].first;
			vector<int> YsortedL,YsortedR,YsortedM;
			for(int i=0;i<n;i++){
				int c=Ysorted[i];
				if(punkty[c].first<div)
					YsortedL.push_back(c);
				else if(punkty[c].first>div)
					YsortedR.push_back(c);
			}
			findnearest(Xsorted,f,m,YsortedL);
			findnearest(Xsorted,m+1,t,YsortedR);
			for(int i=0;i<n;i++){
				int c=Ysorted[i];
				if(div-best < punkty[c].first &&  punkty[c].first< div+best)
					YsortedM.push_back(c);
			}
			for(int i=0;i<YsortedM.size();i++)
				for(int j=(12 <? YsortedM.size()-i);--j;)
					test( YsortedM[i],YsortedM[i+j]);
	}
}
void nearest(){
	vector<int> Xsorted;
	vector<int> Ysorted;
	for(int i=0;i<punkty.size();i++){
		Xsorted.push_back(i);
	}
	sort(Xsorted.begin(),Xsorted.end(),Xsort);
	Ysorted=Xsorted;
	stable_sort(Ysorted.begin(),Ysorted.end(),Ysort);
	/*
		sortX(Xsorted);
		Ysorted=Xsorted;
		sortY(Ysorted);
	*/
	vector<int> newXsorted;
	newXsorted.push_back(Xsorted[0]);
	for(int i=1;i<Xsorted.size();i++)
		if(punkty[Xsorted[i]].first!=punkty[Xsorted[i-1]].first)
			newXsorted.push_back(Xsorted[i]);
	swap(newXsorted,Xsorted);
  /*
	vector<int> newYsorted;
	newYsorted.push_back(Ysorted[0]);
	for(int i=1;i<Ysorted.size();i++)
		if(punkty[Ysorted[i]]!=punkty[Ysorted[i-1]])
			newYsorted.push_back(Ysorted[i]);
	swap(newYsorted,Ysorted);
  */
  if(Ysorted.size()>1){
		bestA=Ysorted[0];
		bestB=Ysorted[1];
		best=ds(punkty[bestA],punkty[bestB]);
		findnearest(Xsorted,0,Xsorted.size(),Ysorted);
	}else{
		best=INF;
	}
}
#include<cstdio>
using namespace std;

int main(){
	int n;
	while(1){
		scanf("%d",&n);
		if(!n)
			return 0;

		punkty.clear();
		for(int i=0;i<n;i++){
			double x,y;
			scanf("%lf %lf",&x,&y);
			punkty.push_back(make_pair((POS)x,(POS)y));
		}
		nearest();
		if(best<INF)
			printf("%.4lf\n",sqrt(best));
		else
			printf("INFINITY\n");
	}
	return 0;
}
