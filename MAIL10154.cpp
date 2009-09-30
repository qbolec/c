/*   @JUDGE_ID:   14143RZ   10154   C++   "O(cnt*(ans+lg cnt )"   */
#include<iostream.h>
#include<stdlib.h>
struct turtle{
	int s;
	int m;
};
turtle turtles[6000];
int count=0;
int maxtonage[6000]={0x7FFFFFFF};//logiczne ze ta tablica jest monotoniczna no nie?:)
#define min(a,b) (a<b)?a:b
int cmp(const void *a,const void *b){
	return ((turtle *)b)->s-((turtle *)a)->s;
}
int main(){
	int m,s;
	for(cin >> m >> s;!cin.eof();count++){
		turtles[count].m=m;
		turtles[count].s=s;
		cin >> m >> s;
	}
	qsort(turtles,count,sizeof(turtle),cmp);
	int answer=0;
	for(int d=0;d<count;d++){
		int cp=turtles[d].s-turtles[d].m;
		for(int t=answer+1;t;t--){
			int nt= min( cp ,(maxtonage[t-1]-turtles[d].m) );
			if( maxtonage[t] < nt){
				maxtonage[t]=nt;
				if(t>answer)answer++;
			}
		}
	}
	cout << answer << endl;
	return 0;
}
