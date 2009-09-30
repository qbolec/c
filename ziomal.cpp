#include <iostream>
#include <map>

using namespace std;

long long int n,k;
map<long long int, long long int> m;

long long int calc(long long int n, long long int k) {
  cout << "VIS" << n << " , " << k << endl;
	long long int val, l;
	map<long long int, long long int>::iterator poz;
	
	if ((poz = m.find(n)) != m.end()) {
		return poz->second;
	}

	l = (n + 1)/2;
	if (!(n % 2)) {
		val = ((calc(l+1,k)*calc(l,k)) + (calc(l,k)*calc(l-1,k)))%k;
    } else {
		val = ((calc(l+1,k)*calc(l-1,k)) + (calc(l,k)*calc(l-2,k)))%k;
	}
	m.insert(make_pair(n, val));
	return val;
}

int main() {
	long long int i;

	cin >> n >> k;
	
	m.insert(make_pair(0,0));
	m.insert(make_pair(1,1));

	for (i = 2; i < 60; i++) {
		m.insert(make_pair(i,(m[i-1]+m[i-2])%k));
	}

	cout << calc(n,k) << endl;

	return 0;
}
