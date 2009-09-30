#include<cstdio>
#include<vector>
#include<algorithm>
#include<iostream>
#include<cassert>
#define FOR(i,c) for(typeof(c.begin()) i =c.begin(); i !=c.end();++ i )
using namespace std;
typedef vector< vector<unsigned char> > GRAF;
int n,k;
typedef unsigned long long number;
number g[200][200];
number x[200];
vector<bool> taken;
number gcd(number a,number b){
	if(!b)
		return a;
	return gcd(b,a%b);
}
void take(int v){
  assert(!taken[v]);
  taken[v]=true;
}
void rem(GRAF &graf,int v){
	FOR(j,graf[v])
		if(*j!=v)
      FOR(i,graf[*j])
        if(*i==v){
          swap(graf[*j].back(),*i);
          graf[*j].pop_back();
          break;
        }
	graf[v].clear();
}
bool minCover(GRAF & graf,int k){//graf,k,n
	cout << "minCover k=" << k << endl;
	if(k<0)
		return false;
	for(int i=0;i<graf.size();i++)
		FOR(j,graf[i])
			cout << i << " -> " << (int)*j << endl;
  vector<unsigned char> foundNow;
	vector<unsigned char> stack;
	for(int i=0;i<n;i++)
		if(graf[i].size()==1)
			stack.push_back(i);
	while(stack.size()){
		int i=stack.back();
		stack.pop_back();
		if(graf[i].size()==1){
			int v=graf[i][0];
			foundNow.push_back(v);
			FOR(i,graf[v])
				if(graf[ *i ].size()==2)
					stack.push_back(*i);
			rem(graf,v);
			k--;
    	if(k<0)
		    return false;
		}
	}
	int edges=0;
	for(int i=0;i<n;i++)
	 edges+=graf[i].size();
	edges/=2;
	if(edges && !k)
		return false;
	if(edges <= k){
   	FOR(i,foundNow)
   	  take(*i);
		for(int i=0;i<n;i++)
			if(graf[i].size()){
				rem(graf,i);
				take(i);
			}
   	return true;
  }
	int b=0;
	for(int i=1;i<n;i++)
		if(graf[i].size()>graf[b].size())
			b=i;
	GRAF copy=graf;
	rem(copy,b);
	if(minCover(copy,k-1)){
   	FOR(i,foundNow)
   	  take(*i);
		take(b);
		return true;
	}	
	if(k>=graf[b].size()){
  	GRAF copy;
  	copy.resize(n);
    vector<bool> keep;
  	keep.resize(n,true);
   	FOR(i,graf[b])
   	  keep[*i]=false;
    keep[b]=false;
    for(int i=0;i<n;i++)
      if(keep[i])
        FOR(j,graf[i])
          if(keep[*j])
            copy[i].push_back(*j);
  	if(minCover(copy,k-graf[b].size())){
     	FOR(i,graf[b])
     		take(*i);
     	FOR(i,foundNow)
  	 		take(*i);
  		return true;
  	}
 	}
	return false;
}
bool clamp(number v){
	cout << "Trying clamped to " << v << endl;
	taken.clear();
	taken.resize(n,false);
	GRAF graf;
	graf.resize(n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(i!=j && g[i][j]<=v)
				graf[i].push_back(j);
  int k2=k;
  for(int i=0;i<n;i++)
    if(x[i]<=v){
      k2--;
      rem(graf,i);
      take(i);
    }    
  return minCover(graf,k2);
}
void solve(){
  cin >> n >> k;
	for(int i=0;i<n;i++)
    cin >> x[i];
	vector<number> w;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
 			g[i][j]=gcd(x[i],x[j]);
 		  w.push_back(g[i][j]);
	  }
	w.push_back(0);
	sort(w.begin(),w.end());
	w.erase(unique(w.begin(),w.end()),w.end());

	int a=0;
	int b=w.size();
	while(a+1<b){
		int c=(a+b)/2;
		if(clamp(w[c]))
			a=c;
		else
			b=c;
	}
	clamp(w[a]);
	int cnt=0;
	for(int i=0;i<n;i++)
	 if(taken[i])
	   cnt++;
	for(int i=0;i<n && cnt<k;i++)
		if(!taken[i]){
			take(i);
			cnt++;
		}
  assert(cnt==k);
	for(int i=0;i<n;i++)
		if(taken[i]){
		  cout << i+1 << ' ';
    }
  cout << endl;
}
int main(){
	int t;
	cin >> t;
	while(t--)
		solve();
	return 0;
}

