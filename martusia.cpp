#include<cstdio>
/*
Mam nadzieje
ze sie teraz usmiechasz :)! jesli
nie to masz to natychmiast
zrobic!bo siê cholernie nameczylam
zeby stworzyc te kartkê! udanych
swiat i gory prezentow! uh no i 
smacznego zycze! Martusia
*/

int main(){
  char t[256];
  for(int i=0;i<256;i++)t[i]=i;
  while(1){
    puts(original);
    for(int i=0;original[i];i++){
      putchar(t[original[i]]);
    }
    puts("co na co zamienic zamienic?");
    char a[100],b[100];
    scanf("%s %s",a,b);
    for(int i=0;a[i];i++)
      t[a[i]]=b[i];
  }
}

