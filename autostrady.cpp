#include<iostream.h>
int n,k;
struct autostrada{
	int p;
	int q;
};
struct list{
	int id;
	list * next;
}
autostrada a[20002];
list * sort[20002];
int sorted[20002];
int begin[20002];
int end[20002];
void solve(int from,int to){
	int au[20002];
	int auc=0;
	for(int i=0;i<k;i++)
		if(from<=a[sort[i]].p)
			if(a[sort[i]].q<=to)
				au[auc++]=sort[i];
	int reservedN=0;
	int reservedS=0;
	for(int i=0;i<auc;i++){
		if(reservedN<=au[i].p){
			reservedN=au[i].q;
		}else{
			if(reservedS<=au[i].p){
				reservedS=au[i].q;
			}else{
				cout << "NIE" << endl;
				exit(0);
			}
		}
	}
}
int main(){
	cin >> n >> k;
	for(int i=0;i<k;i++){
		cin >> a[i].p >> a[i].q ;
		begin[a[i].p]++;
		end[a[i].p]++;
	}
	//sortujemy po lewym koncu
	for(int i=0;i<k;i++){
		list * nexus=new list;
		nexus->id=i;
		nexus->next=sort[a[i].p];
		sort[a[i].p]=nexus;
	}
	int j=0;
	for(int i=0;i<20002;i++){
		for(list * l=sort[i];l;l=l->next)
			sorted[j++]=l->id;
	//cutin single and solvin
	int done=0;
	while(1){
		int opened=0;
		int from=done;
		while(!begin[from] && from==n)
			from++;
		if(from==n)
			break;
		done=from;
		opened+=begin[done++];
		while(1){
			opened-=end[done];
			if(opened==0){
				solve(from,done);
			}
			opened+=begin[done];
			done++;
		}
	}

}
