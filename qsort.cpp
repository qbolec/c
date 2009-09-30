#include<iostream.h>
void qsort(int * tab,int len){//sortowanie integerow niemalejaco
	int * lewy=tab;
	int * prawy=lewy+len;
	int * end=tab+len;
	while(1){
		len=prawy-lewy;
		if(len<6){//easy case
			for(int t=1;t<len;t++){//insert sort
				int e=lewy[t];
				int *i;
				for(i=lewy+t-1;(i>=lewy)&&(i[0]>e);i--)
					i[1]=i[0];
				i[1]=e;
			}
			lewy=prawy;//done
			if(lewy==end)
				return;//jedyne wyjscie z funkcji
			int x=lewy[-1];
			while(*prawy++>=x)//odzyskujemy wskaznik na prawy:
				if(prawy==end) //sprawdzic
					break;//czy te dwie linijki sa potrzebne
			lewy[-1]=prawy[-1];//przestawiamy spowrotem
			prawy[-1]=x;
		}else{//hard case:D
			int * l=lewy;
			int * r=prawy-1;
			int x=*r;
			while(1){
				while(*l<x)l++;// po lewej byly mniejsze od x
				while((r>=lewy)&&(*r>=x))r--;
				if(l<r){
					int tmp=*l;
					*l++=*r;
					*r=tmp;//r nie zmniejszam bo to ryzykowne;D
				}else{//konec:D
					if(r<lewy){//x jest minimalny
						r=prawy-1;
						for(l=r;l>=lewy;l--)
							if(*l>x)
								*r--=*l;
						while(lewy<=r)//przesuwamy wszystkie elementy rowne x na przod
							*lewy++=x;
					}else{//ostatni element tablicy to x, zas element *r, jest mniejszy od x
						for(int * i=lewy;i<l;i++)
							if(*i>*r)
								r=i;
						prawy[-1]=*r;
						*r=x;
						prawy=l;
					}
					break;
				}
			}
		}
	}
}
const int size=10000000;
int t[size];
int main(){
	for(int i=1;i<size;i++)
		t[i]=t[i-1]*0x12ABCDEF;
	qsort(t,size);
	for(int i=1;i<size;i++)
		if(t[i-1]>t[i])
			cout << "shit";
	cout << endl;
	return 0;
}

