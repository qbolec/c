#include <iostream.h>
/*
this is qbolec's algo for AI to the game Batummi [nokia]
copy wright to him, and so on...
71.vanisoft.2003
*/
const int MAXFOWARDMOVES=20;
const int MAXTOTALMOVES=1000000;

const int BUCKETS=6;
const int BUCKETSTOTAL=(BUCKETS+1)<<1;
const int BEANSINIT=3;

const int PLAYER0=0;
const int PLAYER0HOME=BUCKETS;

const int PLAYER1=BUCKETS+1;
const int PLAYER1HOME=BUCKETSTOTAL-1;

const int BEANSTOTAL=(BUCKETS<<1)*BEANSINIT;
struct game{
	int beans[BUCKETSTOTAL];
	int player;
};

int totalmoves=0;
int aimove=0;

inline int oposite(int b){
	return PLAYER1HOME-b-1;
}
inline int move(game & gold,int b){
	//if(totalmoves==MAXTOTALMOVES)return 0;
	if(totalmoves==MAXTOTALMOVES){
		cout << '.' << flush;
		totalmoves=0;
	}
	if(gold.beans[b]){
		totalmoves++;
		int be=gold.beans[b];
		gold.beans[b]=0;
		int bu=b;
		if(gold.player==0){
			while(be--){
				if(++bu==PLAYER1HOME)bu=0;
				gold.beans[bu]++;
			}
			if(bu==PLAYER0HOME)
				return 1;
			gold.player=1;
			if((gold.beans[bu]==1)&&bu<PLAYER0HOME){
				gold.beans[PLAYER0HOME]+=1+gold.beans[oposite(bu)];
				gold.beans[oposite(bu)]=0;
				gold.beans[bu]=0;
			}
		}else{
			while(be--){
				if(++bu==PLAYER0HOME)bu++;
				else if(bu==BUCKETSTOTAL)bu=0;
				gold.beans[bu]++;
			}
			if(bu==PLAYER1HOME)
				return 1;
			gold.player=0;
			if((gold.beans[bu]==1)&&(bu>PLAYER0HOME)){
				gold.beans[PLAYER1HOME]+=1+gold.beans[oposite(bu)];
				gold.beans[oposite(bu)]=0;
				gold.beans[bu]=0;
			}
		}
		return 1;
	}else{
			return 0;
	}

}
inline void cleargame(game & g){
	for(int i=PLAYER0;i<PLAYER0HOME;i++)
		g.beans[i]=BEANSINIT;
	g.beans[PLAYER0HOME]=0;

	for(int i=PLAYER1;i<PLAYER1HOME;i++)
		g.beans[i]=BEANSINIT;
	g.beans[PLAYER1HOME]=0;
	g.player=0;
}
int AI(game & g,int min,int max,int foward){
	if(foward==MAXFOWARDMOVES)
		return g.beans[PLAYER0HOME];
	foward++;
	if(g.beans[PLAYER0HOME]>=max)return max;
	if(g.beans[PLAYER1HOME]+min>=BEANSTOTAL)return min;
	game g2;
	int gotmove=0;
	int bestmove=-1;
	int best;
	if(g.player==0){
		best=min;
		for(int b=PLAYER0;b<PLAYER0HOME;b++){
			g2=g;
			if( move(g2,b) ){
				int result=AI(g2,best,max,foward);
				if(result>best){
					best=result;
					bestmove=b;
				}
				if(best>=max)return max;
				gotmove=1;
			}
		}
	}else{
		best=max;
		for(int b=PLAYER1;b<PLAYER1HOME;b++){
			g2=g;
			if( move(g2,b) ){
				int result=AI(g2,min,best,foward);
				if(result<best){
					best=result;
					bestmove=b;
				}
				if(best<=min)return min;
				gotmove=1;
			}
		}
	}
	aimove=bestmove;
	if(gotmove)
		return best;
	else
		return g.beans[PLAYER0HOME];

}
int main(){
	game thegame;
	cleargame(thegame);

	while(1){
		aimove=0;
    	totalmoves=0;
		int bestresult=AI(thegame,0,BEANSTOTAL,0);
    	cout << "best result:" << bestresult << " by movin' beans from bucket " << aimove <<  endl << "[Procesed " << totalmoves << " moves]"<<endl;
    	if(aimove==-1)break;
    	move(thegame,aimove);
    }
	return 0;
}
