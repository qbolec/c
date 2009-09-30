/*
	kolejna magiczna proba napisania wlasnej biblioteki
	mem.h
	ktora powinna miec takie magiczniusie funkcje jak:
	void * alloc(int size);
	void free(void * what);
	tym razem idea jest taka ze mamy dwa drzewa:
		w jednym s¹ wolne obszary posortowane wg. rozmiaru
		w drugim s¹ zajête obszary posortowane wg. adresu
*/
#include <stdlib.h>
typedef int link;//link to handle...
class memager{
private:
	int TOTALMEM;
	int MAXLINX;
	char * RAM;
	void **linx;
	int freeadr=0;
	inline void gc(){
		//problem jest taki ze obszary sa nieposortowane
		//trzeba by je zatem posortowac wg. kolejnosci adresow

	}
public:
	void * operator [](link lnk){
		return linx[lnk];
	}
	link alloc(int size){
		size+=sizeof(int);
		if(freeadr+size>TOTALMEM){
			gc();
			if(freeadr+size>TOTALMEM)
				exit(1);
		}
		link l;
		for(l=0;linx[l];l++);
		*(int *)&RAM[freeadr]=size;
		linx[l]=(void *)&RAM[freeadr+4];
		freeadr+=size;
		return l;
	}
	inline void free(link lnk){
		linx[lnk]=0;
	}
	memager(int size,int maxlinx){
		TOTALMEM=size;
		MAXLINX=maxlinx;
		RAM=new char[TOTALMEM];
		linx=new void *[MAXLINX];
	}
};
/* sample usage:
	memager ram(0x100000,0x100);
	struct list{
		int value;
		link next;
	};
	#define listptr(a) ((list *)ram[a])
	link head=-1;
	link addtolist(link head,int value){
		link newelement=ram.alloc(sizeof(list));
		listptr(newelement)->next=head;
		listptr(newelement)->value=value;
		return newelement;
	}
	int check(link head,int value){
		for(link l=head;l!=-1;l=listptr(l)->next)
			if(listptr(l)->value==value)
				return 1;
		return 0;
	}
	link remove(link head,int value){
		if(head==-1)
			return -1;
		link rest=remove(head->next,value);
		if(listptr(head)->value==value){
			ram.free(head);
			return rest;
		}else{
			head->next=rest;
			return head;
		}
	}
*/
