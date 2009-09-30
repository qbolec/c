#include<stdio.h>
#include<stdlib.h>

/***********************************************/

class pole{
public:
    int typ;	// 0-puste 1-niedostepne 2-swoj_czolg 3-swoja_armata 4-wrogi_czolg 5-wroga_armata
    int zycie;  // pkt. zycia
};
class poz{
public:
    int x,y;
};

int n,m,t;
pole plansza[32][32];

/***********************************************/

void wczytaj(void);
void atakuj(void);
void inicjuj(void);
void czolg(int x, int y);
void armata(int x, int y);
void wyslij(poz pozycja, poz strzal, poz ruch);

poz strzal_czolg(poz pozycja);
poz ruch_czolg(poz pozycja);
poz strzal_armata(poz pozycja);
poz ruch_armata(poz pozycja);

/************ MAIN *****************************/

int main(void){
    inicjuj();
    while(t){
	wczytaj();
	atakuj();
	t--;
	fflush(NULL);
    }
    return 0;
}

/************ INICJACJA ************************/

void inicjuj(void){
    scanf("%i %i %i\n",&n,&m,&t);
//    printf("%i %i %i\n",n,m,t);
}

/************ TURA ******************************/

void wczytaj(void){
    int i,j;
    int x,y,u,v;
    for (i=1 ;i <= n ;i++)
	for(j=1 ;j <= m ;j++){
	    scanf("%i %i %i %i",&x,&y,&u,&v);
	    plansza[x][y].typ = u;
	    plansza[x][y].zycie = v;
	}
}

void atakuj(void){
    int x, y;
    for (x=1 ;x <= n ;x++)
	for(y=1 ;y <= m ;y++){
	    if (plansza[x][y].typ == 2) 
		czolg(x,y);
	    else if (plansza[x][y].typ == 3) 
		armata(x,y);
	}
    printf("0\n");
}

/************ EJDNOSTKI *************************/

void czolg(int x, int y){
    poz strzal, ruch, pozycja;
    pozycja.x = x; pozycja.y = y;
        
    strzal = strzal_czolg(pozycja);
    ruch = ruch_czolg(pozycja);
    wyslij(pozycja, strzal, ruch);
}

void armata(int x, int y){
    poz strzal, ruch, pozycja;
    pozycja.x = x; pozycja.y = y;
        
    strzal = strzal_armata(pozycja);
    ruch = ruch_armata(pozycja);
    wyslij(pozycja, strzal, ruch);
}

/*********** MYSLENIE ***************************/
inline int sign(int l){
    if (l>0)
	return 1;
    if (l==0)
	return 0;
    else 
	return -1;
}

poz strzal_czolg(poz pozycja){
    int i,j;
    int max = 0;
    poz strzal;
    strzal.x = 0; strzal.y = 0;
    int cel[3][3];
    
    for (i = pozycja.x - 1; i <= pozycja.x + 1; i++)
	for (j = pozycja.y - 1; j <= pozycja.y + 1; j++)
	    if ((i>0) && (j>0) && (i<=n) && (j<=m)) 
		if ((plansza[i][j].typ == 4) || (plansza[i][j].typ == 5))
		    if ((cel[1 + i - pozycja.x][1 + j - pozycja.y] = 30 - plansza[i][j].zycie) > max){
			max = 30 - plansza[i][j].zycie;
			strzal.x=i; strzal.y=j;
		    }
	    
    return strzal;
}

poz ruch_czolg(poz pozycja){
    int i,j;
    int r = 8;
    int max = 0;

    poz ruch = pozycja, tmp;

    poz ruchy[9] ;
    ruchy[0].x = pozycja.x - 1; ruchy[0].y = pozycja.y -1;
    ruchy[1].x = pozycja.x - 1; ruchy[1].y = pozycja.y   ;
    ruchy[2].x = pozycja.x - 1; ruchy[2].y = pozycja.y +1;
    ruchy[3].x = pozycja.x    ; ruchy[3].y = pozycja.y -1;
    ruchy[4].x = pozycja.x    ; ruchy[4].y = pozycja.y;
    ruchy[5].x = pozycja.x    ; ruchy[5].y = pozycja.y +1;
    ruchy[6].x = pozycja.x + 1; ruchy[6].y = pozycja.y -1;
    ruchy[7].x = pozycja.x + 1; ruchy[7].y = pozycja.y   ;
    ruchy[8].x = pozycja.x + 1; ruchy[8].y = pozycja.y +1;
    
    for(i = pozycja.x - r; i <= (pozycja.x + r); i++)
	for(j = pozycja.y - r; j <= (pozycja.y + r); j++)
	    if ((i>0) && (j>0) && (i<=n) && (j<=m)) 
		if ((plansza[i][j].typ == 5) /*|| (plansza[i][j].typ == 4)*/){
		    tmp = ruchy[sign(i - pozycja.x)*3 + sign(j - pozycja.y) + 4];
		    if (plansza[tmp.x][tmp.y].typ == 0){
			ruch = tmp;
			return ruch;
		    }
		}
		else if (plansza[i][j].typ == 4){
		;
		}

    return ruch;
}

