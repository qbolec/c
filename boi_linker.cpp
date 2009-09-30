#include<fstream.h>
#include<string.h>
ifstream fin("LINKER.IN");
ofstream  fout("LINKER.OUT");
//#define fin cin
//#define fout cout
char ENTRYPOINT[32];
int modulescount;
struct modlist{
	modlist * next;
	int id;
};
struct symbol{
	char name[32];
	char dup;
	char used;
	modlist * decl;
	modlist * cure;
};
struct symbollist{
	symbollist * next;
	symbol * s;
};
symbollist * hashtab[1024];
struct mod{
	char name[32];
	char entry;
	char used;
};
char dependency[100][100];
mod module[100];
symbollist * duplicated=0;
int duplicatedc=0;
symbollist * unresolved=0;
int unresolvedc=0;
int used=0;
int hash(char * t){
	int h=0;
	while(*t){
		h<<=1;
		h^=*t++;
	}
	return h&1023;
}
void exports(int id,char * sym){
	if(!strcmp(ENTRYPOINT,sym))
		module[id].entry=1;
	int h=hash(sym);
	for(symbollist * l=hashtab[h];l;l=l->next)
		if(!strcmp(l->s->name,sym)){
			modlist * nexus=new modlist;
			nexus->next=l->s->decl;
			nexus->id=id;
			l->s->decl=nexus;
			if(l->s->decl)
				l->s->dup=1;
			return;
		}
	symbollist * nexus3=new symbollist;
	nexus3->next=hashtab[h];
	nexus3->s=new symbol;
	nexus3->s->decl=new modlist;
	nexus3->s->decl->next=0;
	nexus3->s->decl->id=id;
	nexus3->s->cure=0;
	nexus3->s->dup=0;
	nexus3->s->used=0;
	hashtab[h]=nexus3;
	strcpy(nexus3->s->name,sym);
}
void imports(int id,char * sym){
	int h=hash(sym);
	for(symbollist * l=hashtab[h];l;l=l->next)
		if(!strcmp(l->s->name,sym)){
			modlist * nexus=new modlist;
			nexus->next=l->s->cure;
			nexus->id=id;
			l->s->cure=nexus;
			return;
		}
	symbollist * nexus3=new symbollist;
	nexus3->next=hashtab[h];
	nexus3->s=new symbol;
	nexus3->s->cure=new modlist;
	nexus3->s->cure->next=0;
	nexus3->s->cure->id=id;
	nexus3->s->decl=0;
	nexus3->s->dup=0;
	nexus3->s->used=0;
	hashtab[h]=nexus3;
	strcpy(nexus3->s->name,sym);
}
void dep(){
	for(int h=0;h<1024;h++)
		if(hashtab[h])
			for(symbollist * l=hashtab[h];l;l=l->next)
				for(modlist * c=l->s->cure;c;c=c->next)
					if(l->s->decl)
						for(modlist * d=l->s->decl;d;d=d->next)
							dependency[c->id][d->id]=1;
}
void dfs(int id){
	if(module[id].used)
		return;
	module[id].used=1;
	used++;
	for(int i=0;i<modulescount;i++)
		if(dependency[id][i])
			dfs(i);
}
void need(){
	for(int i=0;i<modulescount;i++)
		if(module[i].entry)
			dfs(i);
}
void use(){
	for(int h=0;h<1024;h++)
		if(hashtab[h])
			for(symbollist * l=hashtab[h];l;l=l->next)
				for(modlist * c=l->s->cure;c;c=c->next)
					if(module[c->id].used)
						l->s->used=1;
}
void check(){
	for(int h=0;h<1024;h++)
		if(hashtab[h])
			for(symbollist * l=hashtab[h];l;l=l->next)
				if(l->s->used){
					if(l->s->dup){
						duplicatedc++;
						symbollist * nexus=new symbollist;
						nexus->next=duplicated;
						nexus->s=l->s;
						duplicated=nexus;
					}
					if(!l->s->decl){
						unresolvedc++;
						symbollist * nexus=new symbollist;
						nexus->next=unresolved;
						nexus->s=l->s;
						unresolved=nexus;
					}
				}

}
int main(){
	int E,I;
	char sym[32];
	fin >> ENTRYPOINT;
	fin >> modulescount;
	for(int i=0;i<modulescount;i++){
		fin >> module[i].name;
		fin >> E;
		for(int j=0;j<E;j++){
			fin >> sym;
			exports(i,sym);
		}
		fin >> I;
		for(int j=0;j<I;j++){
			fin >> sym;
			imports(i,sym);
		}
	}
	dep();
	need();
	use();
	check();
	fout << used << endl;
	for(int m=0;m<modulescount;m++)
		if(module[m].used)
			fout << module[m].name << endl;
	fout << duplicatedc << endl;
	while(duplicated){
		fout << duplicated->s->name << endl;
		duplicated=duplicated->next;
	}
	fout << unresolvedc << endl;
	while(unresolved){
		fout << unresolved->s->name << endl;
		unresolved=unresolved->next;
	}
	return 0;
}
