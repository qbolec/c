#include <fstream.h>
int main(){
	int file=0;
	char filename[32];
	cout << "Podaj litere dysku do zapchania" << endl;
	cin >> filename[0];
	filename[7]='.';
	filename[8]='t';
	filename[9]='x';
	filename[10]='t';

	while(1){
		filename[1]=':';
		filename[2]='\\';
		filename[3]='0'+(char)((file/1000)%10);
		filename[4]='0'+(char)((file/100)%10);
		filename[5]='0'+(char)((file/10)%10);
		filename[6]='0'+(char)((file/1)%10);
		ofstream dupa(filename);
		for(int i=0;i<100000;i++)
			dupa << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
			;
		dupa.close();
		file++;
		cout << file << endl;
	}
}
