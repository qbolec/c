#include <fstream.h>
#include <string.h>
char ** tab=0;
int cursize=0;
int pos=0;
void resize(int newsize){
   char ** nt = new  char * [newsize];
   for(int i=0;i<cursize;i++)
     nt[i]=tab[i];
   if(tab)
    delete tab;
   tab=nt;
   cursize=newsize;
}
void wczytaj(){
   ifstream plik("dupa.txt");
   pos=0;
   while(!plik.eof()){
     char temp[256];
     plik >> temp;
     if(plik.eof())
         return;
     char * napis=new char[strlen(temp)+1];
     strcpy( napis,temp);
     if( pos >= cursize)
       resize( cursize*2+1);
     tab[pos++]=napis;
   }
}
void wypisz(){
	ofstream plik("dupa.txt");
	for(int i=0;i<pos;i++)
		plik << tab[i] << endl;
}
int main(){
   wczytaj();
   wypisz();
   return 0;
}

