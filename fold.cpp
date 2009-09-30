#include<iostream.h>
int T;
int N;
int side[2][100000];
int check(int *t,int a,int b){
	cout << "Chek for N=" << N;
	if(a>b){
		int s=b;
		b=a;
		a=s;
	}
	if(t[a]){
		cout << "a err:" << a << ' ' << b;
		return 0;
	}
	if(t[b]){
		cout << "b err:" << a << ' ' << b;
		return 0;
	}
	for(int i=a+1;i<b;i++)
		if(t[i])
			if((t[i]>=b)||(t[i]<=a)){
				cout << "line :" << i << " to " << t[i] << " crosses :" << a << " to " << b;
				return 0;
			}
	t[a]=b;
	t[b]=a;
	return 1;
}
void reset(){
	for(int i=0;i<=N;i++)
		side[0][i]=side[1][i]=0;
}
void test(){
	int start,end;
	cin >> start;
	for(int i=1;i<N;i++){
		cin >> end;
		if(check(side[i&1],start,end)==0){
			cout << "NO" << endl;
			return;
		}
		start=end;
	}
	cout << "YES" << endl;
}
int main(){
	cin >> T;
	while(T--){
		cin >> N;
		test();
		reset();
	}
}
