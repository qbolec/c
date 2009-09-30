#include <iostream.h>
int spawningpool[256];
long t=0;
unsigned char tm=0;
unsigned char gg=0;
int main()
{
  int a=1;
   for(int f=0;f<10;f++)
   {
    for(int e=0;e<10;e++)
    {
     for(int d=0;d<10;d++)
     {
      for(int c=0;c<10;c++)
      {
       for(int b=0;b<10;b++)
       {
        for(;a<10;a++)
        {
          t++;
          tm++;
          gg+=2;
          spawningpool[gg]=1;
          if(spawningpool[tm])
            spawningpool[tm]=0;
          else
            cout << t << endl;
        }
        a=0;
        gg-=9;
       }

       gg-=9;
      }

      gg-=9;
     }

    gg-=9;
    }

   gg-=9;
   }
   cout << 1000000 << endl;

  return 0;
}


