#include<iostream.h>

const int PAT_SIZE=6;
const int TAB_SIZE=10;
const int EQ_SIZE=10;

class cashed{
public:
	int	values[TAB_SIZE][TAB_SIZE];
	int (* myfoo)(cashed & c,int n,int k);
	int operator ()(int n,int k){
		if(values[n][k]==-1)
			return values[n][k]=myfoo(*this,n,k);
		else
			return values[n][k];
	}
	cashed(int (* foo)(cashed & c,int n,int k)){
		myfoo=foo;
		for(int n=0;n<TAB_SIZE;n++)
			for(int k=0;k<TAB_SIZE;k++)
				values[n][k]=-1;
	}
};
int newton_foo(cashed & c,int n,int k){
	if(n<0)return 0;
	if(k==0)return 1;
	if(k>n)return 0;
	return c(n-1,k-1)+c(n-1,k);
}
int cycles_foo(cashed & c,int n,int k){
	if(n<0)return 0;
	if(n==k)return 1;
	if(k==0)return 0;
	if(k>n)return 0;
	return c(n-1,k-1)+(n-1)*c(n-1,k);
}
int sets_foo(cashed & c,int n,int k){
	if(n<0)return 0;
	if(n==k)return 1;
	if(k==0)return 0;
	if(k>n)return 0;
	return c(n-1,k-1)+k*c(n-1,k);
}
int partitions_foo(cashed & c,int n,int k){
	if(n<0)return 0;
	if(n<k)return 0;
	if(k==0)return 0;
	if(k==n)return 1;
	if(k==1)return 1;
	return c(n-1,k-1)+c(n-k,k);
}
cashed newton( newton_foo );
cashed cycles( cycles_foo );
cashed sets( sets_foo );
cashed partitions( partitions_foo );
const int LIM_SILNIA=13;
int silnia[LIM_SILNIA]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600};

typedef enum atom { ONE,TWO, COL, ROW,   NEG,SIL,   ADD,SUB,MUL,DIV,MOD,EXP,CYC,SET,NEW, TOTAL };
char * name[TOTAL]={"1","2","k","n","zaneguj","silnia","dodaj","odejmij","pomnoz","podziel","wez reszte","spoteguj","#cykli","#podzialow","#wyborow"};
atom formula[EQ_SIZE];

int pattern[PAT_SIZE][PAT_SIZE]={
{1,0,0,0,0,0},
{1,1,0,0,0,0},
{1,2,1,0,0,0},
{1,3,3,1,0,0},
{1,4,6,4,1,0},
{1,5,10,10,5,1},
};

int check(int size,int r,int c){
	int stack[EQ_SIZE+1];
	int stackpos=0;
	for(int i=0;i<size;i++)
		switch(formula[i]){
		case ONE:
			stack[++stackpos]=1;
		break;
		case TWO:
			stack[++stackpos]=2;
		break;
		case ROW:
			stack[++stackpos]=r;
			break;
		case COL:
			stack[++stackpos]=c;
			break;

		case NEG:
			stack[stackpos]=-stack[stackpos];
			break;
		case SIL:
			if(stack[stackpos]>=0 && stack[stackpos]<LIM_SILNIA)
				stack[stackpos]=silnia[stack[stackpos]];
			else
				return 0;
			break;
		case ADD:
			stack[stackpos-1]+=stack[stackpos];
			stackpos--;
			break;
		case SUB:
			stack[stackpos-1]-=stack[stackpos];
			stackpos--;
			break;
		case MUL:
			stack[stackpos-1]*=stack[stackpos];
			stackpos--;
			break;
		case DIV:
			if(!stack[stackpos])
				return 0;
			stack[stackpos-1]/=stack[stackpos];
			stackpos--;
			break;
		case MOD:
			if(!stack[stackpos])
				return 0;
			stack[stackpos-1]%=stack[stackpos];
			stackpos--;
			break;
		case EXP:
			int val;
			val=1;
			if(stack[stackpos-1])
				if(stack[stackpos]<32 && stack[stackpos]>0)
					for(int i=stack[stackpos];i;i--)
						val*=stack[stackpos-1];
				else
					return 0;
			else
				if(stack[stackpos])
					val=0;
			stack[stackpos-1]=val;
			stackpos--;
			break;
		case CYC:
			if(stack[stackpos]<TAB_SIZE && stack[stackpos-1]<TAB_SIZE && stack[stackpos]>=0 && stack[stackpos-1]>=0)
				stack[stackpos-1]=cycles(stack[stackpos-1], stack[stackpos]);
			else
				return 0;
			stackpos--;
			break;
		case SET:
			if(stack[stackpos]<TAB_SIZE && stack[stackpos-1]<TAB_SIZE && stack[stackpos]>=0 && stack[stackpos-1]>=0)
				stack[stackpos-1]=sets(stack[stackpos-1], stack[stackpos]);
			else
				return 0;
			stackpos--;
			break;
		case NEW:
			if(stack[stackpos]<TAB_SIZE && stack[stackpos-1]<TAB_SIZE && stack[stackpos]>=0 && stack[stackpos-1]>=0)
				stack[stackpos-1]=newton(stack[stackpos-1], stack[stackpos]);
			else
				return 0;
			stackpos--;
			break;
		}
	if(stack[1]==pattern[r][c])
		return 1;
	return 0;
}

int check(int size){
	for(int r=0;r<PAT_SIZE;r++)
		for(int c=0;c<PAT_SIZE;c++)
			if(!check(size,r,c))
				return 0;
	cout << "FOUND!" << endl;
	for(int i=0;i<size;i++)
		cout << name[formula[i]] << endl;
	return 1;
}
int brootfind(int pos,int balance){
	if(pos==EQ_SIZE){
		if(balance==1)
			return check(pos);
		return 0;
	}
	int a;
	if(balance==1){
		if(check(pos))
			return 1;
		for(a=ONE;a<NEG;a++){
			formula[pos]=(enum atom)a;
			if(brootfind(pos+1,balance+1))
				return 1;
		}
		for(a=NEG;a<ADD;a++){
			formula[pos]=(enum atom)a;
			if(brootfind(pos+1,balance))
				return 1;
		}
	}else if(balance>1){
		for(a=ONE;a<NEG;a++){
			formula[pos]=(enum atom)a;
			if(brootfind(pos+1,balance+1))
				return 1;
		}
		for(a=NEG;a<ADD;a++){
			formula[pos]=(enum atom)a;
			if(brootfind(pos+1,balance))
				return 1;
		}
		for(a=ADD;a<TOTAL;a++){
			formula[pos]=(enum atom)a;
			if(brootfind(pos+1,balance-1))
				return 1;
		}
	}else if(balance==0){
		for(a=ONE;a<NEG;a++){
			formula[pos]=(enum atom)a;
			if(brootfind(pos+1,balance+1))
				return 1;
		}
	}
	return 0;
}
int main(){
	for(int r=0;r<PAT_SIZE;r++)
		for(int c=0;c<PAT_SIZE;c++)
			pattern[r][c]=partitions(r,c);
	brootfind(0,0);
	return 0;
}
