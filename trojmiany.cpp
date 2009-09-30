#include<iostream>
char c[80][80];
int main(){
	c[0][0]=1;
	for(int i=1;i<80;i++)
		c[0][i]=0;
	for(int n=1;n<80;n++){
		cout << (int)(c[n][0]=1);
		cout << (int)(c[n][1]=(c[n-1][1]+1)%3);
		for(int i=2;i<80;i++)
			cout << (int)(c[n][i]=(c[n-1][i]+c[n-1][i-1]+c[n-1][i-2])%3);
		cout << endl;
	}
	return 0;
};
