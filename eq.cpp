#include <iostream.h>
#include <time.h>
#include <stdlib.h>
#include "eq.h"
int main(){
	int rownania,niewiadome;
	cout << "Zanim zaczniemy obliczenia, podaj epsilon>0, uzywane do porownan"<<endl;
	cin>> epsilon;//ten z eq.h
	cout << "Podaj: liczbe rownan oraz liczbe niewiadomych - oddzielone odstepem" << endl;
	cin >> rownania >> niewiadome;
	eqset e(rownania,niewiadome);
	cout << "Mozesz wybrac jeden ze schematycznych ukladow rownan, badz wlasny:" << endl;
	cout << "0 - podam recznie" << endl;
	cout << "1 - macierz Hilberta: H[i][j]= 1/(i+j-1)" << endl;
	cout << "2 - macierz wymuszajaca duze wspolczynniki (-1 pod przekatna)"<< endl;
	cout << "Podaj swoj wybor:" << endl;
	int wybor;
	cin >> wybor;
	switch(wybor){
		case 0:
			cout << "Dla kazdego rownania podaj sume,a potem wspolczynniki stojace przy niewiadomych" << endl;	
			for(int r=0;r<rownania;r++){
				number suma;
				cin >> suma;
				e.ustawsume(r,suma);
				for(int c=0;c<niewiadome;c++){
					number wspolczynnik;
					cin>> wspolczynnik;
					e.ustawwspolczynnik(r,c,wspolczynnik);
				}
			}
			break;
		case 1:
			for(int r=0;r<rownania;r++){
				e.ustawsume(r,1);
				for(int c=0;c<niewiadome;c++)
					e.ustawwspolczynnik(r,c,1.0/(r+c+1));
			}
			break;
		case 2:
			for(int r=0;r<rownania;r++){
				e.ustawsume(r,r);
				for(int c=0;c<niewiadome;c++){
					if(c==r || c==(niewiadome-1))
						e.ustawwspolczynnik(r,c,1.0);
					else if(c<r)
						e.ustawwspolczynnik(r,c,-1.0);
					else if(c>r)
						e.ustawwspolczynnik(r,c,0);
				}
			}
			break;
		case 4:
			cout << "Prosze podac dolny i gorny zakres z jakiego losowane maja byc liczby:" << endl;
			float dolny,gorny;
			srand( time( 0 ) );			
			cin >> dolny >> gorny;
			for(r=0;r<rownania;r++){
				e.ustawsume(r,dolny+(gorny-dolny)*rand()/RAND_MAX);
				for(c=0;c<niewiadome;c++)
					e.ustawwspolczynnik(r,c,dolny+(gorny-dolny)*rand()/RAND_MAX);
			}
		break;
		default:
			cout << "no minimum powagi" << endl;
			return 0;
	}
	eqset * metoda[4];
	metoda[0]=new eqset(e);
	metoda[1]=new eqset_elementy_glowne_kolumn(e);
	metoda[2]=new eqset_elementy_glowne_wierszy(e);
	metoda[3]=new eqset_elementy_glowne_podmacierzy(e);
	cout << "Zaimplementowane metody:" << endl;
	cout << "0 - bez wyboru elementu glownego" << endl;
	cout << "1 - wybor elementu maksymalnego w kolumnie" << endl;
	cout << "2 - wybor elementu maksymalnego w wierszu" << endl;
	cout << "3 - wybor elementu maksymalnego w calej podmacierzy" << endl;
	cout.precision(20);
	for(int m=0;m<4;m++){
		if(metoda[m]->solve()){
			number maxblad=0;
			for(int r=0;r<rownania;r++){
				number suma=0;
				for(int n=0;n<niewiadome;n++)
					suma+=metoda[m]->wynik(n)*e.uklad[r][n+1];
				number blad=abs(e.uklad[r][0]-suma);
				if(blad>maxblad)
					maxblad=blad;
			}
			cout << endl << "metoda #" << m << " dala wynik z bledem:" << maxblad << endl;
			cout << "proponujac rozwiaznie:" << endl;
			for(int n=0;n<niewiadome;n++)
				cout << metoda[m]->wynik(n) << ' ';
		}else{
			cout <<endl<< "metoda #" << m << " uznala ze uklad jest nierozwiazywalny" << endl;
		}
		cout << endl;
	}
	return 0;
}
/*
3 3
7 1 1 1
16 2 2 4
9 2 2 3

3 3
7 1 1 1
16 2 2 4
9 2.001 2 3.001

5 5
1 -1 0 1 2 3
1 0 1 2 3 4
1 1 2 3 4 5
1 2 3 4 5 6
1 3 4 5 6 7
*/
