#include <iostream.h>
/*
	dixtra z prostym kopcem i macierzowa reprezentacja grafu.
	dane wejsciowe powinny byc w formacie:
		ilosc_wierzcholkow
		[matrix]
		wierzcholek_startowy wierzcholek_koncowy
	wierzcholki sa numerowane od 0
	odpowiedz '-1' oznacza ze nie da sie znalezc takiej drogi.
*/
const int MAX_WIERZCHOLKOW=1000; //1MB?
struct wierzcholek{
	int minkoszt;
	int kopiec_link;
	int sasiedzi[MAX_WIERZCHOLKOW];
};
wierzcholek graf[MAX_WIERZCHOLKOW];
int tmp[MAX_WIERZCHOLKOW];
int n,x,y;
int kopiec[MAX_WIERZCHOLKOW];
int inside=0;
void swap(int a,int b){
	int swp=kopiec[a];
	kopiec[a]=kopiec[b];
	kopiec[b]=swp;
	graf[kopiec[a]].kopiec_link=a;
	graf[kopiec[b]].kopiec_link=b;
}
void repair(int index){
	if(index==1)return;
	int father=index>>1;
	if(graf[kopiec[father]].minkoszt>graf[kopiec[index]].minkoszt){
		swap(index,father);
		repair(father);
	}
}
void repair_down(int index){
	int c1=index<<1;
	if(c1>inside)return;
	if(c1<inside){
		int c2=c1+1;
		if(graf[kopiec[c1]].minkoszt>graf[kopiec[c2]].minkoszt)
			c1=c2;
	}
	if(graf[kopiec[index]].minkoszt>graf[kopiec[c1]].minkoszt){
		swap(index,c1);
		repair_down(c1);
	}
}
void push(int g){
	kopiec[++inside]=g;
	graf[g].kopiec_link=inside;
	repair(inside);
}
int pop(){
	int ret=kopiec[1];
	if(inside>1){
		swap(1,inside);
		inside--;
		repair_down(1);
	}else
		inside--;
	graf[ret].kopiec_link=0;
	return ret;
}
int main(){
	cin >> n;
	if(n>MAX_WIERZCHOLKOW)
		return -1;
	for(int r=0;r<n;r++){
		for(int t=0;t<n;t++)
			cin >> graf[r].sasiedzi[t];
		graf[r].minkoszt=-1;
	}
	cin >> x >> y;
	graf[x].minkoszt=0;
	push(x);
	while(inside){
		int id=pop();
		if(id==y)
			break;
		for(int i=0;i<n;i++){
			if(graf[id].sasiedzi[i]>0){
				if((graf[i].minkoszt==-1)||(graf[i].minkoszt>graf[id].minkoszt+graf[id].sasiedzi[i])){
					graf[i].minkoszt=graf[id].minkoszt+graf[id].sasiedzi[i];
					if(graf[i].kopiec_link)
						repair(graf[i].kopiec_link);
					else
						push(i);
				}
			}
		}
	}
	cout << graf[y].minkoszt;
	return 0;
}
