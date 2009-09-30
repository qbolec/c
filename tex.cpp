
#include <iostream.h>

int main()
{
char a;
int parit=0;


cin.get(a);
while(!cin.eof())
{
  if(a=='"')
  {
   if(parit==0)cout << "``";
   else cout << "''";
   parit=1-parit;
  }
  else cout.put(a);

  cin.get(a);
}

return 0;
}
