#include <iostream.h>

class olddate
{//==================[class.olddate.to.mainpulate.simple.dates]=======
public:
   //..................:infos:................
   int day;
   int month;
   int year;
   //..................:funky:................
   unsigned long comparewith(olddate * other)
   {
    return 0;
   }
   int moveday(int direction)
   {
    if(direction==1)
    {
    }
    else
    {
    }
    return 0;
   }
   int movemonth(int direction)
   {
    if(direction==1)
    {
    }
    else
    {
    }
    return 0;
   }
   int moveyear(int direction)
   {
    if(direction==1)
    {
    }
    else
    {
    }
    return 0;
   }
   void fromcin()
   {
   }
   void setbigbang()
   {
    day= 25;
    month=6;
    year=1998;
   }
};//==================\________________________________________/=======

class newdate
{//==================[class.newdate.to.mainpulate.simple.dates]=======
public:
   //..................:infos:................
   int day;
   int year;
   int epoc;
   //..................:funky:................
   int movedays(int plusminus)
   {
    return 0;
   }
   void setbigbang()
   {
   }
   void flushtocout()
   {
   }
};//==================\________________________________________/=======

//===================[nonclass.date.std.funky]=========================
   int lenghtofyear(int year)
   {
    if((year % 4  ) != 0) return 365; // nie dzieli sie przez 4
    if((year % 100) != 0) return 366; // dzieli sie przez 4 ale nie przez 100
    if((year % 400) != 0) return 365; // dzieli sie przez 100 ale nie przez 400
    return 366;
   }
   int lenghtofmonth(int year,int month)
   {
    switch(month)
    {
    case  1:return 31;
    case  2:
    {
     return lenghtofyear(year)-337;
    }
    case  3:return 31;
    case  4:return 30;
    case  5:return 31;
    case  6:return 30;
    case  7:return 31;
    case  8:return 31;
    case  9:return 30;
    case 10:return 31;
    case 11:return 30;
    case 12:return 31;
    }
   }


int main()
{
 return 0;
}
