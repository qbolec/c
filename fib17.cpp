#include <iostream.h>
int rest[]={1,1,2,3,5,8,13,4,0,4,4,8,12,3,15,1,16,0,16,16,15,14,12,9,4,13,0,13,13,9,5,14,2,1,6,1,0,1};
char bignum[1024];
int len=0;
int main(){
    cin >> bignum;
    int reszta=0;
    while(bignum[len]){
    	reszta*=10;
    	reszta+=bignum[len++]-'0';
    	reszta%=38;
    }
    cout << rest[reszta];
	return 0;
}
