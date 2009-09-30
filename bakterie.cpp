#include <iostream.h>
struct act{
 	char ac;
 	int a;
 	int b;
};
int n,m,t;
char K[1232];
act action[1000];
double p[30];
void sim(act&a){
double s;
	switch(a.ac){
	case 'd':
		p[a.a]=0;return;
	case 'r':
		p[a.a]*=a.b;return;
	case 'c':
		p[a.a]+=p[a.b];return;
	case 't':
		p[a.a]+=p[a.b];
		p[a.b]=0;return;
	case 's':

		s=p[a.a];
		p[a.a]=p[a.b];
		p[a.b]=s;
		return;
	case 'm':
		s=p[n-1];
		for(int i=n-1;i;i--)
			p[i]=p[i-1];
		p[0]=s;return;
	}
}
int main(){
	cin >> n >> m >> t;
	cin >> K;
	char what[256];
	for(int i=0;i<n;i++)
		p[i]=1;

	for(int i=0;i<m;i++){
		cin >> what >> action[i].a >> action[i].b;
		action[i].ac=what[0];
	}
	for(int i=0;i<t;i++)
    	sim(action[i%m]);
    for(int i=0;i<n;i++)
    	cout << p[i] << endl;
}
