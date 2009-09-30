/* rozwa�my formu�e w postaci 3-CNF, niech c1,c2,...,cn b�d� czynnikami koniunkcji.
 * rozwa�my zbi�r wszystkich warto�ciowa� Omega, oraz zbiory C1,C2,..,Cn warto�ciowa� w kt�rych niespe�nione jest ci.
 * wystarczy teraz oszacowa� moc C1 u C2 u ... u Cn.
 * policzymy t� moc z zasady w��cze� i wy�acze�.
 * zauwa�my, �e okre�lenie dok�adnej mocy przekroju dowolnej ilo�ci z tych zbior�w jest bardzo proste:
 * wystarczy policzy� ile r�nych zmiennych wyst�puje w czynnikach 'c' odpowiadaj�cych zbiorom kt�rych przekr�j liczymy,
 * oraz ustaleniu czy jaka� zmienna nie wyst�puje w nich jednocze�nie zanegowana i niezanegowana[wtedy moc=0]
 * jesli bowiem wystepuje np. 8 zmiennych, to aby niespelnione byly czynniki je zawieraj�ce potrzeba je wszystkie
 * ustawi� w jeden konkretny spos�b, za� warto�ciowanie pozosta�ych zmiennych jest nam oboj�tne.
 * wida�, �e wszytskich takich warto�ciowa� jest 2^(200-8) je�li np. zmiennych by�o 200.
 *
 * Docelowo pomys� polega na zmienieniu kolejno�ci sumowania na nast�puj�c�:
 * for ilosczbiorowwprzekroju=1 to n
 *   for liczbazmiennych=1 to 3n //oczywiscie tu moze byc mniej
 *     wyznacz_liczb�_podzbior�w{C1,C2,..,Cn}, ktore maja tyle zmiennych ile trzeba
 *
 * gdyby uda�o si� wyznaczy� t� liczb� w spos�b dynamiczny, albo wprost w czasie wielomianowym to zewn�trzne p�tle
 * zwi�kszaj� z�o�ono�� tylko wielomianowo!
 *
 * Niestety na razie nie mam pomys�u jak robi� to dynamicznie nie alokuj�c przy tym za du�o pami�ci, dlatego:
 *
 * Przedstawi� algorytm, kt�ry pesymistycznie dzia�a wyk�adniczo, ma jednak t� przewag�, �e mo�e bardzo szybko
 * przerwa� obliczenia zg�aszaj�c _prawid�owy_ wynik, i to nie tylko z odpowiedzi� "TAK" [co potrafi np. algorytm
 * podstawiaj�cy wszystkie mo�liwe warto�ciowania] ale co istotne umie tak�e odpowiedzie� "NIE".
 *
 * Algorytm b�dzie liczy� bezpo�rednio z wzoru w��cze� i wy��cze� moc C1 u C2 u ... u Cn.
 * W ka�dym kroku p�tli b�dzie zwi�kszana liczba zbior�w kt�re bierzemy do przekroju.
 * W krokach nieparzystych sumujemy z plusem i je�li na ko�cu kroku nie przekroczyli�my mocy Omegi to odpowied� brzmi:
 * "TAK" [czyli formu�a jest spe�nialna]
 * W krokach parzystych sumujemy z minusem i je�li na ko�cu suma jest wi�ksza od Omegi to odpowied� brzmi:
 * "NIE" [czyli formu�a ta jest sprzeczna]
 *
 * Algorytm korzysta ze znanego faktu, �e sumy cz�ciowe z zasady w��cze� i wy��cze� na przemian szacuj� wynik z
 * g�ry b�d� z do�u.
 *
 * Ufam, �e ci�ko b�dzie znale�� przyk�ad dla kt�rego potrzeba wielu iteracji p�tli g��wnej.
 * Zauwa�my, �e je�li uda�oby si� jako� udowodni� �e wystarczy np. 10 albo 100 iteracji [albo poprostu stwierdzimy,
 * �e dok�adniejsza odpowied� nas nie interesuje] to algorytm jest w pe�ni wielomianowy.
 *
 * Du�� zalet� jest te� to, �e dla algorytmu jest tak na prawd� oboj�tne ile zmiennych jest, w ka�dym nawiasie
 * wi�c nie trzeba si� bawi� w �mudne doklejanie fikcyjnych zmiennych byleby tylko uzyska� posta� 3CNF
 * W zupe�no�ci wystarczy mu po prostu posta� CNF.
 *
 * Poni�ej zamieszczam moj� implementacj� kt�ra u�ywa do liczenia zmiennych typu unsigned long [czyli 2^32] co
 * ogranicza jej zastosowanie do tych sytuacji w kt�rych pierwsza liczona suma czyli |C1|+|C2|+...+|Cn| < 2^32
 * Je�li przyj��, �e zmiennych jest z za� czynnik�w n, to m�j algorytm powinien dzia�a� dobrze je�li tylko:
 * 2^(z-3)*m < 2^32
 * dla ustalenia uwagi przyj��em, �e zmienne mog� si� nazywa� 'a' - 'z' wi�c mo�e ich by� maxymalnie 26
 * limit na d�ugo�� formu�y ustali�em na jeden kilobajt [chodzi wszak o prost� demonstracj�]
 */
#include<iostream.h>
char formula[1025];
char seen['z'-'a'+1];//tabelka w kt�rej sobie oznaczamy zmienne kt�re s� wykorzystane w formule

struct czynnik{
	char * lista_atomow;// zanegowanie liczby [numeru zmiennej] oznacza ze zmienna jest zanegowana
	int ilosc_atomow;//rozwi�zujemy CNF-SAT a nie 3-CNF-SAT wi�c pami�tamy jeszcze dlugosc czynnika
};
czynnik cnf[100];
int n=0;//liczba czynnikow w postaci CNF
int m=0;//liczba zmiennych

char wystepuje[256];//ile razy dany atom wyst�puje ju� w rozwa�anym przekroju

unsigned long OMEGA;//moc omegi
unsigned long BAD=0;//ilo�� z�ych warto�ciowa� [BAD<OMEGA <=> 'TAK']

unsigned long MOC;//ilo�� element�w w rozwa�anym przekroju
unsigned long CZESC;//czesciowa suma

void pharse(){
	n=m=0;
	int ignore=1;//flaga sygnalizuj�ca �e nie jeste�my we wn�trzu �adnego nawiasu
	int negation=0;//flaga sygnalizuj�ca �e wczytano '!'
	int p,pos=0;//pozycja [liczba dotychczas wczytanych atomow w czynniku]
	int i;//index czynnika CNF
	char tmp[1024];//tymczasowa lista zmiennych wyst�puj�cych w czynniku
	
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
	cout << "Prosz� wpisa� formu�� w postaci CNF, np. (!p | q | r) & (p | !z) & ( a|b|c|p ) : " << endl;
	cin.getline(formula,1024);
	pharse();
	OMEGA=1<<m;//tyle jest wszystkich warto�ciowa�.
	MOC=OMEGA;//inicjujemy ilosc warto�ciowa� danego przekroju
	for(int k=1;k<=n;k++){//iterujemy po ilo�ci zbiorow
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
		if(CZESC==0)//ten warunek mo�na z�agodzi� je�li chcemy aproxymowa�
			break;
	}
	if(BAD<OMEGA)
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
	return 0;
}
