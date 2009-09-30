/* rozwa¿my formu³e w postaci 3-CNF, niech c1,c2,...,cn bêd¹ czynnikami koniunkcji.
 * rozwa¿my zbiór wszystkich wartoœciowañ Omega, oraz zbiory C1,C2,..,Cn wartoœciowañ w których niespe³nione jest ci.
 * wystarczy teraz oszacowaæ moc C1 u C2 u ... u Cn.
 * policzymy tê moc z zasady w³¹czeñ i wy³aczeñ.
 * zauwa¿my, ¿e okreœlenie dok³adnej mocy przekroju dowolnej iloœci z tych zbiorów jest bardzo proste:
 * wystarczy policzyæ ile ró¿nych zmiennych wystêpuje w czynnikach 'c' odpowiadaj¹cych zbiorom których przekrój liczymy,
 * oraz ustaleniu czy jakaœ zmienna nie wystêpuje w nich jednoczeœnie zanegowana i niezanegowana[wtedy moc=0]
 * jesli bowiem wystepuje np. 8 zmiennych, to aby niespelnione byly czynniki je zawieraj¹ce potrzeba je wszystkie
 * ustawiæ w jeden konkretny sposób, zaœ wartoœciowanie pozosta³ych zmiennych jest nam obojêtne.
 * widaæ, ¿e wszytskich takich wartoœciowañ jest 2^(200-8) jeœli np. zmiennych by³o 200.
 *
 * Docelowo pomys³ polega na zmienieniu kolejnoœci sumowania na nastêpuj¹c¹:
 * for ilosczbiorowwprzekroju=1 to n
 *   for liczbazmiennych=1 to 3n //oczywiscie tu moze byc mniej
 *     wyznacz_liczbê_podzbiorów{C1,C2,..,Cn}, ktore maja tyle zmiennych ile trzeba
 *
 * gdyby uda³o siê wyznaczyæ tê liczbê w sposób dynamiczny, albo wprost w czasie wielomianowym to zewnêtrzne pêtle
 * zwiêkszaj¹ z³o¿onoœæ tylko wielomianowo!
 *
 * Niestety na razie nie mam pomys³u jak robiæ to dynamicznie nie alokuj¹c przy tym za du¿o pamiêci, dlatego:
 *
 * Przedstawiê algorytm, który pesymistycznie dzia³a wyk³adniczo, ma jednak tê przewagê, ¿e mo¿e bardzo szybko
 * przerwaæ obliczenia zg³aszaj¹c _prawid³owy_ wynik, i to nie tylko z odpowiedzi¹ "TAK" [co potrafi np. algorytm
 * podstawiaj¹cy wszystkie mo¿liwe wartoœciowania] ale co istotne umie tak¿e odpowiedzieæ "NIE".
 *
 * Algorytm bêdzie liczy³ bezpoœrednio z wzoru w³¹czeñ i wy³¹czeñ moc C1 u C2 u ... u Cn.
 * W ka¿dym kroku pêtli bêdzie zwiêkszana liczba zbiorów które bierzemy do przekroju.
 * W krokach nieparzystych sumujemy z plusem i jeœli na koñcu kroku nie przekroczyliœmy mocy Omegi to odpowiedŸ brzmi:
 * "TAK" [czyli formu³a jest spe³nialna]
 * W krokach parzystych sumujemy z minusem i jeœli na koñcu suma jest wiêksza od Omegi to odpowiedŸ brzmi:
 * "NIE" [czyli formu³a ta jest sprzeczna]
 *
 * Algorytm korzysta ze znanego faktu, ¿e sumy czêœciowe z zasady w³¹czeñ i wy³¹czeñ na przemian szacuj¹ wynik z
 * góry b¹dŸ z do³u.
 *
 * Ufam, ¿e ciê¿ko bêdzie znaleŸæ przyk³ad dla którego potrzeba wielu iteracji pêtli g³ównej.
 * Zauwa¿my, ¿e jeœli uda³oby siê jakoœ udowodniæ ¿e wystarczy np. 10 albo 100 iteracji [albo poprostu stwierdzimy,
 * ¿e dok³adniejsza odpowiedŸ nas nie interesuje] to algorytm jest w pe³ni wielomianowy.
 *
 * Du¿¹ zalet¹ jest te¿ to, ¿e dla algorytmu jest tak na prawdê obojêtne ile zmiennych jest, w ka¿dym nawiasie
 * wiêc nie trzeba siê bawiæ w ¿mudne doklejanie fikcyjnych zmiennych byleby tylko uzyskaæ postaæ 3CNF
 * W zupe³noœci wystarczy mu po prostu postaæ CNF.
 *
 * Poni¿ej zamieszczam moj¹ implementacjê która u¿ywa do liczenia zmiennych typu unsigned long [czyli 2^32] co
 * ogranicza jej zastosowanie do tych sytuacji w których pierwsza liczona suma czyli |C1|+|C2|+...+|Cn| < 2^32
 * Jeœli przyj¹æ, ¿e zmiennych jest z zaœ czynników n, to mój algorytm powinien dzia³aæ dobrze jeœli tylko:
 * 2^(z-3)*m < 2^32
 * dla ustalenia uwagi przyj¹³em, ¿e zmienne mog¹ siê nazywaæ 'a' - 'z' wiêc mo¿e ich byæ maxymalnie 26
 * limit na d³ugoœæ formu³y ustali³em na jeden kilobajt [chodzi wszak o prost¹ demonstracjê]
 */
