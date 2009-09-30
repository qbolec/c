//aby muc se pogadac
#include <iostream.h>
//aby muc policzyc pierwiastek (sqrt)
#include <math.h>

int main()
{
  //zadeklarujemy sobie zmienne typu wymiernego
  double a,b,c,delta,x1,x2;

  //spytamy sie o parametry
  cout << "                                            2        " << endl;
  cout << "przyjmujac ze dany wielomian jest postaci aX + bX + c" << endl;
  cout << "podaj wspolczynnik a:";
  cin >> a;
  cout << "podaj wspolczynnik b:";
  cin >> b;
  cout << "podaj wspolczynnik c:";
  cin >> c;

  //zanim zaczniemy liczyc trzeba sprawdzic czy dane maja sens
  if(a==0)
  {
    cout << "na przyszlosc prosze podac sensowna wartosc a" << endl;
    if(b==0 && c!=0)
      cout << "ta funkcja i tak nie ma miejsc zerowych" << endl;

    if(b==0 && c==0)
      cout << "ta funkcja jest jednym wielkim miejscem zerowym" << endl;

    if(b!=0)
    {
      x1= -c / b ;
      cout << "ta funkcja ma jedno miejsce zerowe x=" << x1 << endl;   
    }

    //wychodzimy nic tu po nas
    return 0;
  }


  //policzymy delte
  delta=b*b - 4*a*c;

  //jesli delta jest ujemna to brak rozwiazan
  if(delta<0)
  {
    cout << "ten wielomian nie ma miejsc zerowych" << endl;
  }

  //jesli delta jest rowna zero to (m.in.) nie ma co liczyc sqrt()
  if(delta==0)
  {
    cout << "ten wielomian ma tylko jedno rozwiazanie:" << endl;
    x1= -b / (2*a) ;
    cout << "jedyne miejsce zerowe to x=" << x1 << endl;
  }

  //jesli delta jest dodatnia to sa dwa rozwiazania
  if(delta>0)
  {
    cout << "ten wielomian ma dwa rozwiazania:" << endl;
    x1= -(b - sqrt(delta) ) / (2*a) ;
    x2= -(b + sqrt(delta) ) / (2*a) ;
    cout << "jedno miejsce zerowe to x=" << x1 << endl;
    cout << "            a drugie to x=" << x2 << endl;
  }
  

  //tak byc musi:
  return 0;
}
