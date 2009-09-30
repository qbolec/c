#include<iostream.h>
#include<stdlib.h>
int m;//ilosc elementow zbioru ktory permutujemy - odtad przyjmujemy ze elementy maja numery 1..m
int n;//dana potega ... szukamy takiego A ¿e  A^n=B
const int ms=1000001;
int A[ms];//rozwiazanie
int B[ms];//dana permutacja B
int gB[ms];//najmniejsze takie g>0 ¿e  (B^g)(x)=x
int gA[ms];//najmniejsze takie g>0 ¿e  (A^g)(x)=x wyznaczone jako gA[i]=gB[i]*gcd(gB[i],n)
int h=0;//liczba cykli w B
int head[ms];//najmniejsi reprezentanci cykli w B
int tmp[ms];//tymczasowo tworzony cykl ktory wrzucimy potem do A
int np[64];//liczby pierwsze dzielace n
int npk[64];//
int nc; // for(i=0;i<nc;i++) n+= npk[i];
void cash(int n){
	for(int i=2;i<=n;i++)//ta petla moglaby isc po liczbach pierwszych ale po co?	
		if(n%i==0){//jesli jakas liczba (pierwsza!) dzieli to co zostalo z n
			np[nc]=i;//to dopisujemy ja do listy dzielnikow
			for(npk[nc]=1;n%i==0;n/=i)//dzielimy przez nia tyle razy ile wlezie
				npk[nc]*=i;//w npk[nc] zapisujemy najwieksza potege i dzielaca n
			nc++;
		}
}
int a(int b){	 //patrz DOWOD
	int res=1;
	for(int i=0;i<nc;i++)
		if(b%np[i]==0)//jesli liczba pierwsza dzieli b to
			res*=npk[i];//g[i]=n[i]
	return b*res;
}
int cmp(const void * a,const void * b){//funkcja sortujaca cykle wg gB
	return gB[*(int *)a]-gB[*(int *)b];//chodzi o to by cykle o tym samym gB oraz gA byly kolo siebie w head[]
}
int main(){
	int i,t,s;
	cin >> m >> n;//wczytywanie danych
	cash(n);
	for(i=1;i<=m;i++)//elementy numerujemy od 1 do m wlacznie
		cin >> B[i];//wczytywanie danych
	for(i=1;i<=m;i++)//dla kazdego elementu
		if(!gB[i]){//jesli jeszcze nie wyznaczylismy dla niego gB oraz gA
			head[h++]=i;//znaczy ze jest najmniejszy w swoim cyklu => dodajemy go do listy cykli
			gB[i]=1;//zaczynamy zliczac jego stopien w permutacji B [czyli kiedy wrocimy do i]
			for(s=B[i];s!=i;s=B[s])
                    gB[i]++;
            gA[i]=a(gB[i]);//wyznaczamy gA wg. wzoru [PATRZ DOWOD!!!]
            for(s=B[i];s!=i;s=B[s])
            		gB[s]=-1;//wpisujemy byleco do pozostalych elementow cyklu - interesuje nas glowa!
		}
	qsort(head,h,sizeof(int),cmp);//ustawiamy cykle w takiej kolejnosci aby kolo siebie byly "podobne"
    for(i=0;i<h;){//po kolei dla kazdej glowy cyklu
    	int Al=gA[head[i]];//chcemy utworzyc cykl o dlugosci Al
    	int Bl=gB[head[i]];//kazdy ze sklejanych cykli ma dlugosc Bl
    	int glue=Al/Bl;//wiec musimy skleic Al/Bl cykli - [PATRZ DOWOD! ze w head[] jest glue takich cykli!]
    	for(t=0;t<glue;t++){
    		int s=head[i+t];//s jest reprezentantem cyklu ktory chcemy skleic
			for(int z=0;z<Bl;z++){// A S S E R T ( Bl==gB[head[i+t]] )
				tmp[(t+n*z)%Al]=s;//elementy tego cyklu zajma pozycje przesuniete o t w odstepach co n
    			s=B[s];//przechodzimy do nastepnego elementu tego cyklu
    		}
    	}
    	for(t=1;t<Al;t++)//wklejamy utworzony cykl do tworzonego rozwiazania
    		A[tmp[t-1]]=tmp[t];
    	A[tmp[Al-1]]=tmp[0];//cykl musi byc cyklem:)
    	i+=glue;//w ten sposob zalatwilismy glue cykli z listy head[]
    }
    for(i=1;i<=m;i++)//wypisujemy wynik
    	cout << A[i] << ' ';// std::cout
	return 0;
}
/*
	Dowod poprawnosci wymaga wyjasnienia :
	1. czemu  gA[i]=gB[i]*gcd(gB[i],n) nie powoduje bledu w linijce zaznaczonej ASSERT(Bl=gB[head[i+t]])
	...i to by bylo na tyle, gdy¿ jeœli to za³o¿enie jest s³uszne to wynik jaki wypluje nasz algorytm
	2. spe³ni pok³adane w nim nadzieje tzn faktycznie bêdzie A^n=B.
	...mo¿e zacznê od pkt 2. : algorytm buduje tablice A, widac ze jest ona permutacja gdyz kazda liczba 1..m
	wystepuje w niej dokladnie raz. Budowana jest ona z cykli od dlugosci Al zaleznej od tego jakie akurat cykle
	sklejamy (bo Al=gA[head[i]] ). Oznacza to ze kazdy element na cyklu tworzonym w danym momencie bedzie mial
	docelowo taka wlasnosc ze A^Al[x]=x . Zauwazmy przy tym, ¿e faktycznie Al jest minimalnym takim wyk³adnikiem,
	¿e x wraca na swoje miejsce - jest zatem jego stopniem w permutacji A.
	(Jest tak bo tablice tmp wypelniamy ROZNYMI liczbami, a pozniej robimy z niej cykl)
	Zauwazmy jeszcze JAKIMI liczbami wype³niamy tmp[] ... zauwazmy ze:
	tmp[(t+n*z)%Al] = s;
	tmp[(t+n*(z+1)%Al] = B[s];   =>   tmp[(x+n)%Al]=B[ tmp[x] ];
	A[tmp[x]]=tmp[(x+1)%Al];
	st¹d:
	A^n[tmp[x]]=tmp[(x+n)%Al];   =>   A^n[tmp[x]]=B[ tmp[x] ]; czyli to co chcielismy!

	No to teraz moze dowod trudniejszej czesci czyli:
	czemu gA[i]=gB[i]*gcd(gB[i],n) ?
	otorz wcale tak byc nie musi...ale nic nie stoi na przeszkodzie aby tak bylo.
	duzym ulatwieniem jest to, ze wiem iz problem MA ROZWIAZANIE.
	jesli probowaliscie sobie cos rysowac to pewnie zauwazyliscie ze cykle w B tworza jakis podzial
	zbioru 1..m , zas podzial jaki tworza cykle A musi byc GRUBSZY.
	jesli nie wiecie co to znaczy to nieszkodzi...
	Mowiac scisle: jesli B^k[x]=y czyli jesli y oraz x naleza do tego samego cyklu w B, to wtedy:
		x oraz y naleza do tego samego cyklu w A, bo:
			 A^kn[x]=y
	Widac tez, ze jesli jakis cykl ma dlugosc Al w permutacji A, to jesli x nalezy do tego cyklu:
		A^Al[x]=x
	Jesli ten sam element x nalezy w permutacji B do cyklu o dlugosci Bl, to mamy:
		B^Bl[x]=x, ale te¿:
		B^Bl[x]=A^nBl[x]=A^(nBl[x] % Al[x]) [x]= x
	stad wniosek, ¿e:
		nBl[x]%Al[x]=0
	ale tak¿e (co bardzo istotne):
		n*k % Al[x]  != 0 gdy k nie jest podzielne przez Bl[x]
			(wynika to stad ze Bl[x] jest najmnijszym takim k, ¿e ...blah blah blah)
	oznaczmy
		a:= Al[x]
		b:= Bl[x]
	wiemy ¿e:
		nb%a==0
		nk%a!=0 dla 0<k<b
	zauwazmy ze z tego wynika (wrecz z definicji lcm) iz:
		nb =lcm(n,a)
	oczywiscie:
			lcm(n,a)=n*a/gcd(n,a)
	stad:
		b=a/gcd(n,a)
	przyk³adowo:
		n=2 b=2  -> a=4
		n=4 b=2  -> a=8
		n=3 b=2  -> a=2
	zauwa¿my ¿e jeœli:
		b=¹/gcd(n,¹)
		b=a/gcd(n,a)
	to jeœli weŸmiemy a'=gcd(a,¹) to mamy:
		a'/gcd(n,a')=
		gcd(a,¹)/gcd(n,gcd(a,¹))=
		gcd(a,¹)/gcd( gcd(n,a) , gcd(n,¹) )=
		gcd(a,¹)/gcd( a/b , ¹/b )=
		gcd(a,¹)/( gcd(a,¹)/b ) =
		b* gcd(a,¹)/gcd(a,¹) = b
	innymi s³owy dla ka¿dych dwóch rozwi¹zañ ich gcd te¿ jest rozwi¹zaniem.
	zatem istnieje rozwi¹zanie najmniejsze w sensie podzielnoœci.
	ka¿de inne rozwi¹zanie jest jego wielkrotnoœci¹.
	pytanie zatem jak znaleœæ najmniejsze takie a, ¿e:
		b=a/gcd(n,a)
	jak to zrobic szybko ?
		mozna to bowiem robic wolno - mamy duzo czasu wiec mozemy
		sobie stablicowac tak oto:
		int help[1000001];//globalna i wyzerowana
		for(int a=1;a<=1000000;a++){
			int tmp=a/gcd(n,a);
			if(!help[tmp])
				help[tmp]=a;
		}
	zauwa¿my ¿e:
		a=b*g  // a=Al b=Bl g=glue
		b=a/gcd(n,a)
		b=bg/gcd(n,bg)
		gcd(n,bg)*b=bg
		gcd(n,bg)=g
	jeœli zapiszemy n oraz b w systemie liczb pierwszch to zauwazymy ¿e
		min( n[i], b[i]+g[i] ) = g[i]
	jeœli szukamy minimalnego a => minimalnego g => minimalnych g[i] to:
		g[i]= 0 jeœli b[i]=0
		g[i]= n[i] w przeciwnym przypadku
	zatem mozemy sobie rozbic n na potegi liczb pierwszych aby szybko wyliczac a.
	
	teraz zrozummy czemu to dziala:
		wiemy ze jesli assercja jest spelniona to wynik jest dobry
		wiemy ze istnieje jakies rozwiazanie
		czyli wiemy ze DOBRY alorytm ktory tez jakos skleja cykle by sie nie zepsul
		wiemy ze DOBRY algorytm skleja g' cykli a nasz skleja g cykli
		wiemy ze g' jest podzielne przez g
		wiemy zatem ze w tablicy head[] jest g' cykli o tych samych wlasnosciach
		wiemy zatem ze w tablicy head[] jest g*coœ cykli o tych samych wlasnosciach
		wiemy zatem ze nasz program sie nie wyjebie		
*/
