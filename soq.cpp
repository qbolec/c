#include <fstream.h>
#include <strings.h>

int main(int c,char * * a )
{
 if(c!=3)
 {
         cout << "\n\n.:u've 2 gif a bmp and path to rgb cut:.";
         return 0;
 }
 cout << "\n\n.:tnx 4 coop:.";
 cout << "\n\n.:" << a[1]  << ":.";

 ifstream inBMP(a[1]);

char  namr[100];
char  namg[100];
char  namb[100];

strcpy(namr,a[2]);
strcpy(namg,a[2]);
strcpy(namb,a[2]);

strcat(namr,"R.chanell");
strcat(namg,"G.chanell");
strcat(namb,"B.chanell");

ofstream outR(namr);
ofstream outG(namg);
ofstream outB(namb);

char bufi;

        while(inBMP)
        {
         inBMP >> bufi;
         outR << bufi;
         inBMP >> bufi;
         outG << bufi;
         inBMP >> bufi;
         outB << bufi;
        } ;
 return 0;
}


