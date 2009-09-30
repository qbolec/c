/*BU by qbolec*/#include <iostream.h>
char * string[40];
void show(long i,char * s){
   cout << "string[" << i << "]=\"";
   while(*s){
     if(*s=='\\') cout << "\\\\";
     else{
       if(*s=='\"')cout << "\\\"";
       else cout << *s;
     }
     s++;
   }
   cout << "\";\n";
}
void main(){
string[1]="/*BU by qbolec*/#include <iostream.h>";
string[2]="char * string[40];";
string[3]="void show(long i,char * s){";
string[4]="   cout << \"string[\" << i << \"]=\\\"\";";
string[5]="   while(*s){";
string[6]="     if(*s=='\\\\') cout << \"\\\\\\\\\";";
string[7]="     else{";
string[8]="       if(*s=='\\\"')cout << \"\\\\\\\"\";";
string[9]="       else cout << *s;";
string[10]="     }";
string[11]="     s++;";
string[12]="   }";
string[13]="   cout << \"\\\";\\n\";";
string[14]="}";
string[15]="void main(){";
string[16]="for(long i=1;i<=15;i++)cout << string[i] << endl;";
string[17]="for(long j=1;j<=19;j++)show(j,string[j]);";
string[18]="for(long k=16;k<=19;k++)cout << string[k] << endl;";
string[19]="}";
for(long i=1;i<=15;i++)cout << string[i] << endl;
for(long j=1;j<=19;j++)show(j,string[j]);
for(long k=16;k<=19;k++)cout << string[k] << endl;
}
