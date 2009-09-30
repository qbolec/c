#include<iostream.h>
int main(){
	int T;
	cin >> T;
	while(T--){
		int N,B;
		int cat=0;
		cin >> N >> B;
		for(int i=0;i<B;i++){
			int K;
			cin >> K;
			int sa=1;
			for(int i=0;i<K;i++){
				int a;
				cin >> a ;
				sa*=a;
				sa%=N;
			}
			cat+=(sa%N);
			cat%=N;
		}
		cout << (cat%N) << endl;
	}
	return 0;
}
