#include <bios.h>
#include <stdio.h>
int main(){
	char buff[1024];
	scanf("%s",buff);
	outportb(0 , buff[0]);
	return 0;
}