/*** armata *****/
int wart_strz_arm(int x, int y){
    int i,j;
    int wart = 0;
    
    for (i=x-1; i<=x+1; i++)
	for (j=y-1 ;j<=y+1; j++)
	    if ((i>0) && (j>0) && (i<=n) && (j<=m)) 
		switch (plansza[i][j].typ){
		    case 2: wart -=  1/*plansza[i][j].zycie*/ ;break;
		    case 3: wart -=  5/*plansza[i][j].zycie*/ ;break;
		    case 4: wart +=  1/*plansza[i][j].zycie*/ ;break;
		    case 5: wart +=  /*5*/12 - plansza[i][j].zycie ;break;
		}
    return wart;
}

poz strzal_armata(poz pozycja){
    int i,j;
    int max = 0;
    poz strzal;
    strzal.x = 0; strzal.y = 0;
    int /*cel[9][9]*/ tmp;

    for (i = pozycja.x - 4; i <= pozycja.x + 4; i++)
	for (j = pozycja.y - 4; j <= pozycja.y + 4; j++)
	    if ((i>0) && (j>0) && (i<=n) && (j<=m)) 
//		if ((plansza[i][j].typ == 4) || (plansza[i][j].typ == 5))
		    if ((/*cel[4 + i - pozycja.x][4 + j - pozycja.y]*/tmp = wart_strz_arm(i,j)/*30 - plansza[i][j].zycie*/) > max){
			max = tmp ;//wart_strz_arm(i,j)/*30 - plansza[i][j].zycie*/;
			strzal.x=i; strzal.y=j;
		    }
	
    return strzal;
}

poz ruch_armata(poz pozycja){
    int i,j;
    int r = 10;
    int max = 0;

    poz ruch = pozycja, tmp;

    poz ruchy[9] ;
    ruchy[0].x = pozycja.x - 1; ruchy[0].y = pozycja.y -1;
    ruchy[1].x = pozycja.x - 1; ruchy[1].y = pozycja.y   ;
    ruchy[2].x = pozycja.x - 1; ruchy[2].y = pozycja.y +1;
    ruchy[3].x = pozycja.x    ; ruchy[3].y = pozycja.y -1;
    ruchy[4].x = pozycja.x    ; ruchy[4].y = pozycja.y;
    ruchy[5].x = pozycja.x    ; ruchy[5].y = pozycja.y +1;
    ruchy[6].x = pozycja.x + 1; ruchy[6].y = pozycja.y -1;
    ruchy[7].x = pozycja.x + 1; ruchy[7].y = pozycja.y   ;
    ruchy[8].x = pozycja.x + 1; ruchy[8].y = pozycja.y +1;
    
    for(i = pozycja.x - r; i <= (pozycja.x + r); i++)
	for(j = pozycja.y - r; j <= (pozycja.y + r); j++)
	    if ((i>0) && (j>0) && (i<=n) && (j<=m)) 
		if ((plansza[i][j].typ == 5) /*|| (plansza[i][j].typ == 4)*/){
		    tmp = ruchy[sign(i - pozycja.x)*3 + sign(j - pozycja.y) + 4];
		    if (plansza[tmp.x][tmp.y].typ == 0){
			ruch = tmp;
			return ruch;
		    }
		}

    return ruch;
}

/*********** WYSYLANIE **************************/

void wyslij(poz pozycja, poz strzal, poz ruch){
    printf("%i %i %i %i %i %i\n",pozycja.x ,pozycja.y ,strzal.x,strzal.y,ruch.x,ruch.y);
}
