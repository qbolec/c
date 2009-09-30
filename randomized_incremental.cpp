#include<cstdio>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<utility>
#include<algorithm>
#include<cassert>
#define FOR(i,n) for(int i=0;i<(int)n;i++)
const double EPS=1e-6;
const double UPS=5e10;
typedef std::vector<double> vec;
typedef std::pair< vec , double> hyperplane;
typedef std::vector< hyperplane > equations;
void round(vec & point){
  FOR(i,point.size())
    point[i]=floor(point[i]+0.5);
}
//tworzy wektor o skrajnych mozliwych wartosciach uciekajacy przed promieniowaniem
vec escape(const vec & direction){
  vec suggestion(direction.size(),UPS);
  FOR(i,direction.size())
    if(direction[i]>EPS)
      suggestion[i]*=-1;
  return suggestion;
}
//formatuje dysk twardy
void dump_vector(const vec & v){
  FOR(i,v.size())
    printf("%.0lf ",v[i]);
  puts("");
}
//sprawdza czy punkt lezy po dobrej stronie
bool goodside(const hyperplane & plane,const vec & point){
  double vector_dot_product=0;
  FOR(i,point.size())
    vector_dot_product+=point[i]*plane.first[i];
  return (vector_dot_product>= plane.second-EPS);
}
//ponizsze funkcje podstawiaja informacje ze interesuje nas dana hiperplaszczyzna
vec crop(const vec & tocrop,const vec & croper,int coordinate){
  float scale_factor=tocrop[coordinate]/croper[coordinate];
  vec croped;
  FOR(i,tocrop.size())
    if(i!=coordinate)
      croped.push_back( tocrop[i]-croper[i]*scale_factor);
  return croped;  
}
hyperplane crop(const hyperplane & tocrop,const hyperplane & croper,int coordinate){
  float scale_factor=tocrop.first[coordinate]/croper.first[coordinate];
  hyperplane croped;
  croped.first=crop(tocrop.first,croper.first,coordinate);
  croped.second = tocrop.second-croper.second*scale_factor;
  return croped;
}
//oblicza optymalnerozwiazanie ukladu wiezow we wskazanym kierunku przyjmujac best jako kandydata
vec getbestboundedsolution( const equations & eqs, vec & direction ){
  vec best=escape(direction);
  FOR(i,eqs.size()){
    if( !goodside( eqs[i], best ) ){
      equations eqs_crop;
      //znajdujemy najbardziej niezerowa wspolrzedna do zredukowania
      int z=0;
      FOR(j,direction.size())
        if(fabs(eqs[i].first[z])<fabs(eqs[i].first[j]))
          z=j;
      //tworzymy nowy uklad nierownosci, traktujac i jako rownosc sluzaca do redukowania zmiennej z          
      FOR(j,i)
        eqs_crop.push_back( crop( eqs[j],eqs[i],z) );
      vec direction_crop=crop(direction, eqs[i].first, z );
      //rekurencyjnie wyznaczamy optymalne rozwiazanie
      vec best_crop=getbestboundedsolution( eqs_crop, direction_crop );
      //kopiujemy wspolrzedne do wiekszej przestrzeni
      int jj=0;
      FOR(j,best.size())
        if(j!=z)
          best[j]=best_crop[jj++];
      //wyliczamy brakujaca wspolrzedna przy pomocy rownania i
      best[z]=0;
      double vector_dot_product=0;
      FOR(j,best.size())
        vector_dot_product+=best[j]*eqs[i].first[j];
      best[z]=(eqs[i].second-vector_dot_product)/eqs[i].first[z];
      //podobno rozwiazaniem jest wektor o calkowitych wspolrzednych
      round(best);
    }
  }
  return best;
}
int main(){
  int n,w;
  scanf("%d %d",&n,&w);
  vec start(w,0);
  vec direction(w,0);
  equations eqs(n,hyperplane());
  vec tmp(w,0);
  FOR(i,w)
    scanf("%lf",&start[i]);
  FOR(i,w)
    scanf("%lf",&direction[i]);
  FOR(i,n){
    eqs[i].first.resize(w);
    FOR(j,w)
      scanf("%lf",&tmp[j]);
    FOR(j,w){
      scanf("%lf",&eqs[i].first[j]);
      eqs[i].first[j]*=-1;
    }
    eqs[i].second=0;
    FOR(j,w)
      eqs[i].second+=eqs[i].first[j]*tmp[j];
  }  
  //random_shuffle(eqs.begin(),eqs.end());
  //*  
  //srand(time(0)+rand());
  FOR(i,eqs.size())
    swap(eqs[i],eqs[rand()%(i+1)]);      
  //*/
  vec best=getbestboundedsolution(eqs,direction);
  //*konia z rzedem temu kto mi wyjasni czemu czasem znajduje zle rozwiazanie
  FOR(i,n)
    assert(goodside( eqs[i], best ));
  //*/
  double vector_dot_product=0;
  FOR(i,w)
    vector_dot_product+=(best[i]-start[i])*direction[i];
  if(vector_dot_product<-EPS){
    FOR(i,n)
      assert(goodside( eqs[i], best ));
    while(1);
  }
  printf("%.0lf ",vector_dot_product);//czasem pomaga fabs(vector_dot_product)
  dump_vector(best);  
  return 0;
}
