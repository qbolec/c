/*===================================================================================*\
	uwaga jesli miasta sa numerowane od 0 a nie od 1 - patrz tresc zadania
		to nalezy zmienic petle w wypisz() na nastepujaca :
			for (unsigned int i=0;i<citycount;i++)
\*===================================================================================*/

//Typy Danych//

//Lista Sasiadow to w zasadzie listam z tym ze zawiera rowniez informacje o dlugosci polaczenia//
struct
listas	{
	//index miasta w tabelce m//
	unsigned int		id;
	//wskaznik do nastepnej listy//
	listas *		ne=NULL;
	//no i wreszcie dlugosc polaczenia//
	unsigned int		km;
	};




//Lista Miast to structura zawierajaca index miasta oraz wskaznik do nastepnegej listy//
struct
listam	{
	//index miasta w tabelce m//
	unsigned int		id;
	//wskaznik do nastepnej listy//
	listam *		ne=NULL;
	};



//Miasto to sructura zawierajaca dane o miescie//
struct
miasto	{
	//Minimalna odleglosc od Mc //
	unsigned long int	km=0x1111111111111111;
	//Czy odwiedzano juz to miasto?//
	char			od=0;      //od=0 nie odwiedzony , od=1 jest w kolejce , od=2 jest odwiedzony
	//Ilu s¹siadów ma to miasto//
	unsigned int		sc=0;
	//lista indexów s¹siadów - z gwiazdka bo bedziemy dodawac pierwszych elementow//
	listas	*		sa;
	};

//Dane Potrzebne przy wczytywaniu//

//m to tabelka zawierajaca wszystkie informacje o miastach jakie sobie zamarzysz//
miasto 		m[1000];
//fifo to wskaznik do pierwszego elementu kolejki ktora tak naprawde wcale nie jest fifo//
listam *	fifo;
//te dane sa wymagane przez tresc zadania//
unsigned int	citycount,mcdrivecount,hiwaycount;
//=========================================================================================================================\\
		Program :: Obsluga List Sasiadow ::
//=========================================================================================================================\\

void addne(unsigned int a,unsigned int b,unsigned int d)
{
	listas *	insertion;
	insertion= new listas;
	insertion->ne = m[a].sa;
	insertion->km = d;
	insertion->id = b;
	m[a].sa = insertion;
}

//=========================================================================================================================\\
		Program :: Obsluga Kolejki ::
//=========================================================================================================================\\

void deletefifo(unsigned int id)				//kasuje miasto id z kolejki jesli sie tam znajduje
{
	listam *	fifomover;
	listam *	prev;
	fifomover=listam;
	prev=listam;

	while(fifomover!=NULL)
	{
		if(fifomover->id=id) // to miasto juz czeka
		{
			prev->ne=fifomover->ne;
			
		}
		prev=fifomover;
	}
}

void addtofifo(unsigned int id)					//dodaje miasto do kolejki na odpowiednim miejscu
{
	char		wstawiony=0;
	listam *	fifomover;
	listam *	prev;
	fifomover=fifo;
	prev=fifo;

	listam *	insertion;
	insertion= new listam;
	insertion->id=id;	

	if(fifo==NULL)
	{
		fifo=insertion;	
		wstawiony=1;
	}

	while(fifomover!=NULL && (wstawiony==0))
	{
		if( m[fifomover->id].km > m[id].km )
		{
			insertion->ne=fifomover;
			prev->ne=insertion;
			wstawiony=1;
		}
	}
	if(wstawiony==0)
	{
			insertion->ne=NULL;
			prev->ne=insertion;
	}

}

void proced()							//przetwarza poczatek kolejki
{
	unsigned int 		id=fifo->id;
	listas *	 	sa;
	unsigned int		said;
	m[id].od=2;						//juz mozna go potraktowac jako odwiedzony
	sa= m[id].sa;
	for(int i=0;i<m[id].sc;i++)
	{
		said=sa->id;
		if(m[said].od!=2)				//jesli nieodwiedzony
		{
			if(m[said].od==1)			//jesli jes obecnie w kolejce
			{
				if(m[id].km+ sa->km   <   m[said])
				{
					m[said].km=m[id].km+ sa->km;
					deletefifo(said);
					addtofifo(said);
				}
			}
			if(m[said].od==0)			//w ogole nie ma go nawet w kolejce
			{
				m[said].km=m[id].km+ sa->km;
				m[said].od=1;			//dodajemy do kolejki
				addtofifo(said);
			}
		}
		sa=sa->ne;
	}
}
void movefoward()						//kasuje poczatek kolejki
{
	fifo=fifo->ne;
}
void gocoxem()							//przetwarza cala kolejke
{
	while (fifo!=NULL)
	{
		proced();
		movefoward();
	}
}

//=========================================================================================================================\\
		Program :: Wypisywanie Danych ::
//=========================================================================================================================\\

void wypisz()							//wypisuje dane
{
	unsigned int	dobranoc;
	for (unsigned int i=1;i=<citycount;i++)
	{
		if(m[i].km > dobranoc)dobranoc=m[i].km;
	}
	cout << dobranoc << endl;
}

//=========================================================================================================================\\
		Program :: Wczytywanie Danych ::
//=========================================================================================================================\\

void wczytajmcdrive()						//wczytuje dane dotyczace mcdrivow
{
	for(unsigned int i=1;i=<mcdrivecount;i++)
	{
		cin >> mcdriveloc;
		m[mcdrive].km=0;
		addtofifo(mcdrive);
	}	
}

void wczytajautostrady()					//wczytuje dane dotyczace polaczen
{
	unsigned int 	a,b,d;

	for(unsigned int i=1;i=<hiwaycount;i++)
	{
		cin >> a >> b >> d;
		addne(a,b,d);
		addne(b,a,d);
	}
}


void wczytaj()							//przetwarza dane wejsciowe
{
	unsigned int	mcdriveloc;
	cin >> citycount >> mcdrivecount >> hiwaycount;
	wczytajmcdrive();
	wczytajautostrady();
}

//=========================================================================================================================\\
		Program :: Main Sub ::
//=========================================================================================================================\\

int main()							//nadzoruje prace
{
	wczytaj();
	gocoxem();
	wypisz();
	return 0;
}