#include<cstdio>
#include<cstdlib>
using namespace std;
int main(){
	for(int t=0;t<100;t++){
		int num=10000;
		printf("%d\n",num);
		for(int i=0;i<num;i++)
			printf("%d %d\n",rand()%40000,rand()%40000);
	}
	return 0;
}
