//Sluhalem rozwiazania kolegi ktory logarytm liczyl obliczajac go tylko dla 30 najbardziej znaczacych bitow
//Musze przyznac ze o uile metoda jest duzym optem to jednak jest bledna - oto dowod:


//Oto przyklad ktory pokazuje ze wg. c++ logarytm z 111111111111111111111111111111 (30 jedynek) wynosi 30 a nie 29.9
//Zreszta ten sam wynik daje Calculator w RHIDE (Alt+F4)

#include <iostream.h>
#include <math.h>

int main()
{
  double float1= 0x3FFFFFFF;
  double float2= log2( float1 );
  cout << float2;
}
//na ekranie pojawia sie 30

//Przyklad ten dowodzi ze dla np. dictsize= 630 jedynek , oraz n/m = 10 wynik moze byc bledny bo bedzie wynosil:
//  10 * (log2( 30jedynek ) + 600) = 10 * ( 630 ) = 6300

//Poprawny wynik to cos w okolicach 6299.9(..) wiec w pliku .out powinna sie znalesc 6299

//NIE WIEM CZY ISTNIEJE TEST KTORY ZAWIERA 30 JEDYNEK W NAJBARDZIEJ ZNACZACYCH BITACH - JESLI NIE TO ZNACZY ZE NIE ISTNIEJE MOZLIWOSC WERYFIKACJI CZY KTOS NIE URZYL BLEDNEGO ALGORYTMU

