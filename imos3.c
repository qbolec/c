#include <stdio.h>
#include <string.h>
void compare(char * filea,char * fileb){
    /*idea jest taka : wczytujemy po jednym slowie jak dlugo sie da:P*/
    FILE * fda=fopen(filea,"rb");
    FILE * fdb=fopen(fileb,"rb");
    char worda[256];
    char wordb[256];
    while(!feof(fda)){
    	fscanf(fda,"%s",worda);
    	fscanf(fdb,"%s",wordb);
    	if(strcmp(worda,wordb)){
    		printf("Pliki roznia sie slowami %s i %s",worda,wordb);
    		return;
    	}
    	if(feof(fda) ^^ feof(fdb)){
    		printf("Wyglada na to ze jeden z plikow sie skonczyl szybciej");
    		return;
    	}
    }
	printf("Pliki sa identyczne");
}
int main(int argc, char * args[]){
	if(argc<4){
		printf("Skladnia :%s nazwapliku nazwapliku",args[0]);
	}else{
        compare(args[1],args[2]);
	}
}
