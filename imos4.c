#include <malloc.h>
#include <stdlib.h>
#include <string.h>
struct lista{
	struct lista * next;
	struct lista * prev;
	char	data[256];
};
void emptylist(struct lista * l){
	l->data[0]=0;
	l->next=l;
	l->prev=l;
}
void addtolist(struct lista * l, char * text){
	struct lista * nowyelement= malloc(sizeof(struct lista));/*tworzymy element ktory chcemy wstawic*/
	struct lista * test=l;/*wskaznikiem test jedziemy po liscie szukajac wpisu wiekszego od text*/
	strcpy( nowyelement->data , text);/*nowy element musi przechowywac text*/
	while( strcmp( test->data , text) <= 0 ){
		test=test->next;
		if(test==l)
			break;/*jesli przejechalismy w kolko to nie ma sensu dalej szukac*/
	}
	/*sytuacja wyglada tak ze chcemy wstawic text tuz przed test*/

	nowyelement->prev=test->prev;
	nowyelement->next=test;
	test->prev->next=nowyelement;
	test->prev=nowyelement;
}
void deletefromlist(struct lista * l,char * text){
	struct lista * test=l;/*wskaznikiem test jedziemy po liscie szukajac wpisu wiekszego od text*/
	while( strcmp( test->data , text)  ){
		test=test->next;
		if(test==l)
			return;/*nie znaleziono takie napisu*/
	}
	test->prev->next=test->next;
	test->next->prev=test->prev;
	free(test);
}
int existinlist(struct lista * l,char * text){
	struct lista * test=l;/*wskaznikiem test jedziemy po liscie szukajac wpisu wiekszego od text*/
	while( strcmp( test->data , text)  ){
		test=test->next;
		if(test==l)
			return 0;/*nie znaleziono takie napisu*/
	}
	return 1;
}

