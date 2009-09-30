#include <iostream.h>
/*
 * chinskie twierdzenie o resztach wskazuje izomorfizm,
 * ale jak policzyc funkcje odwrotn¹?
 * tablica mods[] zawiera rzedy pierscieni
 * mozna ja sobie dowolnie edytowac
 */
const int modscount=4;
const int mods[modscount]={0x10001,99991,991,255};

class chinanum{
public:
	int mod[modscount];
	//most interesting part: displaying number
	void print(char buffer[]){
		/*

		 */
	}
	//operations:
	void operator += (chinanum & other){
		for(int i=0;i<modscount;i++)
			mod[i]=(mod[i]+other.mod[i])%mods[i];
	}
	void operator -= (chinanum & other){
		for(int i=0;i<modscount;i++)
			mod[i]=(mod[i]-other.mod[i])%mods[i];
	}
	void operator *= (chinanum & other){
		for(int i=0;i<modscount;i++)
			mod[i]=(mod[i]*other.mod[i])%mods[i];
	}
	void operator /= (chinanum & other){
		for(int i=0;i<modscount;i++){
			//hm? is it possible to determine?
		}
	}

	//constructors: [clone'ing is easy so not defined]
	chinanum(int n){
		for(int i=0;i<modscount;i++)
			mod[i]=n%mods[i];
    }
    chinanum(int * m){
    	for(int i=0;i<modscount;i++)
    		mod[i]=m[i];
    }
    chinanum(){
    	for(int i=0;i<modscount;i++)
    		mod[i]=0;
    }
};





int main(){
	return 0;
}

