#include <stdio.h>/* bez tej biblioteki nie ma co sie brac za pliki*/
unsigned long hash(char * nazwapliku){
	/*	nieco lepiej byloby wczytac na raz caly plik do tablicy
		a nastepnie wyliczyc owa funkcje hashujaca tak jak jest w tresci
		zadania, ale wole pokazac jak sie czyta po jednym znaku*/
	FILE * fd=fopen(nazwapliku,"rb");/*otwieram plik w trypie ReadBinary*/
	unsigned long g,h=0;
	while(!feof(fd)){/*do poki jest jeszcze cos czego nie przeczytano*/
		h= (h<<4)+getc(fd);/*wczytuje JEDEN znak z pliku*/
		g= h & 0xF0000000;
		h^=g|(g>>24);/* w tresci zadania bylo if(g) ale zauwaz ze jesli g==0 to nic sie nie stanie*/
	}
	fclose(fd);/*zamykamy plik*/
	return h % 65521 +1;
}
unsigned long characters(char * nazwapliku){
	/*  ta funkcja zmierzy mi dlugosc pliku */
	FILE * fd=fopen(nazwapliku,"rb");/*otwieram plik w trypie ReadBinary*/
	unsigned long lenght=0;
	while(!feof(fd)){
		getc(fd);/*wczytuje jeden znak ale nic z nim nie robie*/
		lenght++;
	}
	return lenght;
}
unsigned long lines(char * nazwapliku){
	/*  ta funkcja zmierzy mi dlugosc pliku */
	FILE * fd=fopen(nazwapliku,"rb");/*otwieram plik w trypie ReadBinary*/
	unsigned long enters=0;
	while(!feof(fd))
		if(getc(fd)=='\n')
			enters++;/*kazdy enter to koniec jakiejs linijki*/
	return enters;/*kwestia sporna jest czy plik w ktorym nie ma Entera ma 0 czy 1 linijke*/
}
void fivelastlines(char * nazwapliku){
	/*zakladam ze plik wogole ma 5 linijek bo inaczej to moze byc dziwnie*/
	char buffer[5][256];/*tu bede przechowywac ostatnio wczytane linijki*/
	int	bufferindex=0;/*tu bede sobie pamietac gdzie zapisac nowo wczytywana linijke*/
	int letterindex=0;/*tu bede sobie pamietac ktora literke mam wypelnic*/
	FILE * fd=fopen(nazwapliku,"rb");/*otwieram plik w trypie ReadBinary*/
	char p;/*tu bede przechowywac wczytywana literke*/
	while(!feof(fd)){
		if('\n'==(buffer[bufferindex][letterindex++]=getc(fd))){
			buffer[bufferindex][letterindex]=0;
			letterindex=0;
			bufferindex++;
			if(bufferindex==5)
				bufferindex=0;
		}
	}
	fclose(fd);
	/*	plik sie nam skonczyl a w naszym buffer znajduje sie 5 ostatnich linijek
	  	oczywiscie nadal pozostaje problem co jesli na koncu pliku nie ma Enter'a ale olac to*/
	for(p=0;p<5;p++)
		printf("%s",buffer[(bufferindex+p)%5]);
}
void fivefirstlines(char * nazwapliku){
	/*zakladam ze plik wogole ma 5 linijek bo inaczej to moze byc dziwnie*/
	FILE * fd=fopen(nazwapliku,"rb");/*otwieram plik w trypie ReadBinary*/
	int lines=0;
	char p;/*tu bede przechowywac wczytywana literke*/
	while( (lines<5) && !feof(fd) ){
		p=getc(fd);
		printf("%c",p);
		if('\n'==p)
			lines++;
	}
	fclose(fd);
}

int main(int argc,char * args[]){
	if(argc<2){
		printf("skladnia %s nazwapliku",args[0]);
		/*args[0] zawiera zawsze nazwe programu, mozna wiec go uzyc aby poinstruowac usera o wlasciwej skladni*/
	}else{
		printf("Plik %s zawiera %d bajtow, %d wierszy\nSuma kontrolna to :%d\n",characters(args[1]),lines(args[1]),hash(args[1]) );
		printf("Zaczyna sie tak:\n");
		fivefirstlines(args[1]);
		printf("\nKonczy sie tak:\n");
		fivelastlines(args[1]);
	}
	return 0;
}
