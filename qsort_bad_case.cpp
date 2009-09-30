#include<cstdio>
int * tablica;
void qsort1(int lewy, int prawy) {
//  int v=tablica[(lewy+prawy)/2];
  int v_id=(lewy+prawy)/2;
  int temp;
  /*
  do {
    while (tablica[i]<v) i++;
    while (tablica[j]>v) j--;
    if (i<=j) {
      temp=tablica[i]; tablica[i]=tablica[j]; tablica[j]=temp; i++; j--;
    }
  } while (i<=j);
  jesli v jest minimalnym elementem [a jest;P]
  to efektem wykonania powyzszej petli jest:
    1. i sie nie zmienia [bo nie ma elementow mniejszych od v]
    2. j dochodzi do pozycji v_id [bo to jedyna pozycja dla ktorej tablica[j]>v ==false]
    3. jesli left<=v_id  to nastepuje zamiana (wystarczy do tego aby tablica miala >2 elementy)
    4. wpp koniec
    5. w nastepnej iteracji i rzecz jasna zmienic sie nie moze
    6. o ile v_id byl najmniejszy, to j bedzie sie zmniejszalo nonstop, az dojedzie do left
    7. o ile i<=j to cos sie stanie, ale przeciez i=left+1, zas j=left -> nic sie nie stanie
  */
  temp=tablica[lewy]; tablica[lewy]=tablica[v_id]; tablica[v_id]=temp; 
  if (lewy+1<prawy) qsort1(lewy+1, prawy);
}
int *order;
int main(){
  int n=128000;
  tablica=new int[n];
  for(int i=0;i<n;i++)
    tablica[i]=i;
  qsort1(0,n-1);
  order=new int[n];
  for(int i=0;i<n;i++)
    order[tablica[i]]=i;
  printf("%d\n",n);
  for(int i=0;i<n;i++)
    printf("%d %d\n",order[i],order[i]);
    
}
