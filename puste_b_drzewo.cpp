#include<iostream>
#include<cmath>
using namespace std;
//B - parametr B-drzewa, mimnimalna liczba kluczy w wierzcholku
//k - jaka glebokosc ma miec drzewo (1 = ma nie miec dzieci)
//s - od jakiej liczby zaczyna sie przedzial kluczy
//n - jaka ilosc kluczy mamy w przedziale
//t - minimalna liczba kluczy tego wierzcholka (maxymalna to 2*B)
void build_subtree(int b,int k,int s,int n,int t){
  //jesli elementow jest malutko, to nie mamy dzieci i koniec
  assert(n>=t);
  if(k==1){
    assert( n <= 2*b);
    cout << "{ " ;
    for(int i=1;i<=n;i++)
      cout << s++ << ' ';
    cout << '}' << endl;
    return;
  }

  //w przeciwnym razie trzeba wyznaczyc liczbe dzieci
  //w kazdym dziecku chcemy miec co najmniej B^(k-1) kluczy, a co najwyzej (2B)^(k-1)
  const int min_child_size=pow((double)b,k-1);
  const int max_child_size=min_child_size<<(k-1);
  for(int i=t;i<=2*b;i++){//zgadujemy liczbe kluczy w korzeniu
    if( (n-i)>=min_child_size*(i+1) && (n-i)<=max_child_size*(i+1) ){
      cout << "{" << endl;
      //dla kazdych x,y liczbe x mozna przedstawic jako floor(x/y)*(y - (x mod y)) + ceil(x/y)*(x mod y)
      //w tym wypadku x= n-i  , y= i+1
      const int smaller_child_size=(n-i)/(i+1);
      const int larger_child_size=smaller_child_size+1;
      const int number_of_smaller= (i+1)-(n-i)%(i+1);

      for(int c=1;c<=number_of_smaller;c++){
        build_subtree(b,k-1,s,smaller_child_size,b);
        s+=smaller_child_size;
        cout << ',' << s++ << ',' << endl ;
      }
      for(int c=number_of_smaller+1;c<=i+1;c++){
        build_subtree(b,k-1,s,larger_child_size,b);
        s+=larger_child_size;
        if(c<=i)
          cout << ',' << s++ << ',' << endl;
      }
      cout << '}' << endl;
      return;
    }
  }
  assert(false);
}
void build_tree(int b,int n){
  //znajdz najmniejsze k, takie ze (2B)^k >= n
  //k bedzie glebokoscia drzewa (korzen jest na glebokosci 1, liscie na glebokosci k)
  int k=1;
  int limit=2*b;
  for(;limit<n;k++)
    limit*=2*b;
  build_subtree(b,k,1,n,1);
}
int main(){
  int b,n;
  cin >> b >> n;
}
