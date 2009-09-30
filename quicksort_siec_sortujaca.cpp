#include<cstdio>
#include<cstdlib>
int current_t=0;
void dump(const unsigned int x){
	for(int i=0;i<32;++i){
		putchar(x&1<<i ? '1':'0');
		if(i%4==3){
			putchar(' ');
		}
	}
	putchar('\n');
}
bool verify(const unsigned int x,int start,int level,int max_level){
	if(level==max_level){
		return true;
	}
	const int len= 1<<(level-1);
	const int off= (1<<level)-1;
	int end= start+len;
	for(int i=0;i<len;i++){
		int left = (x>>start)&1;
		int right = (x>>end)&1;
		if(left<right){
			return false;
		}
		++start;
		++end;
	}
	return verify(x,start-len,level-1,max_level)&&verify(x,start,level-1,max_level);
}
bool check(unsigned int x,int start,int level){
	const int len= 1<<(level-1);
	const int off= (1<<level)-1;
	int end= start+off;
	for(int i=0;i<len;i++){
		int left = (x>>start)&1;
		int right = (x>>end)&1;
		if(left<right){
			return false;
		}
		++start;
		--end;
	}
	return true;
}
void recsort(unsigned int &x,int start,int level){
	if(!level)  return;
	const int off= (1<<level)-1;
	const int len= 1<<(level-1);
	int end= start+off;
	//dump(x);
	for(int i=0;i<len;i++){
		const int maxi = ((x>>start) | (x>>end)) & 1;
		const int mini = ((x>>start) & (x>>end)) & 1;
		x = (x & (~(( 1<<start) | (1 << end)))) | (maxi << start) | (mini << end);
		//if( ((~x) & (1<<start) ) &&  (x & (1<<end) )){
		//  x^=  ((1<<start) | (1<<end));
		//}
		++start;
		--end;
	}
	//recsort(x,start-len,level-1);
	//recsort(x,start,level-1);
}
int sort(unsigned int x,bool du=false){
	unsigned int y=x;
	if(du)dump(x);
	for(int t=0;;++t){
		current_t=t;
		//puts("==");
		
		if(!du && t>1 && (x&0xFFFF0000) && (~x&0x0000FFFF)){
			//printf("interesting: %u\n",y);
			//sort(y,true);
		}
		if(x+1 & x ){
			//for(int level=1;level<=5;++level){
			for(int level=5;level;--level){
				const int len= 1<<level;
				for(int start=0;start<32;start+=len){
					recsort(x,start,level);
				}
				if(level>=5-current_t){
					//LEMAT 1: 
					//w iteracji current_t (0,..), podczas przetwarzania pierwszych current_t+1 poziomów (level), 
					//wczeœniejsze poziomy (lev) pozostaj¹ posortowane
					for(int lev=5;lev>=level;lev--){
						const int le= 1<<lev;
						for(int st=0;st<32;st+=le){
							if(!check(x,st,lev)){
								printf("bad %u\n",y);
							}
						}
					}
				}else{
					//LEMAT 2:
					//w iteracji current_t, podczas przetwarzania g³êbszych poziomów (level),
					//listki poziomu current_t, tworz¹ ci¹g monotonicznie rosn¹cych bloków (jeden blok zawiera parê listków)
					int lev=5-current_t;
					const int le=1<<lev;
					int a=x;
					int b=a>>le;
					if(a&b!=b){
						printf("bad %u\n",x);
					}
				}
			}

			//recsort(x,0,5);
			if(du)dump(x);
			//    if(!verify(x,0,5,0)){
			//		  puts("Ÿle");
			//}
		}else{
			return t;
		}
	}


}
unsigned int bintodec(char * t){
	unsigned int p=0;
	for(int i=0;t[i];i++){
		p=(p<<1)|(t[i]-'0');
	}
	return p;
}
int main(){
	//6 rounds in small to big "1100 1001 1001 1101 1111 0110 0100 1011"
	unsigned int ix=bintodec("11001001100111011111011001001011");
    //unsigned int ix=bintodec("11011001100110011001100110011001");
	//sort(-724831351,true);
	sort(ix,true);
	system("PAUSE");
	int maximal=0;
	for(unsigned int v=1<<30;v!=0xFFFFFFFF;v++){
		v=rand()<<24 ^ rand()<<16 ^ rand()<<8 ^ rand();
		int rounds=sort(v);
		if(rounds>maximal){
			maximal=rounds;
			printf("%d required %d rounds\n",v,rounds);
			sort(v,true);
		} 
		if(rounds==5){
//			printf("tested %d\n",v);			
			//sort(v,true);
		}
	}
}
