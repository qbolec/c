//MUSZA BYC CONAJMNIEJ DWA ROZNE PUNKTY
#include<algorithm>
#include<utility>
#include<vector>
#define mod(x,m)((x>=m)?x-m:x)
typedef pair<int,int> p2;
typedef long long bigint;
struct punkt{//jesli w zadaniu nie potrzeba pamietac identyfikatorow to mozna uzyc tylko p2
	p2 pos;//wspolrzedne (nie zmieniaja sie w trakcie obliczen)
	int id;//pozycja w danych wejsciowych
	punkt(int x,int y,int id):pos(x,y),id(id){}
};
bool cmpPunkt(const punkt & A,const punkt & B){
	return A.pos < B.pos;
}
vector<punkt> punkty;//dane wejsciowe, zostana przemieszane
vector<punkt> otoczkaT;//wieksze Y
vector<punkt> otoczkaB;//mniejsze Y
vector<punkt> otoczka;//bez powtorzen
int bestA;
int bestB;
bigint best;
bigint dist(p2 & A, p2 & B){//nie potrzebne w otoczce
	bigint dx=A.first-B.first;
	bigint dy=A.first-B.first;
	return dx*dx + dy*dy;
}
void check(punkt & A,punkt &B){//nie potrzebne w otoczce
	bigint d=dist(A.pos,B.pos);
	if(d>best){
		best=d;
		bestA=A.id;
		bestB=B.id;
	}
}

p2 operator -(const p2 & A,const p2 & B){
	return p2(A.first-B.first,A.second-B.second);
}
bigint UVsinus(const p2 & U,const p2 & V){
	return (bigint)V.first*(bigint)U.second - (bigint)U.first*(bigint)V.second;
}
bigint lineDist(const punkt & A,const punkt & B,const punkt & P){//nie potrzebne w otoczce
	bigint s=UVsinus(B.pos-A.pos,P.pos-A.pos);
	return (s<0)?-s:s;
}
bool ABCponizej181(const p2 & A, const p2 & B, const p2 & C){
	return (UVsinus(A-B,C-B)>=0);
}
bool ABCpowyzej179(const p2 & A, const p2 & B, const p2 & C){
	return (UVsinus(A-B,C-B)<=0);
}
void wyznaczOtoczke(){//o tyle lepsza ze czasem juz mamy posortowane punkty
	otoczkaT.clear();
	otoczkaB.clear();
	otoczka.clear();
  sort(punkty.begin(),punkty.end(),cmpPunkt);
  otoczkaT.push_back(punkty[0]);
  otoczkaT.push_back(punkty[1]);
  //T->B
  otoczkaB.push_back(punkty[0]);
  otoczkaB.push_back(punkty[1]);
  for(int i=2;i<punkty.size();i++){
  	while(otoczkaT.size()>1 && ABCponizej181( otoczkaT[otoczkaT.size()-2].pos,otoczkaT[otoczkaT.size()-1].pos,punkty[i].pos))
  		otoczkaT.pop_back();
  	otoczkaT.push_back(punkty[i]);
  	//T->B ABCponizej181->ABCpowyzej179
  	while(otoczkaB.size()>1 && ABCpowyzej179( otoczkaB[otoczkaB.size()-2].pos,otoczkaB[otoczkaB.size()-1].pos,punkty[i].pos))
  		otoczkaB.pop_back();
  	otoczkaB.push_back(punkty[i]);
  }
  for(int i=1;i<otoczkaB.size();i++)//bez pierwszego
  	otoczka.push_back(otoczkaB[i]);
  for(int i=otoczkaT.size()-2;i>=0;i--)//bez ostatniego
  	otoczka.push_back(otoczkaT[i]);
}

void najodleglejsze(){
	best=0;
	bigint mb=0;
	int b=0;
	for(int i=0;i<otoczka.size();i++)
		if(lineDist(otoczka[0],otoczka[1],otoczka[i])>mb){
			b=i;
			mb=lineDist(otoczka[0],otoczka[1],otoczka[i]);
		}
	const int s=otoczka.size();
	for(int i=0;i<s;i++){
		while(lineDist(otoczka[i],otoczka[mod((i+1),s)],otoczka[b])<lineDist(otoczka[i],otoczka[mod((i+1),s)],otoczka[mod((b+1),s)]))
			b=mod((b+1),s);
		//while(lineDist(otoczka[i],otoczka[mod((i+1),s)],otoczka[b])<lineDist(otoczka[i],otoczka[mod((i+1),s)],otoczka[mod((b+s-1),s)]))
    //b=mod((b+s-1),s);
		check(otoczka[i],otoczka[mod((i+1),s)]);
		check(otoczka[i],otoczka[b]);
		check(otoczka[mod((i+1),s)],otoczka[b]);
	}
}

#include<iostream>
void solve(){
	int n;
	cin >> n;
	punkty.clear();
	for(int i=0;i<n;i++){
		int x,y;
		cin >> x >> y;
		punkty.push_back(punkt(x,y,i));
	}
	wyznaczOtoczke();
	najodleglejsze();
  /*
	cout << "Otoczka Gorna :" << endl;
	for(int i=0;i<otoczkaT.size();i++)
		cout << otoczkaT[i].id << ':' << otoczkaT[i].pos.first << '/' << otoczkaT[i].pos.second << endl;
	cout << "Otoczka Dolna :" << endl;
	for(int i=0;i<otoczkaB.size();i++)
		cout << otoczkaB[i].id << ':' << otoczkaB[i].pos.first << '/' << otoczkaB[i].pos.second << endl;
	cout << "Otoczka :" << endl;
	for(int i=0;i<otoczka.size();i++)
		cout << otoczka[i].id << ':' << otoczka[i].pos.first << '/' << otoczka[i].pos.second << endl;
	*/
	cout << "Najodleglejsza para to :" << bestA << '-' << bestB << " ich odleglosc to:" << sqrt(best) << endl;
	/*
	for(int i=0;i<punkty.size();i++)
		for(int j=0;j<punkty.size();j++)
			if(dist(punkty[i].pos,punkty[j].pos)>best){
				cout << "NIEDOBRZE" << endl;
			}
  */
}
int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
		cout << t << "Tests left" << endl;
	}
	return 0;
}
