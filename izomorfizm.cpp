#include<iostream>
#include<string>
#include<utility>
#include<algorithm>
#include<vector>
int n;
struct node;
vector<node> graf[2];
struct node{
  string name;
 	vector<int> out;
 	vector<int> in;
 	vector<int> possible;
 	vector<int> distO;
 	vector<int> distI;
 	int chosen;
 	bool operator ==(const node & o)const{
 		if(out.size() != o.out.size())
 			return false;
 		if(in.size() != o.in.size())
 			return false;
 		if(distO!= o.distO)
 			return false;
 		if(distI!= o.distI)
 			return false;
 		return true;
 	}
 	node(const string & name):name(name){}
};
bool used[50];
bool edge[25][25];
int find(int g,const string&name){
	for(int i=0;i<graf[g].size();i++)
		if(graf[g][i].name==name)
			return i;
	graf[g].push_back(node(name));
	return graf[g].size()-1;
}
void add_edge(int g,const string & from,const string&to){
	int f=find(g,from);
	int t=find(g,to);
	graf[g][f].out.push_back(t);
	graf[g][t].in.push_back(f);
	if(g==1)
		edge[f][t]=true;
}
bool isok(){
	for(int i=0;i<graf[0].size();i++){
		int a=graf[0][i].chosen;
		for(int j=0;j<graf[0][i].out.size();j++){
			int b=graf[0][graf[0][i].out[j]].chosen;
			if(!edge[a][b])
				return false;
		}
	}
	return true;
}
bool broot(int p){
	if(p==graf[0].size()){
		return isok();
	}else{
		//cout << "Abs size:" <<graf[0][p].possible.size() << endl;
		for(int i=0;i< graf[0][p].possible.size(); i++){
			int j=graf[0][p].possible[i];
			if(!used[j]){
				used[j]=true;
				graf[0][p].chosen=j;
				if(broot(p+1))
					return true;
				used[j]=false;
			}
		}
		return false;
	}
}
int main(){
	while(1){
		cin >> n;
		if(!n)
			return 0;
		memset(edge,0,sizeof(edge));
		for(int g=0;g<2;g++){
		  graf[g].clear();
			for(int i=0;i<n;i++){
				string from,to;
				cin >> from >> to;
				add_edge(g,from,to);
			}
		}
		int dist[25][25];
		for(int g=0;g<2;g++){
			memset(dist,29,sizeof(dist));
			for(int i=0;i<graf[g].size();i++){
				dist[i][i]=0;
				for(int j=0;j<graf[g][i].out.size();j++)
					dist[i][graf[g][i].out[j]]=1;
			}
			for(int m=0;m<graf[g].size();m++)
				for(int f=0;f<graf[g].size();f++)
					for(int t=0;t<graf[g].size();t++)
						if(f!=t)
							dist[f][t]<?=dist[f][m]+dist[m][t];
			for(int i=0;i<graf[g].size();i++){
				for(int t=0;t<graf[g].size();t++)
					graf[g][i].distO.push_back(dist[i][t]);
				sort(graf[g][i].distO.begin(),graf[g][i].distO.end());
				for(int f=0;f<graf[g].size();f++)
					graf[g][i].distI.push_back(dist[f][i]);
				sort(graf[g][i].distI.begin(),graf[g][i].distI.end());
			}
		}
		for(int i=0;i<graf[0].size();i++)
			for(int j=0;j<graf[1].size();j++)
				if(graf[0][i]==graf[1][j])
				  graf[0][i].possible.push_back(j);
		memset(used,0,sizeof(used));
		broot(0);
		vector<pair<string,string> > dict;
		for(int i=0;i<graf[0].size();i++)
			dict.push_back(make_pair(graf[0][i].name,graf[1][graf[0][i].chosen].name));
		sort(dict.begin(),dict.end());
		for(int i=0;i<dict.size();i++)
			cout << dict[i].first << '/' << dict[i].second << endl;
		cout << endl;
	}
}
