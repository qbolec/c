#include<iostream>
#include<vector>
using namespace std;
int niewiadome,rownania;
template<class S>
vector<S> operator *(const vector<int> & v,S c){
  vector<S> wynik(v.size(),0);
  for(int i=v.size();i--;)
    wynik[i]=v[i]*c;
  return wynik;
}
template<class S,class T>
vector<S> operator +(const vector<S> & v,const vector<T> &w){
  vector<S> wynik(v.size(),0);
  for(int i=v.size();i--;)
    wynik[i]=v[i]+w[i];
  return wynik;
}
template<class S,class T>
vector<S> operator -(const vector<S> & v,const vector<T> &w){
  vector<S> wynik(v.size(),0);
  for(int i=v.size();i--;)
    wynik[i]=v[i]-w[i];
  return wynik;
}

int main(){
  cin >> niewiadome >> rownania;
  vector<int> w[niewiadome];
  vector<int> b(rownania,0);
  for(int i=0;i<niewiadome;i++)
    w.resize(rownania,0);
  for(int r=0;r<rownania;r++){
    for(int i=0;i<niewiadome;i++)
      cin >> w[i][r];
    cin >> b[r];
  }
  vector<vector<int> > niezalezne_wektory;
  vector<int> niezalezne_wspolrzedne;
  vector<vector<double> > macierz_odwrotna;
  vector<vector<int> > geneza_wektorow;
  int i;
  for(i=0;i<niewiadome;i++)
    for(int j=0;j<rownania;j++)
      if(w[i][j]){
        niezalezne_wspolrzedne.push_back(j);
        niezalezne_wektory.push_back(w[i]);
        vector<int> jak(niewiadome,0);
        jak[i]=1;
        geneza_wektorow.push_back(jak);
        vector<double> singletonik;
        singletonik.push_back(1.0/w[i][j]);
        macierz_odwrotna.push_back(singletonik);
        goto bansuj;
      }
bansuj:
  for(;i<niewiadome;i++){
    vector<double> rozklad;
    for(int ri=0;ri<niezalezne_wspolrzedne.size();ri++){
//      int r=niezalezne_wspolrzedne[ri];
      double s=0;
      for(int c=0;c<niezalezne_wektory.size();c++)
        s+=macierz_odwrotna[ri][c]*w[i][niezalezne_wspolrzedne[c]]
      rozklad.push_back(s);
    }
    vector<double> klon(rownania,0.0);
    for(int c=0;c<rozklad.size();c++)
      klon=klon+ niezalezne_wektory[c]*rozklad[c];
    int niezalezna_wspolrzedna=-1;
    vector<double> nieredukowalne=w[i]-klon;
    for(int r=0;r<rownania;r++){
      if(abs(nieredukowalne[r])>1e-6){
        niezalezna_wspolrzedna=r;
        break;
      }
    }
    if(niezalezna_wspolrzedna>=0){
      cout << "Wspolrzedna " << niezalezna_wspolrzedna << " kolumny " << i << " jest nieredukowalna." << endl;
      niezalezne_wspolrzedne.push_back(niezalezna_wspolrzedna);
      niezalezne_wektory.push_back(w[i]);
      vector<int> jak(niewiadome,0);
      jak[niezalezna_wspolrzedna]=1;
      geneza_wektorow.push_back(jak);
      double skaler=1.0/nieredukowalne[niezalezna_wspolrzedna];
      vector<double> nowy_wiersz(niezalezne_wektory.size(),0.0);
      nowy_wiersz.back()=skaler;
      for(int r=0;r<macierz_odwrotna.size();r++)
        macierz_odwrotna[r].push_back(-rozklad[r]);
      macierz_odwrotna.push_back(nowy_wiersz);//uff
    }else{
      int niecalkowity_wspolczynnik=-1;
      for(int r=0;r<rozklad.size();r++){
        if(abs(rozklad[r]-round(rozklad[r]))>1e-6){
          niecalkowity_wspolczynnik=r;
          break;
        }
      }
      if(niecalkowity_wspolczynnik>=0){
        cout << "Wspolczynnik " << niecalkowity_wspolczynnik << "-tego wektora przy rozkladzie " << i << " kolumny jest niecalkowity." << endl;
        vector<int> okragly(rownania,0);
        for(int r=0;r<rozklad.size();r++)
          okragly=okragly+(niezalezne_wektory[r]*(int)round(rozklad[r]));
        vector<int> roznica=w[i]-okragly;
        vector<int> jak(niewiadome,0);
        jak[i]=1;
        for(int r=0;r<rozklad.size();r++)
          jak=jak - (geneza_wektorow[r]*(int)round(rozklad[r]));
        //podmieniamy wektor nr. 'niecalkowity_wspolczynnik' na 'roznica'
        niezalezne_wektory[niecalkowity_wspolczynnik]=roznica;
        geneza_wektorow[niecalkowity_wspolczynnik]=jak;
        
      }else{
        cout << "Kolumna "<<i<<" nalezy do kraty poprzednich kolumn."<<endl;
      }
    }
  }
}
