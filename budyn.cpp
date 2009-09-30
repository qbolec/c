#include <iostream.h>
#include <conio.h>
/* program sluzacy do sprawdzania czy studentowi nalezy sie stypendium*/
int main() {
   float srednia;
   float niedobor;
   const float sredniaminimalna=3.8;  //minimalna srednia potrzebna do otrzymania stypendium
   int niedoborproc;
   char menu;
   cout<<"Witamy w programie, ktory sprawdzi czy nalezy Ci sie stypendium za wyniki w nauce! \n";
   start:
   do {
      cout<<"Podaj swoja srednia:";
      cin>>srednia;
      if ((srednia<2)||(srednia>5)){
         cout<<"Srednia musi zawierac sie w przedziale od 2.0 do 5.0\n";
      }
      else{
         if (srednia>=sredniaminimalna){
     cout<<"Przysluguje Ci stypendium za wyniki w nauce. Po zajeciach zglos sie do dziekana!!! \n";
         }
         else{
     niedobor=sredniaminimalna-srednia;
     niedoborproc=(niedobor*100)/srednia;
     cout<<"Przykro mi. Twoja srednia "<< srednia <<" jest za niska, abys mogl ubiegac sie o stypendium. \n";
     cout<<"Popraw ja o "<< niedobor <<" albo "<< niedoborproc <<" procent. \n";
         }
      }
   cout<<"Jesli chcesz kontynuowac prace z programem nacisnij (k). \n";
   cout<<"Jesli chcesz opuscic program nacisnij dowolny przycisk.";
   cin>>menu;
   }while(menu=='k');
cout<<"Dziekujemy za prace z programem";
return 0;
}