#include<iostream.h>
char formula[1025];
char seen['z'-'a'+1];//tabelka w której sobie oznaczamy zmienne które s¹ wykorzystane w formule

struct czynnik{
	char * lista_atomow;// zanegowanie liczby [numeru zmiennej] oznacza ze zmienna jest zanegowana
	int ilosc_atomow;//rozwi¹zujemy CNF-SAT a nie 3-CNF-SAT wiêc pamiêtamy jeszcze dlugosc czynnika
};
czynnik cnf[100];
int n=0;//liczba czynnikow w postaci CNF
int m=0;//liczba zmiennych

char wystepuje[256];//ile razy dany atom wystêpuje ju¿ w rozwa¿anym przekroju

unsigned long OMEGA;//moc omegi
unsigned long BAD=0;//iloœæ z³ych wartoœciowañ [BAD<OMEGA <=> 'TAK']

unsigned long MOC;//iloœæ elementów w rozwa¿anym przekroju
unsigned long CZESC;//czesciowa suma

void pharse(){
	n=m=0;
	int ignore=1;//flaga sygnalizuj¹ca ¿e nie jesteœmy we wnêtrzu ¿adnego nawiasu
	int negation=0;//flaga sygnalizuj¹ca ¿e wczytano '!'
	int p,pos=0;//pozycja [liczba dotychczas wczytanych atomow w czynniku]
	int i;//index czynnika CNF
	char tmp[1024];//tymczasowa lista zmiennych wystêpuj¹cych w czynniku
	
	for(i=0;formula[i];i++){
		switch(formula[i]){
		case ')':
			cnf[n].ilosc_atomow=pos;
			cnf[n].lista_atomow=new char[pos];
			for(p=0;p<pos;p++)
				cnf[n].lista_atomow[p]=tmp[p];
			n++;
			ignore=1;
			break;
		case '(':
			ignore=0;
			negation=0;
			pos=0;
			break;
		case '!':
			if(!ignore){
				negation=1;
			}
		default:
			if(!ignore){
				if((formula[i]>='a') && (formula[i]<='z')){
					int z=formula[i]-'a';
					seen[z]=1;
					if(negation)
						z=~z;
					tmp[pos++]=z;
					if(pos==1024)
						ignore=1;
				}
			}
		}
	}
	for(i='z'-'a';i>=0;i--)
		if(seen[i])
			m++;
}
void podzbiory(int ile,int min){
	if(ile==0){
		CZESC+=MOC;
	}else{		
		for(int z=n-ile;z>=min;z--){
			int i;
			//1.sprawdzamy czy aby moc przekroju nie jest rowna 0
			int ok=1;
			for(i=0;i<cnf[z].ilosc_atomow;i++)
				if(wystepuje[~(cnf[z].lista_atomow[i])]){
					ok=0;
					break;
				}
			if(!ok)
				continue;//rozwazamy nastepny zbior Cz
			//2.updateujemy
			for(i=0;i<cnf[z].ilosc_atomow;i++){
				if(!wystepuje[cnf[z].lista_atomow[i]])
					MOC>>=1;
				wystepuje[cnf[z].lista_atomow[i]]++;
			}
			//3.wywolujemy rekurencyjnie
			podzbiory(ile-1,z+1);
			//4.sprzatamy po sobie;
			for(i=0;i<cnf[z].ilosc_atomow;i++){
				wystepuje[cnf[z].lista_atomow[i]]--;
				if(!wystepuje[cnf[z].lista_atomow[i]])
					MOC<<=1;
			}
		}
	}
}
int main(){
	cout << "Proszê wpisaæ formu³ê w postaci CNF, np. (!p | q | r) & (p | !z) & ( a|b|c|p ) : " << endl;
	cin.getline(formula,1024);
	pharse();
	OMEGA=1<<m;//tyle jest wszystkich wartoœciowañ.
	MOC=OMEGA;//inicjujemy ilosc wartoœciowañ danego przekroju
	for(int k=1;k<=n;k++){//iterujemy po iloœci zbiorow
		CZESC=0;
		podzbiory(k,0);//rekurencyjnie przelicza wszystkie podzbiory i uaktualnia zmienna BAD
		if(k&1){
			BAD+=CZESC;
			if(BAD<OMEGA){
				cout << "TAK" << endl;
				cout << "{result achieved using only:" << k << " intersections}"<<endl;
				return 0;
			}else{
				cout << "{BAD<=" << BAD << '}' << endl;
			}
		}else{
			BAD-=CZESC;
			if(BAD>=OMEGA){
				cout << "NIE" << endl;
				cout << "{result achieved using only:" << k << " intersections}"<<endl;
				return 0;
			}else{
				cout << "{BAD>=" << BAD << '}' << endl;
			}
		}		
		if(CZESC==0)//ten warunek mo¿na z³agodziæ jeœli chcemy aproxymowaæ
			break;
	}
	if(BAD<OMEGA)
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
	return 0;
}
