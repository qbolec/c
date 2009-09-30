#include<math.h>
#define free(a) if(!a)delete a
typedef double number;//tu mozna sobie zmienic typ danych na jakim liczymy
number epsilon;
template<class f>inline void swap(f &a,f &b){
	f s=a;
	a=b;
	b=s;
}
template<class f>inline f abs(f x){
	if(x<0)
		return -x;
	return x;
}
template<class f>inline int zero(f x){
	return (abs(x)<=epsilon);
}
struct eqset{
	int rows;//liczba rownan
	int cols;//liczba niewiadomych+1
	number ** uklad;//kolumna 0 oznacza sta³e
	int * permR;//permutacja wierszy: jaki wiersz wejsciowy jest w wirtualnym wierszu r
	int * permC;//permutacja kolumn: kolumna ktorej zmiennej jest w wirtualnej kolumnie c
	number * solved;//wyliczona wartosc i-tej niewiadomej
	void przestaw_wiersze(int a,int b){//wirtualna zamiana wierszy
		swap(permR[a],permR[b]);
	}
	void przestaw_kolumny(int a,int b){//wirtualna zamiana wierszy
		swap(permC[a],permC[b]);
	}
	number & wspolczynnik(int r,int c){//podaje liczbe z ukladu rownan
		return uklad[permR[r]][permC[c]];
	}
	eqset(int iloscrownan=1,int iloscniewiadomych=1):rows(iloscrownan),cols(iloscniewiadomych+1),uklad(new number *[rows]),permR(new int[rows]),permC(new int[cols]),solved(new number[cols]){//c-tor
		for(int c=0;c<cols;c++)
			permC[c]=c;
		for(int r=0;r<rows;r++){
			uklad[r]=new number[cols];
			permR[r]=r;
			for(int c=0;c<cols;c++)
				uklad[r][c]=0;
		}
	}
	void reset(int iloscrownan,int iloscniewiadomych){
		free(permR);
		free(permC);
		free(solved);
		for(int r=0;r<rows;r++)
			free(uklad[r]);
		free(uklad);
		rows=iloscrownan;
		cols=iloscniewiadomych+1;
		uklad=new number *[rows];
		permR=new int[rows];
		permC=new int[cols];
		solved=new number[iloscniewiadomych];
		for(int c=0;c<cols;c++)
			permC[c]=c;
		for(int r=0;r<rows;r++){
			uklad[r]=new number[cols];
			permR[r]=r;
			for(int c=0;c<cols;c++)
				uklad[r][c]=0;
		}
	}
	int solve(){//zwraca 0 jesli uklad nie ma jednoznacznego rozwiazania
		try{
			if(rows<cols-1)
				return 0;
			solveit(rows,cols);
			return 1;
		}catch(int){
			return 0;
		}
	}
	void ustawwspolczynnik(int rownanie,int niewiadoma,double wspolczynnik){
		uklad[rownanie][niewiadoma+1]=wspolczynnik;
	}
	void ustawsume(int rownanie,double suma){
		uklad[rownanie][0]=suma;
	}
	double wynik(int niewiadoma){
		return solved[niewiadoma];
	}
	void solveit(int rsize,int csize){
		int r,i;
		if(csize==2){
			for(r=0;r<rsize;r++)
				if(!zero(wspolczynnik(r,1))){
					solved[ permC[1]-1 ]= wspolczynnik(r,0)/wspolczynnik(r,1);
					return;
				}
			throw 0;
		}


		//tu nalezy przestawic wiersze i kolumny tak aby
		//w polu wspolczynnik(rsize-1,csize-1) bylo to co chcemy oddciac
		number best=wybierz_element_glowny(rsize-1,csize-1);
		if(zero(best))
			throw 0;
		number * main_row=uklad[permR[rsize-1]];

		for(r=rsize-2;r>=0;r--){
			number * this_row=uklad[permR[r]];
			number factor=this_row[permC[csize-1]]/best;
			if(!zero(factor))
				for(i=0;i<csize;i++)
					this_row[permC[i]]-=factor*main_row[permC[i]];

		}
		solveit(rsize-1,csize-1);
		number x=main_row[0];
		for(i=csize-2;i;i--)
			x-= main_row[ permC[i] ] * solved[ permC[i] -1];
		solved[ permC[csize-1] - 1 ] = x/best;
	}
	virtual number wybierz_element_glowny(int row,int column){
		//nic nie przestawiamy, tylko zwracamy co trzeba
		//przestawiamy tylko gdy pechowo wspolczynnik jest rowny zero
		if(zero(wspolczynnik(row,column))){
			for(int r=row-1;r>=0;r--)
				if(wspolczynnik(r,column)){
	                 przestaw_wiersze(row,r);
	                 break;
				}
		}
		return wspolczynnik(row,column);
	}
	eqset(const eqset &e):rows(0),cols(0),uklad(0),permR(0),permC(0),solved(0){
		reset(e.rows,e.cols-1);
		for(int r=0;r<rows;r++)
			for(int c=0;c<cols;c++)
				uklad[r][c]=e.uklad[r][c];
	}
};
struct eqset_elementy_glowne_kolumn:eqset{
	number wybierz_element_glowny(int row,int column){
		//przeszukujemy kolumne szukajac najwiekszej wartosci
		number best=abs(wspolczynnik(row,column));
		int bestr=row;
		for(int r=row-1;r>=0;r--)
			if(abs(wspolczynnik(r,column))>best){
				best=abs(wspolczynnik(r,column));
				bestr=r;
			}
		przestaw_wiersze(row,bestr);
		return wspolczynnik(row,column);
	}
	eqset_elementy_glowne_kolumn(const eqset &e):eqset(e){}
};
struct eqset_elementy_glowne_wierszy:eqset{
	number wybierz_element_glowny(int row,int column){
		//przeszukujemy kolumne szukajac najwiekszej wartosci
		number best=abs(wspolczynnik(row,column));
		int bestc=column;
		for(int c=column-1;c;c--)
			if(abs(wspolczynnik(row,c))>best){
				best=abs(wspolczynnik(row,c));
				bestc=c;
			}
		przestaw_kolumny(column,bestc);
		return wspolczynnik(row,column);
	}
	eqset_elementy_glowne_wierszy(const eqset &e):eqset(e){}
};
struct eqset_elementy_glowne_podmacierzy:eqset{
	number wybierz_element_glowny(int row,int column){
		//przeszukujemy kolumne szukajac najwiekszej wartosci
		number best=abs(wspolczynnik(row,column));
		int bestc=column;
		int bestr=row;
		for(int r=row;r>=0;r--)
			for(int c=column;c;c--)
				if(abs(wspolczynnik(r,c))>best){
					best=abs(wspolczynnik(r,c));
					bestc=c;
					bestr=r;
				}
		przestaw_wiersze(row,bestr);
		przestaw_kolumny(column,bestc);
		return wspolczynnik(row,column);
	}
	eqset_elementy_glowne_podmacierzy(const eqset &e):eqset(e){}
};

